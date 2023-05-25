# Source - Player Client

The Player Client allows the player to automatically connect to their game environment (authenticate with the Identity Server, set up the VPN, view the scoreboard).

### Install (Hosting)
- For any prsopective host looking to run their own version of the software, please not this compontent is not function without the the proper installation of the identity server.
- Running make will generate all requisite files needed for the install process (in the folder entitled build)
- Set up an basic ssh shell server and use the generated build/authlookup file as the auth tool and the generated build/junoshell as the ssh's shell
- If neccesary, modify the sql connect functions to point at the corresponding sql server, the default setting should fine. 
- Assuming the sql server is configured properly and the ssh server is running, the component is good to go. 

### Install  & Usage (Particpating)
- Running make will generate all requisite files needed for the install process (in the folder entitled build)
- Simply running the generated playerclient file with ./playerclient will connect and generate the neccasry configs needed to access the vpn

## Config
- Aside for the exception mentioned in the hosting guide, no further configuration is needed or availible 
