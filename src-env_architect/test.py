#!/usr/bin/python
import json
file = open("./settings.json", "r")
parsed = json.load(file)

scriptwrapper = open("./scriptwrapper.txt", 'w')
for x in parsed['vuln']:
    scriptwrapper.write(x + "\n")
    #print(x)
scriptwrapper.close()

image = open("image.txt", 'w')
image.write(parsed['image'] + "\n")
image.close()

# -2 iteration pseudocode
# import mysql.connector
# mydb = mysql.connector.connect(
#    host="localhost",
#    user="username",
#    password="password",
#    database="database"
# )
# mycursor = mydb.cursor()
# mycursor.execute("SELECT scriptname, dirpath FROM scripts WHERE dirpath = $DIRPATH")
# scripts = mycursor.fetchall()
# #for x in scripts:
# # print(x)
#
# mycursor.execute("SELECT imagename, dirpath FROM images WHERE dirpath = $DIRPATH")
# images = mycursor.fetchall()
# #for x in images:
# # print(x)
# 
# for script in scripts, write the name of the script at dirpath to settings.json
# for image in images, write the name of the script at dirpath to settings.json
# 
