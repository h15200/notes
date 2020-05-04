VS Code plugin - live sass compiler

In settings format json
Add this (to specify save path for that project)

“liveSassCompile.settings.formats”: [
{
“format”: “expanded”,
“extensionName”: “.css”,
“savePath”: “/public/min.css” // or possibly not min.
}
]

Make new project, make public, index.html,

 <link rel=”stylesheet” href=”./css/main.css”>

Make a scss dir in the project dir,
Inside, main.scss

Then on bottom of vs code, you should see Watch Sass. Click on it and it should compile a css automatically

File structure:

In the front end dir
Scss
Style.scss (compiles to .public/css/style.min.css or .dist/css/style)
\_config.scss - Variables, functions, mixins,
\_utilities.scss - Generic styles of containers, typography, backgrounds using functions and variables. Bootstrap-like premade classes for size, padding, margin, colors
\_small.scss - Maybe a media query for small screens

    These _ files will be @import  to the style.scss. Media queries will be imported on bottom of file
