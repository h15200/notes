see separate flex.md and grid.md for those modules

# Current Landscape

2020 - vanilla CSS is growing to cover things that bootstrap and other pre-processors used to do. Bootstrap is on the way out. SCSS is still good for nesting and slightly easier variable, mixins, and functions, but CSS will probably cover these in the next few years. Stick only with SCSS (and CSS when possible) and for now don't bother with bootstrap or LESS.

Reset library is no longer needed.
Just use this at the top of every project

```



*, *::before, *::after {
  box-sizing: inherit;
  margin: 0;
  padding: 0;
}

body {
  box-sizing: border-box;
  // font stuff
}

```

# Recent Mistakes

- You can't style fragment tags in react because they don't exist on rendering!

* You can NOT a z-index on things that are position:static. flex, grid items are exceptions and will always work with z-index.

* Multiple background images can be added with comma separated values, but you must remember to change the opacity of the top layer to less than 1 to see the bottom images, OR use the newish background-blend-mode prop. see h2 topic later in this file

* using vanilla css variables for color and changing opacity later

```
// declaration in root

:root {
  --color-primary-dark: #333;
}

// to use color primary dark with an opacity of .5,
// wrap the var + , + opacity value all under rgba()

h1 {
  color: rgba(var(--color-primary-dark), .5);
}
```

- tranparent is a valid color

- If a keyframe animation is glitchy, backface-visibility: hidden; could be a weird fix

- You CAN change the ::after element on hover of the original like this.
  `.btn:hover::after {}`

- SCSS specific. To use calc() with a variable, you need an additional #{} inside

```
.div {
  width: calc($my_num + 3)
}

// this does NOT work!

// add hash and curly braces to use scss variables along with numbers

.div {
  width: calc(#{ $my_num } + 5)
}
```

- Setting a border-radius on background-image
  When setting a background-image on a rounded container, the edges will overflow. Simply set `overflow: hidden` on the container to have the image rounded.

# File Structure

For big projects, I used 7 in 1 approach

The gist is you separate all scss files into smaller files into the appropriate folders

variables/ font, breakpoints, colors, etc..
helpers/ helper functions
layout/ any global stylings (after resets)
components/
base/ any universal resets
utils.scss - not a dir, but a while with all helpers like .u_margin_bottom_small
main.scss - hub for all of the above

# CSS and CSS with React

## class name convention BEM

Block - Element - Modifier

Sort of takes on the spirit of bootstrap. identify the location and the THING to make it reusable

if a button is part of the nav

class="btn nav-btn"

and if it's blue

class="btn nav-btn nav-btn--blue"

for React, convention is slightly different, but it doesn't really matter. Do your thing as long as you can recognize it.

## Variables (custom properties)

Syntax is

```

// declaration in root

:root {
--color-primary-dark: #333;
}

// use it like so

h1 {
color: var(--color-primary-dark);
}

```

## Utility Classes

In the 7 in 1 approach, in the \_utils.scss, make helpful classes like:
`.u_center_text // center whatever is a child in this div`
`.u_bottom_margin_2 // bottom margin 2rem on this element`

Bottom margins are especially helpful

To use css modules make sure to use the same style class, then import the `_utilities.scss` into main,
and the whatever.module.scss should import main

## Sibling Selector + ~, Hover state selector

When using `:hover` or `:active` etc.., you can change the properties of child elements under that state that you are indicating.

```
a:hover {
}
// when anchor is hovered, change the properties of the anchor itself
```

```
a:hover div {
color: green
}

// when anchor is hovered, change the properties of the CHILD div under anchor

```

But for a SIBLING elements, you can use:

`a.hover ~ div {}`
the tilda `~` means ANY sibling that comes AFTER the hover element that is a div. can be multiple div elements

`a.hover + div {}`
the plus `+` means ONLY the direct next sibling. ONE div element

You CAN’T select a sibling BEFORE the element or any parents of the hover element.

## Body

Usually good to start with:

background-color gray ish
padding 2rem ish- if you want a frame around the entire site
font-family : someVar
font-size:
line-height

## anchor links

- Most buttons will be anchor or Links, so include class/className btn or something to reuse code

