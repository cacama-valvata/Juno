#!/bin/bash

#test w/ ./decode_key.sh <base64_encoded_key>
# <base64_encoded_key> refers to the part of the public key without `ssh-rsa` at beginning or `user@hostname` at end

# define the path to the authorized_keys file
AUTH_KEYS_FILE="/home/self_shell/.ssh/authorized_keys.bak"

# define the public key to search for
PUB_KEY=$1

# search the file for the key and print the entire line
grep "$PUBKEY" "$AUTH_KEYS_FILE"


# #########################################
# PROOF OF CONCEPT - TESTING CONTEXTS
#
# An openssh server set up locally.
# sshd_config:
# ```
# AuthorizedKeysCommand /bin/bash -c "/home/casey/Repos/Juno/src-player_client/keygrep.sh %k"
# AuthorizedKeysCommandUser root
# ```
# A target ssh user `self_shell` with 'shellserver.out' shell
# No 'authorized_keys' file for `self_shell`
#
# In 'authorized_keys.bak', a command and a public key on one line, like:
# ```
# command="login appusername" ssh-rsa AAAAB... ...user@hostname
# ```
# 
# Upon login with the appropriate key, you should see:
# ```
# $ ssh -i .ssh/self self_shell@localhost heartbeat
# Hello, appusername.
# here is your heartbeat :D
# ```
# #########################################
