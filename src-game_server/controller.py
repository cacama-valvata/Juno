import os
import multiprocessing as mp

# gets user input
def get_input():
    usr_in = input("Enter command: ")
    return usr_in

# parses the command entered and jumps to diff function depending on input
def which_input(command, linux_img_count):
    match command[0]:
        case 'make':
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
        case 'exit':
            return 1, linux_img_count

        case _:
            print('Error: Invalid command')
            return 0, linux_img_count

# function called by creating new process, create vm with qemu
def start_linux_vm(img_name):
    os.system('qemu-system-i386 -hda ' + img_name + ' -cdrom FD13LIVE.iso -m 16M -boot order=dc')
    #print('qemu-system-i386 -hda ' + img_name + ' -cdrom FD13LIVE.iso -m 16M -boot order=dc')

# creates disks and process for vms
def linux_vm(num_vm, linux_img_count):
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
        # creates process with start_linux_vm func, passes in disk name
        p = mp.Process(target=start_linux_vm, args=(filename_arr[i],))
        # appends process id to arr
        procs.append(p)
        # starts process
        p.start()

    return procs, count

# to be implemented later
def windows_vm(num_vm):
    for i in range(num_vm):
        print('creating windows vm ' + str(i + 1))

def main():
    # inits unique image counter
    linux_img_count = 1
    # will be a list of lists of process ids
    procs = []
    # infinite loop for input
    while(1):
        # splits input by space
        command = get_input().split(' ')
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
        for i in range(len(procs)):
            for j in range(len(procs[i])):
                if (procs[i][j].is_alive()):
                    continue
                else:
                    print('process ' + str(procs[i][j]) + ' shut down')
                    procs[i][j].join()
                    del procs[i][j]
                    break
            if (len(procs[i]) == 0):
                del procs[i]
                break


if __name__ == '__main__':
    main()