- links are inline by nature, so good idea to make inline-block to have access to vertical padding/ margin while taking up the entire horizontal space

- All anchor tags have 4 link states:

  1. :link (unclicked, initial state)
  2. :hover
  3. :visited (a link a user has already clicked)
  4. :active (the exact moment the link is clicked)

- Generally use group a:link and a:visited to style "regular" stategeneric color, border-radius, padding, transition time, etc..

- And a:hover and a:active for click actions

## buttons (actual)

Although most clickable thing are anchors and not buttons, some things do need to be actual button elements, like a submit button.

Usually, you get rid of the default border because it's ugly and add cursor pointer

## form

Always wrap in a container so it’s reusable later as .form-group

`font-family` defaults to something else inside all form tags, so assign back to “inherit” in css if you want the font of whatever you set in `body`

To style the input focus state - turn outline to none, but always replace with some other cue such as adding box shadow and a border on focus for accessibility

To prevent shifting on the border, make it in the resting state as well ex.. `Border-bottom: 3px solid transparent;` then have it a different color in focus state

action attribute will take you to the html file that the form submit will trigger
method defaults to "get"

## input and label

syntax (3 ways)

1. label before input, using a htmlFor (just "for" for react) matching the name attribute of input
2. label AFTER input with same syntax
3. label is parent of input. No need for htmlFor attribute

- it doesn't matter which to use in terms of best practice, so use the one that makes the most sense in terms of css. In a type=checkbox, it may make sense to nest to make the entire row checkable

```
<input id="name" type="text" required placeholder="enter name" />
<label htmlFor="name">enter name</label>
```

```
<label>
  <input name="first-name" />
</label>
```

These are not automatically inherited from the `body`, so set them to `inherit`
Font-family
font-size
Color

might be good to `border: none` and background-color to grey

You can style the placeholder TEXT!

`input::placeholder { color; blue }`

You can style on valid/invalid state INSIDE the input focus state.
`input:focus:valid` or `input:focus:invalid`

Or the valid/invalid statement of the required call itself with
`input:required:valid` and `input:required:valid`

