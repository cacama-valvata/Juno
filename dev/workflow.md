---
title: Development Workflow - Juno

colorlinks: true
linkcolor: Bittersweet
---

# TL;DR:

1. Submit an issue on Github.
2. Assign yourself to an issue.
3. Create a new branch (probably off of main).
4. Pull on your local repo, switch to new branch.
5. Write your changes, commit, push, like normal. 
6. Remember to include new tests, and run your tests locally.
7. Submit a PR on GitHub, include "Closes #n."
8. Have checks pass.
9. Get someone else to review it.
10. Merge the PR into main, profit.

The basic workflow we're following is called [the "Github Flow" model.](https://docs.github.com/en/get-started/quickstart/github-flow) 

\pagebreak

# Is there something you think should be worked on?

Submit it as an issue on Github: [https://github.com/cacama-valvata/Juno/issues](https://github.com/cacama-valvata/Juno/issues)

# Don't have something to do?

We'll split up some tasks to do ("issues" to work on) each week or few weeks. Let me know if you want more to do than that.

Assign yourself to the Issue so that we know you're working on it. Then create a new branch in Github. On your local repo, `git pull` and then you should see your new branch pop up in the output. Switch to it with `git checkout [branch name]`, and then start developing your changes on that branch.

# Working on an Issue?

Pretty straight-forward: write code that works. JK:

It might be more useful to start by writing new tests for the functionality you are implementing or bugs you are fixing. Run these and make sure that they fail. Then start writing code for each atomic test until it passes. If you're unsure about any step in your progress, ask questions of the group. Either its a question we all need to consider before proceeding (an overlooked design question) or someone else will know your answer. 

Once you think all your work is done and is passing your new tests, push it to your branch in the repo and submit a pull request! If multiple people are working on changes that are related, then instead of creating a PR into `main`, one person will create a merge request into the other person's branch, and further testing will be done to ensure that the changes integrate with each other.

# Have work that is ready to be merged into main?

Create a pull request into main with a summary of your changes. Include "Closes #n" in either your body or your PR title, where n is the number of the Issue that your PR resolves. This is automatically tracked by Github, so that when your pull request is merged in to main, the issue is automatically closed as resolved and the two are linked. 

If multiple people are working on changes that are related, then instead of creating a PR into `main`, one person will create a merge request into the other person's branch, and further testing will be done to ensure that the changes integrate with each other.

# See a PR that needs reviewing?

Go review it!! Everyone is able to review code by others, you don't specifically need me to review it. 

Things to look for in the code:

- Cleanliness: no erroneous or "duct-tape and spit" code
- Conformity to the Formatting requirements
- Secure programming: is your code vulnerable to injection or overflow, or other attacks?

Also verify that they did write new tests where applicable as part of the PR.

If the PR doesn't pass the review: write a comment on the PR explaining why it wasn't approved.

# Don't know how to do a given task?

TELL ME. We'll work through it together and get some resources at hand. Otherwise, start Googling :-)
