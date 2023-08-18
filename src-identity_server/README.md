# Source - Identity Server

The Identity Server manages the keys and VPN configurations that the players use to connect to the game environment, as well as organizing private rooms for different players to match up for games.

source, makefiles, etc here

# Setting Up Server

Included is a bash script `setup.sh`. Be sure to have python3, pip, pyvenv, and docker installed, as well as giving your user the `docker` group. Then, run `./setup.sh`. After it has completed, you should see output referring to generating a new Django server token. Then, you can run `python3 manage.py runserver` to deploy it.

Be sure to change the DEBUG_MODE in JunoIAM/settings.py and add the accessible IP to the ALLOWED_HOSTS list.

