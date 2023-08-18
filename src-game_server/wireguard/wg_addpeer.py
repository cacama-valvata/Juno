# Settings you may wish to change
WG_SERV = "wg0"
CONFIG_PATH = "/etc/wireguard"

import configparser
import ipaddress
from base64 import b64encode, b64decode
import os
from sys import argv

# python script [user id] [wg pubkey]


'''
MIT License

Copyright (c) 2019 OSU Security Club

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


https://gitlab.com/osusec/discord-bot/
'''


wgconf_filename = CONFIG_PATH + "/" + WG_SERV + ".conf"
wgpubkey_filename = CONFIG_PATH + "/" + WG_SERV + ".pub"
wgtempl_filename = CONFIG_PATH + "/" + WG_SERV + "_conn.template"
routing_filename = CONFIG_PATH + "/routing.info"
'''
. /etc/wireguard/
|_ > wg0.conf
|_ > wg0.pub
|_ > wg0_conn.template
|_ > routing.info
'''

nextpeer_userid = argv[1]
nextpeer_key = argv[2]

with open (routing_filename, mode='r', encoding="utf-8") as rtf:
    routing = rtf.read().splitlines ()
self_ip = routing[0]
self_port = routing[1]

with open (wgconf_filename, mode='r', encoding="utf-8") as wgc:
    wg_config = wgc.read().splitlines()
wg_config.append("")


'''

    FUNCTIONS

'''

def is_validkey (key_string):
    key_bytes = bytes (key_string, "utf-8")
    if b64encode (b64decode (key_bytes)) == key_bytes:
        if len (b64decode (key_bytes)) == 32:
            return True
    
    return False


def is_userpresent ():
    for line in wg_config:
        if line == f"# {nextpeer_userid}":
            return wg_config.index (line)
    
    return -1


def add_newkey ():
    try:
        end_interface = wg_config.index ("[Peer]")
        interface_conf = wg_config[:end_interface]
    except ValueError:
        interface_conf = wg_config.copy()
    
    interface_parser = configparser.ConfigParser ()
    interface_parser.read_string ("\n".join (interface_conf))

    # CIDR notation: 10.0.0.0/24
    interface_ip = interface_parser["Interface"]["Address"]

    try:
        tempcopy = wg_config.copy()
        tempcopy.reverse()
        lastpeer_idx = tempcopy.index ("[Peer]")
    # First [Peer] added to file
    except ValueError:
        lastpeer_ip = ipaddress.ip_network (interface_ip)
        #print ("Implied last peer from interface address")
    else:
        lastpeer_config = tempcopy[:lastpeer_idx + 1]
        lastpeer_config.reverse()

        lastpeer_parser = configparser.ConfigParser()
        lastpeer_parser.read_string ("\n".join (lastpeer_config))

        lastpeer_conf = lastpeer_parser["Peer"]["AllowedIPs"]
        lastpeer_ip = ipaddress.ip_network (lastpeer_conf)

    if not (lastpeer_ip.network_address + 1) in ipaddress.ip_network (interface_ip):
        #print ("All IPs in range taken.")
        exit ()

    nextpeer_ip = lastpeer_ip.network_address + 1

    new_conf_entry = "\n".join (
        [
            "",
            f"# {nextpeer_userid}",
            "[Peer]",
            "Endpoint = 0.0.0.0:51820",
            f"AllowedIPs = {nextpeer_ip}/32",
            f"PublicKey = {nextpeer_key}",
            "\n",
        ]
    )

    # TODO: how to prevent race condition on write
    with open (wgconf_filename, mode='a', encoding="utf-8") as wgc:
        wgc.write (new_conf_entry)

    os.system ('systemctl restart wg-quick@wg0')

    return nextpeer_ip


def update_key (line_no):
    for i in range (line_no, line_no + 5):
        if wg_config[i].startswith ("PublicKey"):
            wg_config[i] = f"PublicKey = {nextpeer_key}"
            break

    with open (wgconf_filename, mode='w', encoding="utf-8") as wgc:
        wgc.write ("\n".join (wg_config))

    os.system ('systemctl restart wg-quick@wg0')

    peer_parser = configparser.ConfigParser ()
    peer_parser.read_string ("\n".join (wg_config[line_no:line_no + 5]))
    nextpeer_ip = peer_parser["Peer"]["AllowedIPs"].split("/")[0]

    return nextpeer_ip


def print_conn (peer_ip):
    with open (wgtempl_filename, mode='r', encoding="utf-8") as wgt:
        conn_conf = wgt.read()

    with open (wgpubkey_filename, mode='r', encoding="utf-8") as wgp:
        wgpubkey = wgp.read().strip()

    conn_conf = conn_conf.replace ("<peer id here>", str (peer_ip))
    conn_conf = conn_conf.replace ("<self pubkey here>", wgpubkey)
    conn_conf = conn_conf.replace ("<self ip>", self_ip)
    conn_conf = conn_conf.replace ("<self port>", self_port)

    print (conn_conf)



'''

    MAIN

'''


line_no = is_userpresent ()
if line_no < 0:
    peer_ip = add_newkey ()
else:
    peer_ip = update_key (line_no)

# At any point it can fail and nothing will be printed
print_conn (peer_ip)
