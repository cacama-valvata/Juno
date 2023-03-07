import os

def get_input():
    usr_in = input("Enter command: ")
    return usr_in

def which_input(command):
    if (command[0] == 'make'):
        match command[1]:
            case 'linux':
                linux_vm(int(command[2]))
            
            case 'windows':
                windows_vm(int(command[2]))

            case _:
                print("Error: Invalid command")
    else:
        print("Error: Invalid command")

def linux_vm(num_vm):
    for i in range(num_vm):
        print('creating linux vm ' + str(i + 1))

def windows_vm(num_vm):
    for i in range(num_vm):
        print('creating windows vm ' + str(i + 1))

def main():
    command = get_input().split(' ')

    which_input(command)


if __name__ == '__main__':
    main()
