import os
import multiprocessing as mp
import socket

# private ip of server
HOST = "10.0.0.190"
# whatever port
PORT = 65432

# gets user input
def get_input():
    usr_in = input("Enter command: ")
    return usr_in

# parses the command entered and jumps to diff function depending on input
def which_input(command, linux_img_count):
    match command[0]:
        case 'game':
            # need to verify if command[1] is an int

            # create a vm passing in game id, number of vms, and the image count we are on
            return linux_vm(command[1], int(command[2]), linux_img_count)
            '''
            match command[1]:
                case 'linux':
                    # starts creating linux vms
                    return linux_vm(int(command[2]), linux_img_count)
            
                case 'windows':
                    # starts creating windows vms
                    return windows_vm(int(command[2]), linux_img_count)

                case _:
                    print("Error: Invalid command")
                    return 0, linux_img_count
            '''
        case 'exit':
            return 1, linux_img_count

        case _:
            print('Error: Invalid command')
            return 0, linux_img_count

# function called by creating new process, create vm with qemu
def start_linux_vm(img_name, game_val):
    #os.system('qemu-system-i386 -hda ' + img_name + ' -cdrom FD13LIVE.iso -m 16M -boot order=dc')

    # qemu call to create vm, uses img_name as hard disk, and grabs iso file from ssh using game id as path to iso
    os.system('qemu-system-i386 -hda ' + img_name + ' --drive media=cdrom,file=ssh://ubuntu@10.0.0.79/home/ubuntu/game/' + game_val + '/FD13LIVE.iso -m 16M -boot order=dc')
    #print('qemu-system-i386 -hda ' + img_name + ' -cdrom FD13LIVE.iso -m 16M -boot order=dc')

# creates disks and process for vms
def linux_vm(game_val, num_vm, linux_img_count):
    filename_arr = []
    count = linux_img_count
    # for each vm create a unique (for this run of program) disk 
    for i in range(num_vm):
        # name of disk file
        image_name = 'linuximg' + str(count)
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

    return procs, count

# to be implemented later
def windows_vm(num_vm):
    for i in range(num_vm):
        print('creating windows vm ' + str(i + 1))

# cleans up all finished procs, if all procs are finished returns false, otherwise returns true
def clean_procs(procs):
    # arr of finished process indexes
    fin_procs = []
    # arr of cleared process row indexes
    fin_rows = []
    # for each row
    for i in range(len(procs)):
        # for each process in row
        for j in range(len(procs[i])):
            # if process is still alive do nothing
            if (procs[i][j].is_alive()):
                continue
            # otherwise append index to fin_procs
            else:
                print('process ' + str(procs[i][j]) + ' shut down')
                fin_procs.append(j)
        # for each index in fin_procs
        for j in fin_procs:
            # kill process
            procs[i][j].join()
        # for each index in fin_procs
        for j in reversed(fin_procs):
            # remove index from proc list
            del procs[i][j]
        # if row is empty
        if (len(procs[i]) == 0):
            # append index to fin_rows
            fin_rows.append(i)
        # clear fin_procs
        fin_procs.clear()
    # for each index in fin_rows
    for i in reversed(fin_rows):
        # remove row from proc list
        del procs[i]
    
    # if all procs are killed return false
    if (procs == []):
        return False
    # otherwise return true
    else:
        return True


def main():
    # inits unique image counter
    linux_img_count = 1
    # will be a list of lists of process ids
    procs = []
    # create socket with tcp protocol
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        # bind host addr and port to socket
        s.bind((HOST, PORT))
        # infinite loop for input
        while(1):
            # listen for input from socket
            s.listen()
            # when input accept connection
            conn, addr = s.accept()
            with conn:
                print(f"Connected by {addr}")
                # receive 1024 bytes of data from connection, decode it and split on newline
                data = conn.recv(1024).decode().split('\n')
            for c in data:
                # handles case when input is "asdf\n"
                if c == '':
                    continue
                # splits input by space
                command = c.split(' ')
                # gets list of process ids and new unique image counter
                p, linux_img_count = which_input(command, linux_img_count)
                # if user entered exit end program
                if (p == 1):
                    break
                # if user entered a valid command append process to list
                if (p != 0):
                    procs.append(p)
                # for each process id check if process has ended, if so join, otherwise continue
                # removes stopped processes from list


if __name__ == '__main__':
    main()
