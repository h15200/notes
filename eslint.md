Wrote scripts for these in the PATH!

Use either of these!
h-eslint-node
h-eslint-browser

# BACK END (Simpler setup!)

Start project,

npm init
npm i --save-dev eslint eslint-config-airbnb

Touch .eslintrc.js,
put in .gitignore

Start with

```
module.exports = {
  "extends": "airbnb-base" ,
  "rules": {
    "arrow-parens": [
      "error", "as-needed"
    ],
    "comma-dangle": 0,
    "no-console": 1,
    "no-multiple-empty-lines": 0,
    "semi": 0,
    "no-unused-vars": [
      "error",
      {
        "vars": "local",
        "args": "none"
      }
    ],
    "quotes": 0,
  }
}
```

# Eslint FRONT END!

    Start project,

```npm init -y
npm i --save-dev eslint eslint-config-airbnb eslint-plugin-html eslint-plugin-import eslint-plugin-jsx-a11y eslint-plugin-react eslint-plugin-react-hooks

touch .eslintrc.js
Put in .gitignore
```

```
module.exports = {
  "extends": [
    "airbnb-base",
    "plugin:react/recommended"
  ],
  "parserOptions": {
    "ecmaFeatures":{
      "jsx": true
    }
  },
  "rules": {
    "arrow-parens": [
      "error", "as-needed"
    ],
    "comma-dangle": 0,
    "no-console": 1,
    "quotes": 0,
    "no-multiple-empty-lines": 0,
    "semi": 0,
    "no-unused-vars": [
      "error",
      {
        "vars": "local",
        "args": "none"
      }
    ]
  },
  "env": {
    "browser": true
  },
}
```
