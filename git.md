If you've forgotten to add .gitignore with `node_modules` and have pushed already,

make a gitignore, add `node_modules` as well as `node_modules/` if you have sub projects

then to remove the current repo with modules,
`git rm -r --cached node_modules`
