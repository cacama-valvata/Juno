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
  - \fancyhead[L]{\textsl{JUNO - CAPITAL REQUEST}}
  - \fancyhead[R]{\textsl{\leftmark}}

#fontsize: 12pt
---


\begin{titlepage}
  \vspace*{2cm}
  \begin{flushright}
  {\huge
    Juno - Capital Request\\[1cm]
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

```table
---
markdown: True
table-width: 1
width:
  - 0.25
  - 0.1
  - 0.075
  - 0.2
  - D
---
Name of Item,Cost,Source,Alternatives,Justification

Oracle Cloud Infrastructure Credits - `BM.Optimized3.36`,$220,[Link](https://www.oracle.com/cloud/compute/pricing/),Amazon Web Services Credits - `c5n.metal`,"To unify work on our project which includes a hypervisor, we will require access to a central server that provides virtualization capabilities."
```

# Requirements

## Project Requirements

A significant component of Juno is the hypervisor that hosts the attack and defense games; the project is almost non-existent without it. To effectively develop the hypervisor, we need a centralized server in order to test it on. We are utilizing Github Actions (GA) in order to automatically build and test all other components, however it is not sufficient to test a hypervisor. Github Actions encourages an **automatic** and **auditable** process for building and testing code, which is a process we want to preserve across all components of the project. Because of this, we wish to use cloud computing instead of offline, physical computers. As we will demonstrate in the following sections, we believe Oracle Cloud Infrastructure (OCI) would be the best and cheapest option for our needs. 

## Hardware Requirements

Due to the above factors, when choosing a cloud provider and instance type for testing the hypervisor, our biggest hardware requirements are:

- The instance is bare metal, allowing uninhibited virtualization.
- The instance utilizes Intel processors with VT-x capabilities.
- The provider allows us to deploy our own operating systems ("Bring Your Own Image" or BYOI).
- The provider offers an API that allows us to automate deployment in the cloud from GA runners.

# Comparison of Options

```table
---
markdown: True
table-width: 1
width:
  - 0.25
  - 0.2
  - 0.1
  - 0.2
  - D
---
Provider,Bare Metal?,Intel?,BYOI?,GA API?

[Amazon Web Services](https://aws.amazon.com/ec2/instance-types/),On-Demand,Yes,Work-Around,[Yes](https://github.com/marketplace/actions/configure-aws-credentials-action-for-github-actions)

[Google Cloud Platform](https://cloud.google.com/bare-metal/docs/bms-planning),Special Order,Yes,Yes,[Yes](https://github.com/marketplace/actions/set-up-gcloud-cloud-sdk-environment)

[Microsoft Azure](https://learn.microsoft.com/en-us/azure/baremetal-infrastructure/concepts-baremetal-infrastructure-overview),Subscription,Yes,No,[Yes](https://github.com/marketplace/actions/azure-login)

[Oracle Cloud Infra.](https://www.oracle.com/cloud/compute/pricing/#compute-bare-metal),[On-Demand](https://docs.oracle.com/en-us/iaas/Content/Compute/References/computeshapes.htm),Yes,Yes,[Yes](https://github.com/marketplace/actions/run-an-oracle-cloud-infrastructure-oci-cli-command)
```

When comparing our options and our project requirements, our most viable cloud solutions are Amazon Web Services and Oracle Cloud Infrastructure.

\pagebreak

# Breakdown of Cost

## Intended Usage

Our development process will look like the following:

1. The team pushes code to the repository and triggers a build.
2. The GA runner compiles the code to a bootable image.
3. The GA runner creates a new instance in the cloud, then deploys the bootable image to the instance.
4. Once the instance is operating, the GA runner connects to the instance and runs the tests, reporting back the results.
5. Once finished, the GA runner disconnects, and automatically terminates the instance.

While we would primarily develop code on our laptops and allow Github Actions to test for us, we would also use the cloud resources to sanity-check our implementations - atomic testing of code to verify that it will work in the full implementation.

## Cost Demonstration

From our usage, we anticipate that we would spend 4 hours on average each week testing our code (given 1-2 pushes each week that require a build and test), as well as 1 hour on average each week doing sanity checks. This comes to a total of 5 hours of cloud usage each week.

From our Gantt chart, we anticipate being in development from the start of Winter term to week 5 of Spring term, excluding Spring break. In total, this development period consists of 16 weeks. Therefore, we anticipate using a total of **80 hours** of cloud computing over the course of our development.

Below in our calculations, it is important to note that we are assuming **on-demand** pricing. For example, Amazon Web Services offers different levels of enterprise subscription for bare metal instances that are intended for long-lasting, constantly-running servers. We instead plan to use the on-demand, hourly rates for these bare metal instances so that we are only charged for the time that we use it.

**Between OCI and AWS as calculated below, our best solution is the `BM.Optimized3.36` instance for a total of $216.96.**

### Oracle Cloud Infrastructure

Oracle Cloud Infrastructure (OCI) has the following Bare Metal instance types that would fit our needs:

```table
---
markdown: True
table-width: 1
width:
  - 0.25
  - 0.1
  - 0.15
  - 0.15
  - 0.15
  - D
alignment: DCCCCC
---
Instance Type,OCPUs,GB RAM,CPU Price,Mem. Price,Total Price/hr

`BM.Standard3.64`,64,1024,$0.054/hr,$0.0015/hr,$0.0555/hr

`BM.Optimized3.36`,36,512,$0.04/hr,$0.0015/hr,$0.0415/hr
```

Note: The `BM.Standard2.52` is shown as available in the [calculator](https://www.oracle.com/cloud/costestimator.html), however is no longer supported by OCI.

For 80 hours, the total cost of our usage on each instance type is:

```table
---
markdown: True
table-width: 0.5
width:
  - 0.25
  - 0.2
alignment: DC
---
Instance Type,Total Cost

`BM.Standard3.64`,$327.68

`BM.Optimized3.36`,$216.96
```

For our purposes, our best option from OCI is the `BM.Optimized3.36` for $216.96.

**Resources:**

- [Description of Instance Types](https://docs.oracle.com/en-us/iaas/Content/Compute/References/computeshapes.htm)
- [Pricing of Instance Types](https://www.oracle.com/cloud/compute/pricing/#compute-bare-metal)

### Amazon Web Services

Amazon Web Services (AWS) has the following `.metal` instance types that would fit our needs (costs calculated in `us-west-2`):

```table
---
markdown: True
table-width: 1
width:
  - 0.2
  - 0.1
  - 0.15
  - 0.15
alignment: DCCC
---
Instance Type,vCPUs,GiB RAM,Price/hr

`c5n.metal`,72,192,$3.888/hr

`m5zn.metal`,48,192,$3.964/hr

`m5.metal`,96,384,$4.608/hr

`i3.metal`,72,512,$4.992/hr

`m5d.metal`,96,384,$5.424/hr

`m5n.metal`,96,384,$5.712/hr
```

For 80 hours, the total cost of our usage on each instance type is:

```table
---
markdown: True
table-width: 0.4
width:
  - 0.2
  - 0.2
alignment: DC
---
Instance Type,Total Cost

`c5n.metal`,$311.04

`m5zn.metal`,$317.12

`m5.metal`,$368.64

`i3.metal`,$399.36

`m5d.metal`,$433.92

`m5n.metal`,$456.96
```

For our purposes, our best option from AWS is the `c5n.metal` for $311.04.

**Resources:**

- [Description of Instance Types](https://aws.amazon.com/ec2/instance-types/)
- [Pricing of Instance Types](https://aws.amazon.com/ec2/pricing/on-demand/)

\pagebreak

# Management Plan

We're aware that we are asking for a lot, and that the purchased resources couldn't be used by teams after us, like a circuit board could. The resources are also not easily auditable by OSU: we would be receiving a certain number of credits and it's our responsibility to manage our usage of those credits to prevent running out of compute power too early. As such, we are instituting a few automatic control measures in order to manage our usage after receiving the credits.

One of these measures is hosting a script on one of our personal computers that checks OCI every hour and stops any instances that have been running for more than 4 hours. No "build & test" should take longer than 4 hours at maximum, therefore any instance that has been running that long is likely an instance that was created for sanity-checking and does not need to be on continuously. We choose to stop these instances instead of immediately terminating them in case there is code on the instance that needs to be recovered before termination.

We will also design our Github Actions workflow to *not* trigger on every code push but instead on changes made to an arbitrary flag file. It does not matter what the contents of the flag file are, because the intention is that any changes made to it triggers GA to build and test the code. By using a flag file instead of triggering on any push of code, we reduce the number of times that the OCI instances need to be created to only those requested by the development team. When we request that the build should be tested by explicitly changing the flag file, then we know we actually have changes to code that we need to test.

We will also continue to monitor our usage throughout development to ensure that we are staying within our budget of credits. If we are using them too quickly, we will need to reevaluate our workflow and relevant assumptions to reduce how many hours per week we are spending.
