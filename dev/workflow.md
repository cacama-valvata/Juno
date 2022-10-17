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

\pagebreak

# Is there something you think should be worked on?

Submit it as an issue on Github: [https://github.com/cacama-valvata/Juno/issues](https://github.com/cacama-valvata/Juno/issues)

# Don't have something to do?

We'll split up some tasks to do ("issues" to work on) each week or few weeks. Let me know if you want more to do than that.

# Have something you are doing?

Create a branch off of `main` for your changes, do your development on that. You'll likely need to write additional tests in Actions for your changes. Create a pull request, I will review it and merge it into `main`. If multiple people are working on changes that are related, then instead of creating a PR into `main`, one person will create a merge request into the other person's branch, and further testing will be done to ensure that the changes integrate with each other.

This is super simple, called [the "Github Flow" model.](https://docs.github.com/en/get-started/quickstart/github-flow) 

# Don't know how to do a given task?

TELL ME. We'll work through it together and get some resources at hand. Otherwise, start Googling :-)
