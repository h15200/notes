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
`_config.scss` - Variables, functions, mixins,
`_utilities.scss` - Generic styles of containers, typography, backgrounds using functions and variables. Bootstrap-like premade classes for size, padding, margin, colors
`_small.scss` - Maybe a media query for small screens

    These _ files will be @import  to the style.scss. Media queries will be imported on bottom of file

## Sass/Less Tech Talk

### What is Sass/Less, css pre-processors vs css libararies

css Pre-processors vs css libararies
They are different technologies, but often grouped together as options when deciding how to style a site.

Check to see if they both compile to css.

Analogy - if we're comparing styling to preparing a beautiful dinner, regular css would be cooking dinner. Libraries would be closer to ordering in, and plating what you order and setting the table.

Pre-processor libraries, in this comparison, would be like asking a friend to help you cook with things like hey I chopped

Talk about the inflexibilities of take out.

End of section - it's important for devs to understand WHY libraries are making those decisions. Things like vertical rhythm, complimentary colors (the other versions), type scaling, font pairing etc..

Move on to Sass vs Less history - ruby, js, dart

talk about Sass/SCSS syntax
functions

CSS and postCss and

Decision path - let's cook our own dinner, but ask a friend to chop the carrots. I recommend this as it doesn't abstract away any styling skills
