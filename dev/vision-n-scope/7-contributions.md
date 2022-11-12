\pagebreak

# Individual Contributions to the Project

## Casey Colley - Project Lead, Primary Point of Communication

placeholder

## Arian Ghorbani

placeholder

## Carter MacNab

placeholder

## Alex Marx

### Introduction

By the end of Capstone, I'd like to have worked on and completed the game server which deals with taking in requests for new games and then spawning virtual machines per the instructions. I would like to refer to the low level work I have done on the game server with creating hypervisors and other such tools on my resume.

### System Architecture

Figure 1:
This is a system where these 5 parts will come together to be able to automatically create and deploy virtual networks of virtual machines for people to practice attacking and defending them. The user can log into the player info server from which they can do a number of things related to competitions such as joining teams or scheduling games. The player info server communicates with the environment architect and the game server to start deploying the required virtual machines with the required settings. The environment architect stores a number of images and vulnerability configurations which it sends as required to the game server so it can deploy the correct virtual machines. The game server creates the virtual machines and sends them to the individual users depending on what they need, whether it be a network of devices or just a specific one.

Figure 2:
My part specifically is the game server. The parent (main) process running on the server takes in requests for virtual machines that need to be created. It then spawns a child process for each virtual machine needed, which uses KVM and the specified images and configs from the environment architect to create them. It then sends the virtual machines back out to the internet so that the users can access them while communicating with the player info server to manage the VPN configs.

### User Stories

User Story 1:
"As a user, I need a way to create virtual machines with a variety of specified vulnerabilities so I can practice attacking and patching them."

User Story 2:
"As a user, I need to automate the creating of virtual machines so I don't need in depth knowledge on how to set them up."

### Iteration Plan and Estimates

Iteration 0:
- Task: Write Python script as wrapper for QEMU and write tests accordingly.
- Time: 4 Weeks, Winter Term Weeks 1-4

Iteration 1:
- Task: Write parent process that will reveive instructions and create child processes for virtual environments accordingly. Write tests.
- Time: 6 weeks, Winter Term Weeks 5-10

Iteration 2:
- Task: Write virtual serial console and appropriate tests.
- Time: 3 weeks, Winter Term finals week and Spring Term Weeks 1-2

## Yeongjin Jang - Faculty Advisor

placeholder
