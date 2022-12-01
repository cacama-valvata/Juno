---
# do not include title, author
# hardcoded in title page

numbersections: true
colorlinks: true
linkcolor: Bittersweet
# dont specify toc
# generated in 0-titlepage.md

header-includes:
  - \usepackage{pdfpages}
  - \usepackage{fancyhdr}
  - \pagestyle{fancy}
  - \fancyhead[L]{\textsl{JUNO - FALL RETROSPECTIVE}}
  - \fancyhead[R]{\textsl{\leftmark}}

#fontsize: 12pt
---


\begin{titlepage}
  \vspace*{2cm}
  \begin{flushright}
  {\huge
    Juno - Fall Retrospective\\[1cm]
  }
  \end{flushright}

  \begin{flushleft}
    \vspace*{0.5cm}
    Advisor: Yeongjin Jang
  \end{flushleft}
  
  \begin{flushright}
  Casey Colley \\
  \vspace*{0.5cm}
  Arian Ghorbani \\
  \vspace*{0.5cm}
  Carter MacNab \\
  \vspace*{0.5cm}
  Alex Marx \\

  \end{flushright}

  \vspace{2 in}

  \begin{flushleft}
    \tableofcontents
  \end{flushleft}

\end{titlepage}

\pagebreak


# Overview

This fall, the development team proposed Juno - a framework for automatically designing and deploying practice networks for security attack and defense games. The project aims to reduce the barrier to entry into cybersecurity games. By automating environment creation, players can spend more time studying and practicing penetration testing and incident response.

This document serves as an executive summary over the goals and current progress of the Juno development team, as well as expected progress over the next several months.

# Goals

By the end of Spring term, the development team plans to have a working system consisting of a KVM-based hypervisor, an environment-creation server, a web-based identity management server, and a player client. Success is measured if these assets can be deployed relatively easily by OSUSEC members, then used to host attack and defense games in a timely manner for team training.

By the end of Fall term, the team planned to identify and write out project requirements, security needs, and potential risks, as well as draw up a technical design and project timeline. Success for this goal is measured by having these items completed and available.

# Progress

This fall, the development team succeeded in their goals of identifying requirements and risks, creating a project timeline, and drawing a technical design of the project. Our deliverables include the Vision and Scope document, a Gantt chart with decomposed tasks and estimated dates for each iteration, and a project design. The design will need to undergo some revisions in response to the team's Security Design Review, however the initial project design is finished and available for presentation.

# Risks and Mitigation

The biggest risks the project faces include the presence of security vulnerabilities, too granular of a project scope, and too complex of a project deliverable. 

A high level of security is expected from the project. Because our intended audience includes cybersecurity professionals, the presence of any security vulnerabilities in the system will be exploited. In response to this possibility, the team has developed workflow processes to prevent security vulnerabilities in the code, including writing automated security tests, conducting code reviews on every pull request, and collaborating with another capstone team to hunt for vulnerabilities via traditional penetration testing methods.

Additionally, one aspect of the project is the ability to pass in settings to configure the randomly generated environments - how granular of settings should the system offer the user? If the settings are *too* granular, the project may not be completed in time, but if the settings are not granular *enough*, they may not be helpful to users. To mitigate this risk, we plan to incorporate plugin support into the environment architect so that users can write their own misconfiguration scripts for the vulnerabilities that they want to include. That way, we can offer very granular settings to the user without needing to also write granular code to support it.

Lastly, the project's chief userbase are members of OSUSEC: they should be able to deploy, configure, and run the system with very little technical assistance from the team. The system is already complex enough: instead of installing just one server on a favorite Linux distribution, it is composed of four distinct servers that need to work together. In order to eliminate this risk, the team plans to write thorough documentation and detailed, human-readable interfaces (i.e. the `help` menu). 

\pagebreak

# Project Timeline

```table
---
table-width: 1
markdown: True
width:
  - 0.2
  - 0.2
  - D
alignment: CCD
---
Iteration,Completion Date,Summary

Planning,December 2nd,"Write Vision and Scope document, lay out project timeline, and draw the project design."

Iteration 0,February 3rd,"Build mockup of system out of pre-built components wrapped in python scripts. The SSH shell part of the player client is built from scratch instead of out of pre-built components."

Iteration 1,March 17th,"Incrementally replace components from Iteration 0 with self-written ones. Hypervisor: parent process that dispatches to QEMU. Identity Server: interfaces with other components. Env Architect: interfaces that receives instructions and sends back disk images. Player Client: write client daemon that instantiates VPN configs received from SSH shell."

Iteration 2,April 28th,"Incrementally replace components from Iteration 0 with self-written ones. Hypervisor: hardware emulation, replace QEMU. Identity Server: website backend and service-polling scoreboard. Env Architect: generates and sends config scripts."

Expo Prep,June 9th,"Design poster and prepare a live demo for expo."
```
