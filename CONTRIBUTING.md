# Contributing to the ArduinoTBB6612FNG library project

First of all, thanks for being reading this file! That means that in some way and in some degree you are considering contributing to this project. Though initially conceived as personal project, any community help if welcome.

This document is divided in several sections, containing different information that can be helful for you when contributing to the project:
- "Ways of collaboration" defines different scenarios of project contribution. It is a good first step if you have an idea of how to collaborate.
- "Github workflow" describes the steps you must follow when working or the project.

# Ways of collaboration

Below you'll find different ways of collaboration sorted by what I consider is more probable collaborations to less probable.

## I want to submit a bug
If you have found a bug, the best way of communicating it is by creating a new discussion in the [Spooky Stuff](https://github.com/VGavara/ArduinoTB6612FNG/discussions/categories/spooky-stuff) category. Take your time to describe it in the best way: fixing a bug is not always easy, and the more information you provide the easier will be. Any kind of additional data (screenshots, videos, ...) will help, though they were not extrictly necessary.

## I want to suggest a new feature
So you have used the library and missed some feature that would be nice to have. In that case feel free of start a discussion in the [Ideas](https://github.com/VGavara/ArduinoTB6612FNG/discussions/categories/ideas) category. Those proposals considered as interesting will be converted into features. Finally they will be programmed to be published in a given release.

## I just have a question
Asking questions is also a way of collaboration: some questions are the inspiration of new features that for sure improve the library. If you have a question, just ask it in the Discussions [Questions & Answers](https://github.com/VGavara/ArduinoTB6612FNG/discussions/categories/questions-answers) category.

## I want to work on a good first issue
Some existing issues are labelled as "good first issue", meaning that they are a good starting point for begin collaborating in the project. If you have identified such a issue, please contact the repository owner to discuss specific details of the issue before starting coding. In case you didn't have chosen an issue, again contact the repository owner for discussing what could be a your good first issue.

## I want to work on a given issue, no matter is a good first one
You're a brave programmer, no doubt. If you want to be helpful for the project, no matter how, the best way is contacting the repository owner to discuss the best available issue for you.

## I want to be involved in a different way
If you think that you can be valuable for this project in a different, not previously described way, feel free to contact with the repository owner (vgavara) in order to expose your idea.

# Github workflow
The repository is a shared resource used by different people concurrently. That means that some rules must exist in order to allow a lovely coexistence between project members, as rules exist for driving a vehicle by the road to help you arrive to your destination as a UDP datagram does (ie, as a single piece).

Some of these rules deal with the worflow, ie, that list or sorted actions that ends with the inclusion of your contribution in the project codebase. The suggested workflow is described below:

1. Once you have picked an [issue](https://github.com/VGavara/ArduinoTB6612FNG/issues) to work with, assign it to you.
2. In the [project Kanban](https://github.com/VGavara/ArduinoTB6612FNG/projects/1), move the issue from "To Do" column to "In Progress".
3. Create a [branch](https://github.com/VGavara/ArduinoTB6612FNG/branches) from the `main` branch and prefix it with "feature-" if it's labelled ad feature or "bug-" if its labelled as bug. Put the issue number after the prefix, so for instance the branch was called "feature-12" if you're working in the issue #12, that it's considered a feature.
4. After working locally on that branch and having committed your **tested** code, create a [pull request](https://github.com/VGavara/ArduinoTB6612FNG/pulls) to submit your work and allow project members to review it. Be sure that the created pull request is addressed to merge your work in the `main` branch.
5. Once your pull request was merged, delete the branch you created in step 3.

To get a more detailed view of the process described above, read [Understanding the GitHub flow](https://guides.github.com/introduction/flow/).
