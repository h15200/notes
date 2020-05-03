# Basics of PHP

PHP is used in server side to create dynamic (not static, different for each user) web apps.

User -- Web Server -- PHP Interpreter -- PHP & HTML Files
|
|
Database

PHP can be used directly inline with an HTML doc.
The start of inline PHP is notated by <?php    and ends with   ?>

Commenting - # or /\*

echo - use double quotes, escape nested double quotes, \n for new line.

String concatenation use dot.
echo “Hi” . “there.”; // prints “Hi there.”

Syntax - variables are declared with $. 
Snake casing is traditional for php  $like_this

String parsing - simply add the variable with \$ inside curly braces and they will print the assigned values.
To add immediate letters after, surround var name with curly braces.

Ex. $type = “golden retriever”;
echo “\nLook at all of those ${type}s!”;

Echo can also work like  
 echo (“this also works”);
echo “this”, “also”, “works!”;
echo (“this”, “does”, “not”) /_ this will throw an error _/

For printing just variables, you don’t need double quotes

n = n + 1; can be shortened to n .= 1;

Assigning by reference (like a pointer)

$person = “Bob”;
$person_2 =& \$person;

// any changes to one will change the other

Numbers - integers and floats can be used in math, but using a float will result in decimal points as a result even if it calculates to an even integer.

+=
-=
\*=
/=
%=

All good

Exponents is \* \*

Functions
Variable in php is snake_case.
Functions are camelCased by convention
function <functionName> {
} // same as a function declaration in javaScript

    If there is no return statement, the function returns NULL (not undefined like JS)

    Parameters of functions must have a $ to denote variables

    If a php function is called without the exact number of arguments for the declared parameters, it will cause an ERROR unless there is a declared default value in the parameter.

    function greet($name=”chum”) {
    	return “hi there, ${name}”;
    				}

    Since in php you need to assign reference by &$variable, functions remain pure.

    	function addTwo ($num) {
    		echo $num+2;
    			}
    	$my_num = 1;
    	addTwo($my_num);     # returns 3;

echo \$my_num; # returns 1;

However, if you pass in &$num (pass by reference) as the parameter, $my_num will change after the function is run

Built-in Functions
gettype($<var>);  # will return the type of data
	var_dump($<var>); # will return details of a data type

    strrev()  - string reverse
    strtolower() - lower cap
    strtoupper() - higher cap
    str_repeat(str, number of repeats) - repeats a string
    substr_count(str, substr) - counts how many substrings in a string

    pi() - returns pi
    abs() - absolute number of an input number
    round() - rounds to nearest integer
    ceil () - rounds up to integer
    floor() - rounds down integer
    getrandmax() - returns the greatest number our environment will allow to generate
    rand() - if no parameters, returns a number between 0 and getrandmax
    	Otherwise, rand(min_num, max_num); # inclusive on both ends
    str_pad - pads a string with extra crap
