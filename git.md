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

To go back to an older version of commit
`git reset --hard “commithash”` (the hash for that particular commit)

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
