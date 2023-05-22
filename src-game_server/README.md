# Source - Game Server

The Game Server includes the hypervisor itself and the game controller which sets up the networks, instantiates the machines, and mitigates player access.

source, makefiles, etc here

### Install
First you have to install python 3 on your machine. I would recommend 3.10 or higher as that is what this was built on.
Next run `python3 qemu_install.py` to install the necessary packages to run qemu.
After that all you have to do is run `python3 controller.py` to start up the game server.
