# Bash notes

## IMPORTANT!!!

Macs ship with an older version of bash, 3.2.57(1)
You can NOT use modern syntax like -v to see if a variable value exists.
The following notes will all be for the older, 3.2.57(1) bash version

## ~

~/ is the same as /Users/hideaki/

`~/someDirInCurrentUser`

## If you ls -l

File permissions are separated like so:

`-rwx-rw--r--`

1. first `-` indicates it's a file
2. first set of letters indicate owner permission, then group 3. permission, then everybody else
3. you are the owner, so look at the first set of letters

r = readable
w = writable
x = executable

So in the above example, owner can read, write, and execute, the group can only read and write and all others can only read.

### You can change permissions with chmod

syntax is chmod [GroupIndicator]+[thePermissionToAdd][filenameincurrentdir]

for GroupIndicator
u = "user" or owner, what you'll use most of the time
g = "group", or the second set of what you see in ls -l
o = "others", or the third set
a = "all three"

IF no group indicator, a is assumed, changing permissions for all groups.

Owners will most likely start with r and w permissions, and you'll PROBABALY have to add the x when you are writing your own scripts.

Best practice to always use `chmod u+x [fileName]`

## Set up

- `#!/bin/bash` on all files
- No extension like .sh
- `chmod u+x <filename>`
- In commandline, edit with nano scriptname but maybe just better to open up vscode

## Adding to path

### Temporary

in the beginning of any terminal session add
`export PATH=$PATH:~/[someDir]` call the script from anywhere with just the file name (if the filename does NOT have any extensions)

The syntax is
`export PATH` exports the file to the PATH
`$PATH:` an absolute path is coming next
`/Users/hideaki/someDir` adds the dir inside Users/hideaki to PATH
as a bonus, you can use `~/` to replace `/Users/hideaki/`

Remember to add the whole dir WITH the script inside, not individual scripts.

### Permanent

If you want to keep that dir in the PATh permanently, you write the same exact export code above INSIDE the ~/.bashrc file.

## Commands

- `date`
- `head -n 3 filename` first 3 three lines of script
- `tail filename` last 10 lines (default without -n) of script
- `echo $PATH | tr ":" "\n" | tail -n 3` print the PATH but replace : with a newline, and just the last 3 entries

## Syntax - Common mistakes

- White space and return carriages matter a lot!!

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
   Does file exist? - this is actually optional, but best practice for readability

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

File check version

```
FILE=testFile
if [ -f $FILE ]; then
echo "$FILE" exists in current dir!
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

## grep "Global Regular Expression Print"

`grep hello journal.txt`

if 'hello' is present in journal.txt, it will print the word the number of itmes it appears. It used 3 times, output is

```
hello
hello
hello
```

grep -i will ignore all cases

## Reading txt, manipulating strings

The general strengths of bash is manipulating strings from txt files.

`cat file.txt` print entire file

Others to check out

tr, sort, uniq, awk

## color output

Best to output script erros in red, 200 ok in green, default in white

To change color, when echo

`echo $'\e[1;31m'"The command did not work"`

However, this will make everything after \$'\e[1;31m' red forever, so change it back to white after the error

``echo $'\e[1;31m'"The command did not work"$'\e[0m'`

It gets messy fast, though, sooo assign them to variables

```
red=$'\e[1;31m'
white=$'\e[0m'

echo $red"That did NOT work"$white
echo Now it's back to normal white
```

## Creating a file with content

pipe an echo

`echo 'hello' > hello.js`

This will make a file called hello.js with hello inside

Append to a file

`echo 'how are you?' >> hello.js`

this will append a line to an existing file

### Possible issues appending to an existing file

If I forgot to carriage return the last line, it will not print to a new line.
Prettier will format on save and always do that for me for js files, but not for .ignore or .env files.

Workaround.. Just make a new line in the command. This might make extra lines, but the code will run this way for sure.

`echo -e '\neslintrc.js' >> .gitignore`
the -e flag allows you to use \n inside the echo

## nodemon and local ports lsof

In the typescript tutorial, I set up ndoemon and concurrently to run tsc -w on a ts file and to nodemon the build js file at the same time. The ts file used an express server to liston to port 3000.

When I didn't shut down the session with control c and exited VS code, the port stayed OPEN!

This is a weird bug with nodemon or ts or the combination of the two, but the workaround is.

### How to list port activity

Check for activity on localhost:3000
`lsof -i tcp:3000`

If any output, the port is in use.
If no outoput, the port is open and available to use.

From that output, look at the PID number of each.
To Kill that node,

`kill -9 SpecificPIDnum`

That third arg should be a number that was listed from the lsof command.

Now the port is open and avilable to use!
