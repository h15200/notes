# git

# commands

See if the machine has git on terminal  
 `git --version`

Create a repository on github

Clone repository on terminal  
 `git clone http://blablabla` (that you got through the repository on github)

    OR  start with the local computer, and make an empty repo
    git init

On terminal have the git keep track of the working file
`git add foo.html` // this tells the computer to keep track of this file from now on.

To save to a server (not yet on github) needs -m
`git commit -m “Message to yourself about this particular save. “`

`git commit -am "message"`
add AND commit at the same time with message

To check if you are updated in the repository (will work on whatever file you have used ‘git add’)
`git status`

To take the code from computer to github (again, the file that is under ‘git add’)
`git push`

To take the code from github to local computer
`git pull`

If the repository and local codes are different and you try to git push/pull, you’ll need to merge conflict by picking the version you want to keep

To see the history of commits
`git log`

To go back one commit
`git checkout HEAD “filename”`

If you’ve added multiple files to the staging area and you want to remove one of them
`git reset HEAD “filename”`

To see other “branches”
`git branch`

To create new branch but stay in master
`git branch “newbranchname”`

To create another branch from the master AND go to the new branch
`git checkout -b “name of new branch”`

To switch branches
`git checkout “name of branch”`

To delete branch
`git branch -d “branchname”`

To merge branches
If you want to add a “feature” branch to your master branch, first switch to master by git checkout master, then type
`git merge feature`

To push a new branch from console
`git push--set-upstream origin “name of new branch”`

## Backtrackign when you forgot .gitignore

If you've forgotten to add .gitignore with `node_modules` and have pushed already,

make a gitignore, add `node_modules` as well as `node_modules/` if you have sub projects

then to remove the current repo with modules,
`git rm -r --cached node_modules`

## Going back!

ABSOLUTELY make sure that you want to go back, as the current code will be deleted completely!

To go back to an older version of commit
`git reset --hard “commithash”` (the hash for that particular commit)

## Working with collaborators

You can work collaboratively on your own public repos or even on other public repos where you don't have push (write) access. Even with read-only access, you can make pull requests.

A git master creates a public repo, adds collaborators

At the top level (upstream), pull requests are reviewed and merged.

TWO ways of setting up GitHub for teams

1. Organizations - account owner creates many teams with differing permission level for various repos

2) Collaborators - Repo owner (git master) can add collaborators with read only or read and write access.
   (git master should be a different person from the scrum master) Everyone except the git master should have read-ONLY access.

TWO models of pull requests

1. Fork & Pull Model - used in public repos where we don't have write access
2. Private

Use Fork & Pull with Organization

1.  Set up organization
2.  Set up public repo (git master makes a clone of the organization level repo)
3.  Make boilerplate file structure
4.  Everybody FORKS (not clone!) this public repo (even as the git master) and clone
5.  git master must take care never to work directly on the organization level repo!
6.  Everybody makes an upstream to the organization level to make pull requests.
7.  Make feature branches

Never write on master branch. Not even on your forked repo. Create feature branches and review and merge
`git checkout -b [new-feature]`
add and commit,
`git remove -v` see what the remote is
`git push origin [new-feature]` -> push to your forked repo
Then make a PR to the ORGANIZATION LEVEL master (never your own master to your own branch)

`git pull upstream master`, then `git push origin master` to update your own master.
`git merge master` inside branch will update the base of the branch

### PR

- problem you were solving
- your solution
- any notes on testing
- screenshots of working solution

The reviewer (git master or the whole team) will review the PR and merge if approved.

Best practice to set protections on the master branch
github - settings - master - organization level add some rules.
