# Source - Game Server

The Game Server includes the hypervisor itself and the game controller which sets up the networks, instantiates the machines, and mitigates player access.

source, makefiles, etc here

### Install
- First you have to install python 3 on your machine. I would recommend 3.10 or higher as that is what this was built on.
- Next run `python3 qemu_install.py` to install the necessary packages to run qemu.
- Edit the controller.py file and change the `HOST` variable under the import statements to the ip of the computer that your environment architect is running on.
- Edit the controller.py file and change the `PORT` variable under the import statements to whatever port you want the Player Info Server to communicate to the Game Server on.
- After that all you have to do is run `python3 controller.py` to start up the game server.
