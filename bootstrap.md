# bootstrap

## setup

<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous"/>

## classes

Bootstrap has pre configured classes

### wrapper for responsive container

<div class=”container-fluid”>  </div>  
Wrap the entire html body with this to have responsive full screen for whatever device

### responsive images

`class="img-responsive"` - makes the image 100% of the width of the device. Use on all images

### util classes

class=”text-center” , “text-left”, “text-right” - child element layout

### color classes

class=”text-primary” or “btn-primary” for buttons colors with primary color of app.

### placeholder

`class=”well”` - visual representation of where this element (usually a div) will be located on the page. Used as a placeholder for layout.

### buttons - visuals

Buttons - remember, the element is <button> but most classes are btn-thing

The role and class attributes can turn <a> and <input> into buttons as well.

<a role=”button” class=”btn btn-primary” href=”#”>Click Here!</a> - turns the link into a button

<button class=”btn btn-default” // you can name two classes at the same time with a single empty space separator

<button class=”btn btn-default btn-block” // will stretch the button as wide as the device width

You must include class=”btn” for all buttons.

The second parameter, btn-default can be changed to btn-primary to use the primary color of the app.
Options for btn-default
btn-primary
btn-info - optional actions
btn-danger - dangerous actions

### Bootstrap Grid

    Steps:

<section class = “container” >
   <div class=”row”>
      Have, Header, paragraphs, anchors - each with a class=”col-<size>-<#outof12>”

Col total is 12!
Common usage is:
If you want a row of elements,
Wrap everything in class=”row”, then individually div class=”col-md-3” //medium 3 per item in that row (for 4 items evenly across the screen, as 3\*4=12)

Use built in primary colors for all images, font, etc..
Use img-responsive for all images

### font awesome with bootstrap

<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.5.0/css/font-awesome.min.css" integrity="sha384-XdYbMnZ/QjLh6iI4ogqCTaIjrFk87ip+ekIjefZch0Y+PvJ8CDYtEs1ipDmPorQ+" crossorigin="anonymous">

Used with an “i” tag <i class=”fa fa-thumbs-up”> thing </i>

WIll print a thumbs up to the left of “thing” . Icons will take on the pixel size of their parent element for convenience.

Using class=”col-xs-num” on form elements will spread out buttons evenly over different devices
