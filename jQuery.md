# jQuery

## setup - jQuery code goes inside a js code

jQuery is inserted at the very end of the <body> section of the html but BEFORE the js script

  <script>src="jquery-3.4.0.min.js"</script>
  <script>src=”index.js”</script>
</body>

// Then in the js file,

\$(document).ready(function() {
// all custom jQuery will go here

});

## syntax

jQuery variables start with $ by convention.
const $thing = $(“.button”);   // stores the class button to variable $thing.

<div class="container">
 <div class="hello">Hello</div>
 <div class="goodbye">Goodbye</div>
</div>

If you want to remove the second div element with the class “hello”, you can either:
$(“.hello”).remove()  // remove this element
OR
$(“.container”).remove(“.hello”) // remove the child named <.hello> of this element

\$(“<tag>”)function()

Methods for tags:

.ready
.addClass (“ “)
.removeClass (“ “)
.toggleClass(“ “) - will add class if it already doesn’t exist, and remove otherwise
.text() - will replace current tag TEXT only with this text
.html() - will replace content with HTML. text + things like <em> and <strong>
.css() - changes css
Ex. \$(“button”).css(“color, blue”); // same as button {
color:blue; }

// can pass multiple properties by
.css( { color: “blue”,
backgroundColor: “red”}) // the properties are camelCase with NO spaces!

    * for single changes, use syntax  .css(“color”, “blue”)

- when using objects, .css({color: ”blue”})
  .animate() - very similar to .css, but represents the end state of the css. First argument is the object with the style changes, and the 2nd argument is milliseconds for the transformation duration. Use syntax for object css - \$(“h3”) .animate({backgroundColor: “yellow”}, 400)

          ex. $(“h1”).animate({color: “blue”, height:

  .prop() - changes properties of elements
  Include properties “disabled”, boolean
  .remove() - will remove an entire element
  .appendTo(“<target>”) - moves an html element to a different location
  .clone() - copies an element. Usually chained to append to copy and paste to a location
  $(“thing”).clone().append(“newPlace”);
.parent() - selects the parent element. Used like: $(thing).parent().css(“color”, “blue”);
  .children() - selects the child elements of an element.
  <class/id>:nth-child(<n>) - selects the nth element of a class or an id. Chain to another command like .children()
  .siblings() - selects siblings of an element not including itself
  .closest( <class> ) - goes UP the dom tree to find the closest element with (<class>)
  $(“h3”).closest(“.nav”) // selects the closest element with class=”nav” above the h3 
.next() - selects the next sibling element UNDER the dom tree.
.find() - will find and select ALL elements under an element that matches the tag inside ()
	$(‘.showcase’).find(‘.caption’) - will select all class=”caption” with in the showcase class
  .prev() - selects the previous sibling element (above)
  <class/id>:odd - selects odd elements 1, 3, 5 (remember 0 index)
  <class/id>:even - selects even elements 0,2,4
  .show() - if the display property is set to none, this will reverse it
  .hide()
  .on() - adds event handlers to jQuery objects. Takes two parameters, the action to listen for, and a callback to run when the action is committed.

First parameter includes:
“click”
“mouseenter” - triggers when the cursor enters an area
“mouseleave” - when the cursor leaves an area

    common ex.  $('.class').on('click', () => {

\$('.shoe-information').hide();
});

After calling .on, if you pass (event) as a parameter to the callback function, you can use \$(event.currentTarget) // NO QUOTES to refer to the class/id that was in the first part previous to .on.

.slideDown(numInMilliseconds)
.slideUp(numInMs)
.slideToggle() - toggles between slideDown and slideUp
.toggle - will go between show and hide
.fadeIn(numInMs), .fadeOut(numInMs)
.fadeToggle(numInMs) - toggles between fadeIn and fadeOut()
// can also use strings like “fast” and “slow”.
.slideDown()

Things you can add to classes

“animated shake”
“animated bounce”
“animated hinge” - falls off page
“fadeOut”

## Async in Jquery

```
$.ajax({
  method: 'GET',
  url: 'http://demo.com',
  success: function(result) {
   // result is whatever the URL sends back from the request
  },
  error: function(err) {
   // if any errors occur during the process you can check out the
   // the error by logging the 'err' argument
  }
};
Or you can specify the type of HTTP request from the get-go. Like so:
$.get('http://demo.com', function(result) {
// result is whatever the URL sends back from the request
});
```
