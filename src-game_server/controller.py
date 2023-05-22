import os
import multiprocessing as mp
import socket
import sys
import selectors
import types

# private ip of server
HOST = "10.0.0.190"
# whatever port
PORT = 65432
sel = selectors.DefaultSelector()

# gets user input
def get_input():
    usr_in = input("Enter command: ")
    return usr_in

# parses the command entered and jumps to diff function depending on input
def which_input(command):
    img_count = 1
    print(command)
    match command[0]:
        case 'game':
            # need to verify if command[1] is an int
            # create a vm passing in game id, number of vms, and the image count we are on
            procs = linux_vm(command[1], int(command[2]), img_count)
        case _:
            print('Error: Invalid command')

    while (clean_procs(procs)):
        continue


# function called by creating new process, create vm with qemu
def start_linux_vm(img_name, game_val):
    #os.system('qemu-system-i386 -hda ' + img_name + ' -cdrom FD13LIVE.iso -m 16M -boot order=dc')

    # qemu call to create vm, uses img_name as hard disk, and grabs iso file from ssh using game id as path to iso
    os.system('qemu-system-i386 -hda ' + img_name + ' --drive media=cdrom,file=ssh://ubuntu@10.0.0.79/home/ubuntu/game/' + game_val + '/FD13LIVE.iso -m 16M -boot order=dc')
    #print('qemu-system-i386 -hda ' + img_name + ' -cdrom FD13LIVE.iso -m 16M -boot order=dc')

# creates disks and process for vms
def linux_vm(game_val, num_vm, img_count):
    filename_arr = []
    count = img_count
    # for each vm create a unique (for this run of program) disk 
    for i in range(num_vm):
        # name of disk file
        image_name = 'game' + str(game_val) + 'linuximg' + str(count)
        # counter for unique name
        count += 1
        print('creating disk for vm ' + image_name)
        # add disk name to arr
        filename_arr.append(image_name)
        # creates disk with qemu
        os.system('qemu-img create ' + image_name + ' 200M')

    # list of process ids
    procs = []
    # for each vm create process to spawn it
    for i in range(num_vm):
        print('creating linux vm ' + str(i + 1))
        # creates process with start_linux_vm func, passes in disk name and the id of the game
        p = mp.Process(target=start_linux_vm, args=(filename_arr[i], game_val))
        # appends process id to arr
        procs.append(p)
        # starts process
        p.start()

    return procs

# to be implemented later
def windows_vm(num_vm):
    for i in range(num_vm):
        print('creating windows vm ' + str(i + 1))

# cleans up all finished procs, if all procs are finished returns false, otherwise returns true
def clean_procs(procs):
    # arr of finished process indexes
    fin_procs = []
    # for each process
    for i in range(len(procs)):
        # if process is still alive do nothing
        if (procs[i].is_alive()):
            continue
        # otherwise append index to fin_procs
        else:
            print('process ' + str(procs[i]) + ' shut down')
            fin_procs.append(i)
    # for each index in fin_procs
    for i in reversed(fin_procs):
        # kill process
        procs[i].join()
        del procs[i]
    # if all procs are killed return false
    if (procs == []):
        return False
    # otherwise return true
    else:
        return True

def accept_wrapper(sock):
    conn, addr = sock.accept()
    print(f"Accepted connection from {addr}")
    conn.setblocking(False)
    data = types.SimpleNamespace(addr=addr)
    events = selectors.EVENT_READ | selectors.EVENT_WRITE
    sel.register(conn, events, data=data)

def service_connection(key, mask):
    sock = key.fileobj
    data = key.data
    if mask & selectors.EVENT_READ:
        recv_data = sock.recv(1024).decode()#.split('\n')
        if recv_data:
            #print(recv_data.split(' '))
            #return 0
            command = recv_data.split(' ')
            p = mp.Process(target=which_input, args=(command,))
            print(p)
            p.start()
            return p
        else:
            print(f"Closing connection to {data.addr}")
            sel.unregister(sock)
            sock.close()

def main():
    # inits unique image counter
    linux_img_count = 1
    # will be a list of lists of process ids
    procs = []
    # create socket with tcp protocol
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # bind host addr and port to socket
    s.bind((HOST, PORT))
    # listen for input from socket
    s.listen()
    print(f"Listening on {(HOST, PORT)}")
    s.setblocking(False)
    sel.register(s, selectors.EVENT_READ, data=None)
    try:
        # infinite loop for input
        while True:
            events = sel.select(timeout=None)
            for key, mask in events:
                if key.data is None:
                    accept_wrapper(key.fileobj)
                else:
                    procs.append(service_connection(key, mask))
            #clean_procs(procs)

    except KeyboardInterrupt:
        print("Caught keyboard interrupt, exiting")
    finally:
        sel.close()

if __name__ == '__main__':
    main()
