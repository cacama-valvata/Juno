# Success Measures (Solution Evaluation)

## Goals

- An unfamiliar person is able to fully install it by themselves with only written instructions for help. This will be measured by having a member of OSUSEC successfully install the project (sans the hyprevisor) on their laptops. Not only will this measure how easy it is to deploy the software, but how good our documentation is for deployment.
- All parts of the project (sans the hypervisor) can be reasonably installed on a "generic college laptop." This will be measured by running the components on a laptop and then measuring the RAM and CPU usage. The expectation is that it will run at 80% utilization or lower.
- The different components of the project are able to communicate over a network. This will be measured by pinging each box from each other box. Code must be in place for each component to know where the other components are in the network. 
- There are no glaring security vulnerabilities in the software, especially in code relating to the hypervisor. This will be measured by having specific security vulnerability-related tests in the application testing suite, such as testing an input field for buffer overflow capabilities. Yeongjin will assist the team in designing suitable tests, and what vulnerabilities to test for. 
- The environment is reachable through a network (gated by a Wireguard VPN), which requires setting up virtual networks. This will be measured by pinging the virtual machine via an external machine.
- The hypervisor is deployable on x86 processors with VT-x support. This will be measured by attempting to deploy a single, lightweight VM after the hypervisor has been installed on x86 processors with VT-x support (which the development team has at least one of). The VM should be successfully deploy and run.
- The hypervisor can support the most common business and pentesting OS's as VMs. This will be measured by deploying a Windows VM, an Ubuntu VM, and a Kali VM, and checking for generic usability, such as opening a text editor and writing some text. 
- The program can receive and save player-specific or game-specific settings, and these settings are meaningfully implemented on the deployed environment. This will be tested by choosing an arbitrary vulnerability on both Windows and Linux, having the server deploy an environment with that vulnerability present, and then using AtomicRedTeam or a similar tool to test its exploitability on the system. 

## Reach Goals

Additional goals that we would like to see out of the project but aren't strictly necessary for the main goal of the project. We will implement these goals if we find that we have completed our main goals in less time than anticipated.

- The project will have a compononent where a user can use a graphical interface to design environment configs by hand. This will be measured by using the GUI to design a config, deploy that config into an environment, and verify that the config was implemented successfully via Metasploit.
- The project (sans the hypervisor) will be deployable via Kubernetes so that it can scale as the load increases or decreases. This will be measured by designing the project components to deploy on Kubernetes, and then simulating large volumes of traffic sent to the servers. For the hypervisor, it may be able to be deployed in a server cluster. This would require multiple machines to connect together as a cluster and then deploying several environments at once to stress the resources.
- The hypervisor is able to run *any* OS, whether it's standard for business or not. We will measure this by deploying a VM with TempleOS.
- The documentation will include a video tutorial on setting up the software.
- The hypervisor is able to run on AMD processors with AMD-V support. We will measure this by acquiring AMD processors with AMD-V support and testing for successful execution, similar to x86 measurements.
