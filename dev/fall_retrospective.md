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

- what we got done this term

# Risks and Mitigation

- yeah

# Project Timeline

- someone draw a bare bones chart of this based on the gantt chart
- only winter and spring term
- summarize the tasks into the component "hypervisor", etc
- put chart in /images folder and embed here
