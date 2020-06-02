# Using Gulp (task-runner) with Browserify (module-bundler)

An old school (pre-webpack) but relevant option.

npm scripts

```
"gulp-prod": "node_modules/.bin/gulp prod",
"gulp-dev": "node_modules/.bin/gulp dev"

```

download a bunch of devDependencies

```
const gulp = require('gulp');
const source = require('vinyl-source-stream');
const browserify = require('browserify');
const watchify = require('watchify');
const babelify = require('babelify');
const sassify = require('sassify');
const nodemon = require('gulp-nodemon');
const buffer = require('vinyl-buffer');
const uglify = require('gulp-uglify');
const path = require('path');

const sourceFile = path.join(__dirname, '/client/index.js');
const destFile = 'browserify-bundle.js';
const destFolder = path.join(__dirname, 'build');

gulp.task('prod', () => {
  return browserify(sourceFile)
    .transform(
      babelify.configure({
        presets: ['@babel/preset-env', '@babel/preset-react'],
      })
    )
    .transform(sassify)
    .bundle()
    .pipe(source(destFile))
    .pipe(buffer())
    .pipe(uglify())
    .pipe(gulp.dest(destFolder));
});

```
