#!/bin/bash

#test w/ ./decode_key.sh <base64_encoded_key>
key=$1
decoded_key=$(echo $key | base64 --decode)
echo $decoded_key