:placeholder-shown {
Style the input when the placeholder is displaying something

### RADIO

For radio, wrap in an extra container AFTER .formGroup like .formRadio

Then have the buttons have the same name attribute, `type=”radio”` and id along with a label element with htmlFor same as Id

You can NOT style radio buttons/check boxes in css, so you’ll have to build a new one over the existing one.

Solution: since radio labels can be clicked to click on the actual radio buttons, you can hide the original button and make a new one INSIDE the label element as a span

Use pseudocode :checked and if the original, now hidden button is checked, make the new DOT inside the custom button appear with opacity

The original radio button should be position:fixed opacity:0 to keep the tab accessibility alive

## Images

Are inline elements by default, so you'd want to make it a display: block in most cases.

Images need to have the appropriate resolution size to optimize performance based on device.
If you click on an image file in vs code, you can look at the right bottom corner for the pixel size

2 types of images

Html images - when you use img tags and add a src
Css images - when you use background-image and use image without declaring it html

### Responsive Images

A responsive design By definition must have three things

1. media queries
2. responsive images
3. grid system

What is responsive images?

The appropriate image file will be downloaded for the view port so phones don't download huge images

Use <picture> (html 5.1) and picture fill (polyfills for pictures)

first wrap your img with a picture tag

each picture tag will have
source tag with srcset attribute and media attribute with media query

img tag will now be for the smallest mobile version, which is the fallback in case source doesn't work

There should be a source tag for EACH version of the picture (not including mobile)

this means the picture will ONLY download based on media query

```

<picture>
  <source srcset="pathToBigImage" media="(min-width: 1200px)">
  <source srcset="pathToSmallerImage" media="(min-width: 800px)">
  <img src="pathToSmallestMobileImage" alt="pie"/>
</picture>
```

download Picturefill library for older browser compatibility

### background-image or object-fit on img tags

If you want to use image to cover an entire container,
background-image in css is the easiest way.

If you need to use img tags for gatsby or other optimization, use object-fit

```
.img {
Height: 100%;
Width: 100%;
object-fit: cover
}
```

## Responsive Images with HTML

### Density switching

HTML
srcset attribute instead of src and use multiple images for different densities.

Density switching in HTML
`<img srcset=”img/logo-green-1x.png 1x, img/logo-green-2x.png 2x alt=”blabla” />`
This will allow the browser to use the first 1x png file for normal screens and 2x for high resolution screens

### Resolution switching

`<img srcset=”img/banner-small 300w img/banner-large 1000w" sizes="(max-width: 900px) 20vw, (max-width: 600px) 30vw, 300px src="someKindOfFallback>"`
srcset specifies that the first image is 300 pixels wide and the second is 1000 pixels wide
notice there are no commas but just white space separated values of `file1 size1 file2 size2 etc..`

sizes specifies when to use which image. The 300px in the end is the default if neither breakpoints apply.
Src= is a fallback in case the srcset and sizes don’t work

In terms of art direction, you can allow the browser to use different image files based on the device, usually based on the screen width.

### Art Direction

For art direction, use `<picture>` tags with `<source>` and `<img>` inside along with a media query inside the html.

```

<picture

<source srcset=”logo1 1x, logo2 2x”
media=”(max-width: 37.5em)”>
<img srcset=”stuff” alt=”stuff” src=”fallback”

```

## Responsive Images in CSS

For image tags, this does NOT work because adding display none inside a media query for an html tag still results in the browser downloading those images.

For background images, putting them inside media queries WILL trigger the download itself, making it responsive.

For css images, you can use 2 different images for background images that cover the screen. The small one can be the default (mobile first) and around 1200px - 600 x 2.

Then write a media query for bigger screens and better dpi

```

@media (min-resolution: 192dpi) and (min-width: 600px), (min-width:2000px){
Background-image: url(theBiggerVersion)
}

```

// the comma separation is the same as an OR operator
// if the screen size is bigger than 600 AND it’s retina, OR if it’s 2000px + regardless of dpi, use the big image
Divide px by 16 and use em instead for best practice

## Multiple background-images

- background-image property can take comma separated images. Both linear-gradient (or whatever gradient) made up of just colors AND a url(path) can be taken to make overlays.

  - ex ```
    .header {
    background-image: linear-gradient(to right bottom, #222, #666), url(../somepath.jpg))
    }

    ```

    ```

- You can either blend the two (or more bg images) using background-blend-mode (93.5% usage) or adjusting the opacity of the top layer.

- Since useability is much higher than clip-path, a good alternative although a bit verbose.

## Clippath

Looks cool in new sections of a site

Will only show a portion of the element. The polygon will make a multi path shape based on the X Y coordinates. Separate X and Y with a whitespace, and each coordinate should be comma separated. The below example will show the ENTIRE element, so the same thing as not writing any clip path. The order of coordinates are the same as padding or margin (top, right, bottom, left) No need to add a unit for ZERO, but you can use usual units (percentage or vh is probably best for responsiveness)

(use both clip-path and -webkit-clip-path)
clip-path: polygon(0 0, 100% 0, 100% 100%, 0 100%)

## Skew Entire section

An alternative to clip path is to skew an entire section by using transform: skewY-(6deg);

And have all direct children skew back upright

`.section >* { transform: skewY(6deg);`

## Center horizontally and vertically

2 methods

```

.container {
display: flex
align-items: center
Justify-elements: center
}

.container-item {
align-items: center // centers text inside the item
}

```

old school without flexbox

```

Position absolute (position relative on parent container)
top: 50%
left: 50% //now top left edge is centered
transform: translate(-50%, 50%) // go back half the element’s height and width
text-align: center // now content is centered

```

## currentColor as a color

for borders, box-shadows, and anything else on an element that could change color based on state like hover,
use currentColor as it dynamically sets the color.

If color is not indicated on this div, it will cascade from a parent that does have a color indication

```
div {
  color: red;
  border: 5px solid currentColor;
  box-shadow: 0 0 5px solid currentColor;
}
```

## ::before and ::after

::after creates a child of the element in css alone without the help of html.

Nothing will display unless you have at least two properties:
content and display

`content: ''` You must still set content to an empty string even if there is no content.
The display should be set as the "master" element

## Keyframes Animation

Must have at least the keyframe name AND animation duration to activate
optional third arg like `infinite`

```

p {
animation: myAnimation .4s infinite
}

```

Use @keyframes rules and implement them in elements
For performance, best to just use TWO selectors or less inside each keyframe %
One of the 2 is usually transform to move elements and the other is opacity.

Usually necessary to start with opacity 0% at 0% of animation so the element doesn’t transport at the beginning

```

@keyframes slideFromLeft {
0% {
opacity: 0;
transform: translate(-100px);
}

80% {
Transform: translate(20px); // goes past final position

100% {
opacity: 1;
transform: translate(0) // snaps back to final position
}
}

```

// you can also use ‘from’ and ‘to’ instead of 0 to 100%
// keyframes can be declared AFTER or BEFORE the element that is implementing it

Other useful settings:
animation-delay: amount of time before the action start
animation-timing-function: the ramp up of the animation rate - built in types
animation-iteration-count: number of cycles
animation-direction: which way to roll the tape
animation-fill-mode: where the css of the element should end up

When using delay, probably a good idea to use fill-mode: backwards (to start with opacity 0) as the initial state is probably better hidden.

If an animation is glitchy, backface-visibility: hidden; could be a weird fix

## Transition

You can use transitions to select different times/cubic bezier for each type of transition separated by a comma

```
.thing {
transition: transform .2s, width .6s cubic bezier(0,1,1,0), background-color .2s;
}
// all transforms will take .2s, width changes will take .6s with the curve of bezier(0,1,1,1), background-color will take .2s
```

### Cubic Bezier

transition: cubic-bezier:

Custom timing for transition. Mess around at https://easings.net/en and cubic-bezier.com

## background video

Do this instead of writing `src=` as an attribute inside the video tag

```
<video>

	<source stuff here />
</video>
```

Available at coverr.com

## filter

Super useful when you want a hack to change the color of a picture or vector

You can use filter on an image to blur, change brightness, saturation, etc..
Useful on hover.

### filter and translate: scale bug

When using this with translate: scale, there might be a weird line, in which case you can use overflow: hidden on the container

## Text color with color gradients

- put the background color on the entire container with the text

```
.heading-secondary  {
 background-image: linear gradient(color, color);
 background-clip: text;
-webkit-text-fill-color: transparent;
}
```

## Box shadow

First value is almost always 0!

A good box shadow on links and buttons

```
a:visited, a:link {
box-shadow: 0 .6rem 1.2rem rgba($black, 0.2)
}

a:active {
0 .3rem .6rem rgba($black, .2)
transform: translateY(1px);
}

// change shadow so that it looks like it's moving down on click
```

## Useful Glyphs

Glyphs are symbols written in html.

### greater than, less than

`&gt;` >
`&lt;` <

for writing code inside a `<code>` element without triggering real html

### space but no content

TO have an html element with no content but space on a paragraph
`&nbsp;`

### Fast and easy close button

An easy way to make a close button on an anchor element.
make line-height: 1 to center the cross inside the element

`&times;`

## Text shadow

Don't forget to set opacity around .2

A typical header shadow on hover could be:

```
h1:hover {
text-shadow: .3rem .5rem .5rem rgba($color-black, .2);
}
```

## Outline

If you want space between the margin and the border, use outline property which works exactly the same as borders
It also has a useful prop, `outline-offset`

## scroll-behavior

When you click on an anchor link (or any react version of that) that has a #section jump, the scroll behavior defaults to intantaneous jump. If you want a smoother scroll as to show the user which way we are jumping to:

```
// in the html tag

html {
  scroll-behavior: smooth;
}
```

## zoom in / zoom out on hover

To zoom in, just use transition: scale(1.4).
To zoom out, put an initial state of scale(1.4) and go to scale(1) on hover

## shape-outside (when using floats)

When floating an object, you can use shape-outside to dictate how the text outside flows around this object. A common thing to do is to use clip-path (and -webkit-clip-path) to make a shape, then use that same shape on shape-outside so the text flows around the shape

Both shape-outside and clip-path should be used with prefix -webkit as well

## old way of grid layout (float) and clear fixes

- before flexbox / grid, you used float left or float right to do layout
- all float calls will collapse the height, so you need to do a `clear fix`
- ```
  floated::after {
    content: "";
    display: table;
    clear: both;
  }
  ```

## Horizontal Scroll bar on just one line of text

in the container div,

```

overflow-x: scroll;
Whitespace: no-wrap.

```

## Text overflowing out of container

- on the container, set these two props

```

overflow-x: hidden;
text-overflow: ellipses;

```

## mask - like a stencil kit

As of 2020, use prefixes

To put a color over an image like a mask

set `background-color` to whatever color you want

`mask-image : <select image>`
`mask-size : cover` // besides `cover`, other properties in background-size will work

This will make a stencil of the image in the color that you wanted.

## <span> glitch box-decoration-break

When a span element text is broken into a new line or page, it behaves differently from regular text
`-webkit-box-decoration-break: clone;` will take on existing margin, border, padding properties in a new line

## Rotating Cards Feature

Set transition to .8 s or something like that on the parent
Make two cards (one with ::after) have them stack on stop of each other with position absolute

Have the back card already hidden and rotated 180 deg on rotateY
Backface-visibility: hidden

On hover (or click), transform rotateY(180deg) the front card, and rotate the back card back to 0 deg
Perspective: the lower it is, the more drastic the rotation transformation is

## Changing highlighted / selected text color

in the base folder

```

::selection {
background-color: $primary-color;
color: $color-white
}

```

## Pure css hamburger menu

Structure:

If in gatsby, place this div IN between the <Layout> component in index.js

ememt code

```

Div.navigation
Input.navigation_checkbox id=”navi” type=”checkbox”
Label.navigation_button htmlFor=”navi”> span stuff
Div.navigation_background // the button that goes over the hidden input/label
Nav.navigation_nav // the component that pops up
Ul.navigation_list
Li.navigation_item a.navigation_link x 4

```

The background will expand by 80x to cover the entire screen.
For the new button, use one line for the span and use ::before and ::after to add 2 lines. Then on click, the middle one will hide and the before and after will form a cross.

The div itself is one line, not any content inside the div, so make sure you use the height value

Style the background (the actual hamburger menu) as a circle button. Position fixed

The background expands on :checked to transform: scale(80) and covers the entire viewport

Make sure z-index for background, button, and nav is set such that it’s (from high to low) button, nav, background

On .button, <span> is just a 3px height with a background dark. Then in css add ::before and ::after and have them positioned with absolute. Have before top: -1px or something and after top:1px.

On \_checkbox:checked, have the span element background-color: transparent, and the before and ::before ::after should rotate 45 degrees or -45 degrees (or even better, add an extra 180 or 360 to make the animation more dramatic) and set top to 0.

Also on checked, have the nav elements appear. Keep them opacity 0 and click-event: none when not checked

## Pure css popups / modals

Make a component

```

div.popup id=”popup”
Div.popup_content

```

fixed position
100vh
width 100%
dark background
opacity 0
visibility: hidden

Using #popup in an anchor href, jump to that section

Then .popup:target {
Opacity 1
Visibility: visible
}

### :target

Will select the elemnt that has an id that is equal to the current position displayed in the url.
For example, if you are in `myhomepage.com/about#jazzSection`
Then it will style the element with an id of jazzSection ONLY when it is indicated in the url bar

## media queries, breakpoints, mobile vs desktop first

- Unless the particular field is desktop majority, do mobile first. It strips down the site to its bare essentials

  - for MOBILE first, you will use `min-width: 40em` (applies to all screens bigger than 40em) from smallest to largest screens. The order matters as some screens will inherit properties from other screens

    ```
    @media only screend and (min-width: 50em) {
      h1 {
        // stuff
      }
    @media only screend and (min-width: 40em) {
      h1 {
        // stuff
      }
    }
    @media only screend and (min-width: 37.5em) {
      h1 {
        // stuff
      }
    }

    }

    ```

  - for desktop first you will use `max-width: 30em` (all screens smaller than 30em) and order from smallest to largeset view port

- Find break points based on content and when the layout starts breaking, not some pre made pixels

- Best practice to use ems for media break points

- syntax is:

for very small screen (for desktop first in this case)

```

@media only screen and (max-width: 25em) {
h1 {

}
}

```

### advanced media query stuff

Use mixins to write media queries inside the mobile version in SASS for big projects

### @content

allows rulesets inside the mixin when declared

Use both min and max width for the middle children break points! Otherwise, you’ll have to think about the order

### query by device type

The way css can figure out the device type is detection of a hover type. You can add multiple media queries with a comma, which as as an OR operator

```

// either a device with a certain max width OR a device that has a mouse
@media only screen and (max-width: whatever),
only screen and (hover: hover) {
h1 {
color: blue
}
}

```

For NON mouse devices, use `only screen and (hover: none);`

### Units

Use relative units when possible

html {
font-size: 100%;

@include media (big-desktop) {
font-size: 110%;
}

@include media (tab-land) {
font-size: 85%;
}
@include media (tab-port) {
font-size: 70%;
}
@include media (phone) {
font-size: 65%;
}

When going through media queries, go from big to small:

Base and typography
Overall html sizing
H1 letter spacing, size
H2
General layout and grid
Page layout
Individual components

When the media query requires a new build all together, copy and paste the entire section first and then delete the ones that don’t need changes via process of elimination

## @suports, caniuse.com, graceful degradation

Always check to see if features are supported on most browsers

For example, let’s say you want to use backdrop-filter which is supported 70% ish right now and you need a backup plan.

In css, you can do this with `@supports`
does your browser support stuff inside parens? if so, use the first line. if not, use the second line

```

@supports (backdrop-filter: blur(10px) {
backdrop-filter: blue(10px);
background-color: whateverColor;
}

// important to write out the FULL prop AND value inside the parens. it's weird, but
you have to write the css twice for the prefered method, once in parens, and once in first line.

```

## sliding color highlight on hover

by using ::before and ::after on hover, you can make some cool things
like a sliding hover highlight.

You make an item, and an item::before, which is the high lighted version of item.

You can access the ::before item on hover over the original item with

```

item:hover::before {

}

```

Making a hovering highlight example:

reminder: z-index does not work on position: static!! Change to relative.

```

&\_item::before {
content: "";
display: block;
position: absolute;
top: 0;
left: 0;
background-color: \$color-primary;
width: 3px;
transition: transform .2s, width .4s cubic-bezier(1,0,0,1);
height: 100%;
transform: scaleY(0);
}

&\_item:hover::before {
transform: scaleY(1);
width: 100%;
}

&\_link:link,
&\_link:visited {
display: flex;
align-items: center;
text-decoration: none;
text-transform: uppercase;
color: \$color-grey-light-1;
padding: 1rem 1.5rem;
position: relative;
z-index: 10;
}

```

## Loading images from an api

If you are loading an image tag with outside data and assigning it to src, the browser
will render an empty border during the time the element has no src attribute.

Putting # or "" inside the src does not work.

THe best workaround is to use css and keep the element out of the flow until it's loaded

```

img {
display: none;
}

img[scr*="https"] {
displya: inline-block;
// other props for the image
}

```

`*=` is 'includes'

## weird bug opacity, display, transition

To go from display none to fade in

1. display: 'none' transition: 'opacity 3s'
2. WAIT by using setTimeout( () => {opacity: 1}, 0)

- latest aha's

you can repeat the same tag, class, id and add specificity (no reason, but possible)
.header.header

a pseudo class has the same specificity as a class

.test:hover {
background-color: orange
}

.test.test{
background-color: blue;
}

// will be blue

nth-child(3) // only 3rd child

// when passing in n to nth-child, it will start by using 0 in place of n then increment until no match
nth-child(-n + 3) // will increment n from 0 going up until not possible

- How to make a triangle with css only

div with borders without content and inline-block
make top/bottom transparent and a third one not transparent

- when you want words to break at words, but super long single strings to break and not overflow the container
  `overflow-wrap: anywhere`

using word-break does not work for both conditions for some reason.

```

```
