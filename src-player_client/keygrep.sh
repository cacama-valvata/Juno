#!/bin/bash

# define the path to the authorized_keys file
AUTH_KEYS_FILE="/path/to/authorized_keys"

# define the public key to search for
PUB_KEY="ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQD..."

# search the file for the key and print the entire line
grep "$PUB_KEY" "$AUTH_KEYS_FILE"
