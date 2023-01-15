#!/bin/bash

#test w/ ./decode_key.sh <base64_encoded_key>
# <base64_encoded_key> refers to the part of the public key without `ssh-rsa` at beginning or `user@hostname` at end

# define the path to the authorized_keys file
AUTH_KEYS_FILE="/home/self_shell/.ssh/authorized_keys.bak"

# define the public key to search for
PUB_KEY=$1

# search the file for the key and print the entire line
grep "$PUBKEY" "$AUTH_KEYS_FILE"
