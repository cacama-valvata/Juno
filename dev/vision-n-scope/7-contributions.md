\pagebreak

# Individual Contributions to the Project

## Casey Colley - Project Lead, Primary Point of Communication

### Introduction

By the end of Capstone, I’d like to have worked on and completed a system that takes in settings for the presence of vulnerabilities and outputs virtual machine images that represent an intentionally-vulnerable, interdependent business network. This system is one of the foundational parts of the project, performing most of the work that is necessary to quickly and consistently design networks for Attack and Defense games. This portion of the project is what I personally need for training teams in OSUSEC. 

### User Stories

“As a user, I need a component that will automatically create a vulnerable network of virtual machines for me given some vulnerability settings so that I can get a variety of learning experiences with vulnerabilities.”

“As a user, I need the ability to deploy pre-configured environments instead of creating a new one every time, so that I can practice what I potentially missed on the first experience with the network.”

“As a user, I need the ability to save environment configurations as a constant “image” so that I can deploy them again at a later date.”

“As a developer, I need to be able to keep track of the list of flags per environment, so that I can prove that players in the environment accomplished certain goals to award points.”

### Individual Iteration Plan

Iteration 0:

- Task: Write Python script to receive instructions and send disk images or configuration scripts as appropriate. Write tests accordingly.
- Time required: 1 month, Winter term weeks 1-4


Iteration 1:

- Task: Write a program that receives instructions and sends lists of flags to the Scoreboard. It also sends disk images and lists of flags to the Hypervisor upon receiving instructions. Write tests.
- Time required: 6 weeks, Winter term weeks 5-10


Iteration 2:

- Task: Program also generates and sends config scripts to Hypervisor upon receiving instructions. Write tests.
- Time required: 6 weeks, Winter term Finals Week & Spring term weeks 1-4

Each iteration’s task is dependent on the previous iteration’s work.


## Arian Ghorbani

### Introduction

By the end of the capstone, I would like to have worked on and completed the player identity server, which involves setting up the management of keys and VPN configurations used by players to connect to game environments. I’d like to be able to reference my work on Juno’s config management system on resumes after graduation.

As a written description of the relationships between the given models, the player’s PC can connect to Juno via a web browser that sets up the requirements for the environment that will eventually be used for an Attack and Defense game. A virtual machine will also be run on the PC that connects with the player information server via SSH keys. The player info servers keep track of the requirements set by players and keep track of games, with the help of the environment architect and the game server. The environment architect keeps track of available environments and doles them out as requested by the info servers, while the game server spawns a child process per game that has been started by the players. My work in particular will be with setting up the web app authentication and data tracking of the player info servers.


### User Stories

“As a senior project manager, I need to train my security team on the vulnerabilities inherent to programs run on different platforms and operating systems, so that our project will be more resilient to having security vulnerabilities come up both in-production and once it’s released.”

“As a developer with a focus on security, I want to familiarize myself with security vulnerabilities in various environments I may come across in order to better understand these systems, so that I can broaden my knowledge base for future positions or promotions.”

### Iteration Plan and Estimates

It’s most likely that, in iteration, our team is going to start iteration 0 around the beginning of Winter term by putting together a basic prototype made up mostly of adapted and stitched-together open source work. In that period, we will also be spiking any extra information that we need to adapt that open-source work into what we require. It will likely take 3-4 weeks to complete the prototype, and maybe a bit longer for the spike, since what we decide to spike will depend on what we decide we need to add onto the functionality that the prototype provides. From there, we will each spend 4-6 weeks to work on iteration 1, writing our own versions of a lot of the work in the prototype and expanding the functionality to better fit our requirements, at this point being around Weeks 9/10 of Winter term. By the end of Winter term, we will begin work on iteration 2, which will involve putting together virtual machines and databases to cinch the entire project into its fully realized state by week 3 or 4 of Spring term.


## Carter MacNab

### Introduction

 By the end of Capstone, I'd like to have worked on and completed the player client and scoreboard software necessary for the functionality of our project. I also want to play a role in observing and implementing rigid security rules to ensure our project stays free of potential vulnerability concerns. Developing the player client and focusing on security concerns will allow me to play a role in advising and learning from my fellow teammates during the course of development. 

My focus will be on completing would be the player client and scoreboard. While separate, these two portions of Juno are some of the most important as they are the largest medium from which the players interact with the rest of the system. The player client ensures the player is properly connected and ensures that the images and scoreboard information is sent accordingly. 

### User Stories
“As a user, I need more engaging ways to practice and learn about key cybersecurity concepts so that I can strengthen my skills in attack and defense.” 

“As a developer, I need easy ways to edit the environments served to the players so that I can more focus on tailoring a custom environment for learning rather than deployment.”

“As an educator, I need a quick way to deploy environments that demonstrate key security concepts so that I can more efficiently teach my curriculum.”

### Iteration Plan and Estimates

Iteration 0: (1 month)
 Write SSH shell for sending heartbeats and receiving Wireguard configs. Write tests as component is developed.

Iteration 1: (1 month)
Write program that sends heartbeats and receives Wireguard configs. Upon receiving a config, puts config in appropriate file and instantiates it. Write tests.

Iteration 2: (3 weeks)
Write the scoreboard that polls services and accepts flags. Write tests.

## Alex Marx

placeholder

## Yeongjin Jang - Faculty Advisor

Dr. Yeongjin Jang is the faculty advisor of the project. His primary contribution to the project is to meet weekly with the Project Lead and offer guidance on technical issues, designs, or project timelines. As a professor, Yeongjin has a stake in this project to use it to teach cybersecurity students in his classes, particularly Cyber Attacks and Defenses. Additionally, as the faculty advisor of OSUSEC, he is also interested in using this project to train teams of OSUSEC members for Attack and Defense games.
