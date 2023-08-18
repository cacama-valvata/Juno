# Source - Game Server

The Game Server includes the hypervisor itself and the game controller which sets up the networks, instantiates the machines, and mitigates player access.

source, makefiles, etc here

### Install
- First you have to install python 3 on your machine. I would recommend 3.10 or higher as that is what this was built on.
- Next run `python3 qemu_install.py` to install the necessary packages to run qemu.

### Config
- Edit the `controller_conf` file to match your setup
- The `HOST` value should be set as the IP addr of the device the Game Server is running on.
- The `PORT` value should be set as whatever port you want the Game Server to listen on for commands from the Player Info Server
- The `ENVARCH` value should be set as the IP of the Environment Architect
- The `ENVARCHUSER` value should be set as the username of the user under which all the files for the Environment Architect is stored

### Running
- Just run `python3 controller.py` to start up the game server.
