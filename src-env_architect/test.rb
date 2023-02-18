#!/usr/bin/ruby
require 'json'

#read and parse settings.json
file = File.read('./settings.json')
document = JSON.parse(file)

#TODO: support for multiple VMs being asked for to support an entire network

#output the script w/ functions
#STEPS: Look for all listed scripts, throw all their functions into a wrapper script, and output that wrapper script with a text file containing the name of the machine image

#TODO: this should be scriptwrapper.sh
wrapper = File.open("scriptwrapper.txt", 'w')
for x in document['vuln'] do
    wrapper << x[1] + "\n"
end
wrapper.close

#Now, output textfile with name of machine image
image = File.open("image.txt", 'w')

image << document['image'] + "\n"

image.close
#print document
