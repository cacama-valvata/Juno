#!/usr/bin/python
import json
file = open("./settings.json", "r")
#print(json.dumps(filedata)) #test line
parsed = json.load(file)

scriptwrapper = open("./scriptwrapper.txt", 'w')
for x in parsed['vuln']:
    scriptwrapper.write(x + "\n")
    #print(x)
scriptwrapper.close()

image = open("image.txt", 'w')
image.write(parsed['image'] + "\n")
image.close()
