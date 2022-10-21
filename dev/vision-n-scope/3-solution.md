# Vision Statement (Solution)

By the time this project is complete, it will bring value to stakeholders by providing an educational platform for use in both self-teaching and classroom settings. With this environment, students and cybersecurity learners (up to a professional level) will be able to experiment in a sandbox of both building and testing Attack and Defense systems while being assisted along the way with the difficulties of doing so. Whereas beforehand, deployment of cybersecurity Attack and Defense exercises would take significant amounts of time and effort on the part of the exercise designer, this project will make setting up these environments much more viable.

## Growth Hypothesis

Given the fact that we, as a group, have natural access to several OSU communities deeply tied to cybersecurity, namely the OSU Security Club, a seed of growth for this project’s audience would be that very club. Since it’s difficult to set up Attack & Defense games for cybersecurity students to use in order to learn, having a tool such as this available to OSU students and being able to use it in such an applicable setting is a highly effective system for growing our project’s userbase. From there, the project could spread across the cybersecurity community at OSU as a whole, and perhaps even to other educational institutions. Professors in OSU and beyond could use this tool to assist in the curriculum development of cybersecurity courses in the future.

## Value Hypothesis

Juno aims to reduce the barrier to entry into cybersecurity games by automating the creation/design of vulnerable networks and deploying these on demand. Juno will be a successful program when cybersecurity students and academic organizations can leverage the tool to host Attack & Defense games for classes and competition practices. The users will be capable of hosting games up to an hour in advance; We will know that Juno is valuable when users are able to utilize the program to host weekly Attack & Defense games, leveraging its features for educational opportunities and experiences.

## Requirements

### Functional

- The hypervisor should successfully load any given OS
- The program should successfully cause changes in the designed environment based on user-chosen settings
- The program should alert the user to successful environment creation once the environment has been created
- Automatically design vulnerable, interdependent VMs in a business-network context
- Deploy these networks on-demand on a self-hosted hypervisor
- Control game access to only the players who requested that game
- Poll services over the network to score the team and track overall scores

### Non-Functional

- Can deploy a network and get players able to use it within the space of an hour
- Can correctly save user specifications and load them into a new network in a deterministic/consistent manner