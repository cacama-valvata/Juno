\pagebreak

# Constraints & Risks

## Time

We anticipate that our project will require a greater than average amount of time to build, due to a few factors. The first factor is the technical level required for the project. While we are utilizing KVM to take care of the weedy details of hardware-assisted virtualization, it still requires familiarity with how to use KVM effectively and low-level knowledge on how hardware and operating systems interact. The second factor is thoroughness: one component of the project is a database of possible vulnerabilities and misconfigurations. How thoroughly we want to include settings per CVE will determine how much time the project requires. In the end, we should expect to include most major, modern vulnerabilities, which will require a lot of time. The third factor is the number of interdependent services being run that need to communicate with each other. This factor introduces greater complexity in the code we must write so that each component can interact with the others.

## Resources

While our project is not necessarily resource-intensive to develop, it does have some *unique* resource needs. 

For 80% of the project, we plan to automatically build and test our code on Github Actions runners. Github provides Actions runners in the form of minutes, and has options for projects to pay for more minutes per month or to use larger runners (2-core default vs 4- or 8-core). However, for public repositories, all Actions minutes used by the project are free. So, this restriction would not apply to us, and we wouldn't require additional resources for this service. Here, our development is only limited by the speed of the runners.

For 80% of the project, Github Actions is sufficient. However, the other 20% of the project is a hypervisor that is intended to be installed and run on bare metal. This can be downright impossible to run and test on Github Actions and most cloud hosting providers, as nested virtualization is often turned off. To be able to test this, we would require either additional hardware (such as an SBC - Small Board Computer) or credits on a cloud hosting provider for bare metal instances. For example, this might be an `m5.metal` instance on AWS.

While either option would work for testing, there are a few additional considerations to keep in mind: automation and auditability. While it is entirely possible to test the hypervisor by having Actions compile the disk image, manually installing this to a partition, and manually booting and running tests, it requires the tests to be run manually and the results from the test to be entered back into Github manually (with the potential for mistakes). This method is not automated, and is also not auditable. One team member cannot independently verify the results that another team member posts. Therefore, we would prefer to use bare metal instances on a cloud hosting provider.

We will submit more detailed calculations, prices, and methodology at a later date, but for a quick cost demonstration, let's assume we would like to use Amazon Web Services (AWS). There are a variety of bare metal [instance options](https://aws.amazon.com/ec2/instance-types/) that utilize Intel processors (in ascending order of cost): `m5zn.metal`, `m5.metal`, `m5n.metal`, and `m6i.metal`. Let's take the lowest cost option on this list for demonstration: the `m5zn.metal` priced at [$3.96 per hour](https://aws.amazon.com/ec2/pricing/on-demand/) of CPU time. The hardware on these instances is much faster than traditional cloud VMs as well, so testing will likely be faster than the Github Actions tests.

In a typical testing cycle, changes to the hypervisor codebase (and *only* changes to the hypervisor) would trigger a Github Actions workflow. The runner would compile the hypervisor into a disk image as defined by the Makefile. It would then use the [AWS CLI tool](https://github.com/marketplace/actions/configure-aws-credentials-action-for-github-actions) to create a bare metal instance on the AWS infrastructure using that disk image. Next, it would connect to the instance over SSH and begin running its tests, with all testing output being sent back to the Github Actions runner. The runner can then verify that the output from the instance matches its expected output, and record these results. The runner can then terminate the AWS instance.

This testing would only be run every one week at most, as it depends on the speed of development. Because bare metal instances are so much faster than traditional VMs and home-use processors, we anticipate that testing would be faster as well. We estimate that it would not take more than 2 hours to run tests on the hypervisor. That would place the total cost at:

$3.96 / hour * 2 hours / week * 4 weeks / month * 6 months of development time = $190.08 overall.

## Scope

The largest constraint would be the intended granularity of the project. In other words, the level to which the infrastructure can be modified to the end users needs. This is likely something that will change over the course of the project. It also acts as a large risk, as an infrastructure that is too dynamic might end up being confusing to utilize, whilst infrastructure that is static, may not accomplish the originally intended goals. 

Scope also comes into play with the second factor mentioned in the time constraint - it isn't feasible to allow settings for every possible CVE in Mitre's database. However, we should expect to include the most major vulnerabilities in the modern field (such as Eternal Blue and Log4Shell).

An additional risk that will likely be encountered during development will be the presence of security vulnerabilities. Due to the fact the stakeholders in this project come from a cybersecurity background and that we anticipate high-level malware on the environment, it will be important to uphold a high standard of security during development. So long as the level is retained, the end product will have a low chance of containing security vulnerabilities.

## Risks

g


