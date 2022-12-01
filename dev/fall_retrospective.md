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

By the end of Fall term, the team planned to identify and write out project requirements, security needs, and potential risks, as well as draw up a technical design and project timeline. Success for this goal is measured by having the following items completed and available:

- Vision and Scope document, outlining:
  - Project needs
  - Potential risks during development
  - Workflow plan for ensuring a high level of security
- Gantt chart with:
  - Decomposed tasks per project component
  - Team members assigned to each task
  - Estimated start time and time required for completion of each task
- Technical design drawing

# Progress

This fall, the development team succeeded in their goals of identifying requirements and risks, creating a project timeline, and drawing a technical design of the project. Our deliverables include the Vision and Scope document, a Gantt chart outlining tasks and estimated dates of completion for each iteration, and a project design. The design will need to undergo some revisions in response to the team's Security Design Review, however the initial project design is finished and available for presentation.

# Risks and Mitigation

The biggest risks the project faces include the presence of security vulnerabilities, too granular of a project scope, and too complex of a project deliverable. 

The project is intended for cybersecurity students and professors, therefore a high level of security is expected from the project and required for the system to ensure safe functioning of itself and of the network it is hosted in. While the system may be hosting malicious behavior in the hypervisor, that behavior should not be able to compromise anything outside of that context. Because our intended audience includes cybersecurity professionals, the presence of any security vulnerabilities in the system will be exploited and may compromise the system. In response to this possibility, the team has developed workflow processes to prevent security vulnerabilities in the code, including writing automated security tests, conducting code reviews on every pull request, and collaborating with another capstone team to hunt for vulnerabilities via traditional penetration testing methods.

Additionally, one aspect of the project is the ability to pass in settings to configure the randomly generated environments. A design question that the development team needs to address is how granular of settings the system should offer to the user. Should the user be able to request the presence of a specific CVE, or only broad classes of vulnerabilities? Additionally, should the user be able to request vulnerabilities with certain difficulty levels? If the settings are *too* granular, the project may not be completed in time, but if the settings are not granular *enough*, they may not be helpful to users. To mitigate this risk, we plan to incorporate plugin support into the environment architect so that users can write their own misconfiguration scripts for the vulnerabilities that they want to include. That way, we can offer very granular settings to the user without needing to also write granular code to support it.

Lastly, the project's chief userbase are members of OSUSEC: they should be able to deploy, configure, and run the system with very little technical assistance from us. However, if the project is too complex, then they will not be able to easily do this. This risk comes from the fact that the system is composed of 4 distinct servers that need to be able to see each other and communicate, instead of installing just one server on a favorite Linux distribution. In order to eliminate this risk, the team plans to write thorough documentation on installation and the various interfaces exposed to the user, as well as ensuring that the interfaces (i.e. the `help` menu) are detailed and human readable. For example, one aspect of the project is installing a Type-1 hypervisor onto bare metal. This entails creating bootable media of the hypervisor image, booting to it in the BIOS and bootloader menu of the server, then what? Therefore, the team will also include an install script in the image that the user can then run to automatically copy the hypervisor image onto persistent disk. This is the standard way that you would install an operating system, so including this support for the user is critical to avoid uneccessary complexity in an already complex system.

# Project Timeline

- someone draw a bare bones chart of this based on the gantt chart
- only winter and spring term
- summarize the tasks into the component "hypervisor", etc
- put chart in /images folder and embed here
