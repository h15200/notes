# Bash notes

## IMPORTANT!!! 
Macs ship with an older version of bash, 3.2.57(1)
You can NOT use modern syntax like    -v to see if a variable value exists. 
The following notes will all be for the older, 3.2.57(1) bash version

## Set up

* `#!/bin/bash` on all files
* No extension like .sh
* `chmod -x <filename>`     
* In commandline, edit with nano scriptname but maybe just better to open up vscode
* in the beginning of session add  `export PATH=$PATH:/Users/bla bla` to be able to call the script from anywhere 

## Commands

* `date`
* `head -n 3 filename`   first 3 three lines of script
* `tail filename` last 10 lines (default without -n) of script
* `echo $PATH | tr ":" "\n" | tail -n 3` print the PATH but replace : with a newline, and just the last 3 entries

## Syntax - Common mistakes

* White space and return carriages matter a lot!!


This will run
```
if (a -gt b)
then echo 'yes'
fi
```

This will NOT run
```
if (a -gt b) then echo 'yes'
fi
```

If you want it on the same line, add a semicolon to signify return carriage

## Strings and variables

To use variables inside quotes, use double quotes and dollar sign

`echo "a is $a and b is $b"`
if the variables are not assigned, it will print a single whitespace


## In conditionals, there are types of brackets for different use cases! 
<br/>

1. ARITHMETIC - uses double parenthesis

The code still runs without whitespace after double parens, but probably best to have a space as a habit as double square brackets won't run otherwise
```
if (( a== 3))
  then blabla
fi
```

Also when you are incrementing or making changes with number variables

```
(( count++ ))
```
<br/>

2. Does variable have a value `[ -z ]`

For checking if a variable 'output' has a value, use single square brackets.
This will NOT run without a single whitespace after the brackets.
This will be true if the variable is NOT assigned! Remember it's the opposite of javascript truthy

```
  if [ -z ${output} ];
    then echo 'output has no assigned value!'
    else 
    echo "output is $output"
   fi
```
<br/>

3. Comparing a string to regex [[ =~ ]]

This also needs whitespace after brackets


```
if [[ $thing =~ [0-9]{3} ]]
then SOMETHING
fi
```
<br/>

## Read line loops syntax. keyword 'read', then the variable name that you pick

```
while read line 
do
  echo $line
done > fileName.txt
```