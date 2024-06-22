# using terminal (linux)

- `man` + command to look at documentation. The most important command!
- `history` will show previous commands
- `ctrl + u` to delete current command line

## files and navigation

- always use `rm` with -i, especially for recursive deletes on directories `rm -ir my_dir`
- mv will rename if no destination
- `file myFile.txt` will show file type
- `head`, `tail`, `more`, `less` will show file info
- `cat` will print to output if none is specified. if output is shown, it will overwrite `cat file_1 > file_2` // will overwrite file_2 with content of file_1
- `echo hello! > file1.txt` will add text to file
- `sudo` is "super user do"

## package management

- `apt` stands for Advanced Packaging Tool
- `sudo apt install <packageName>` (brew in macOS)
  - in linux, `sudo` is necessary for apt commands. In macOS, users usually have permission and `sudo` is NOT a good idea
- `sudo apt update` updates the cache of all systems applications for users to be able to observe
- `sudo apt list --upgradable` will list all available upgrades
- `sudo apt upgrade` (not update, upGRADE) will actually install the available new versions
- `sudo apt search packageName` will search through repo for available apps. Will also indicate if you have it installed already
- `sudo apt remove packageName` will remove app

## systems

- `uptime` will show how long system has been running
- `free -h` displays amount of used and free memory. -h turns bytes into readable format
- `ps -A` displays snapshot of all processes
- `df -h` shows disk space info
- `fdisk -l` shows partition info. may need sudo depending on user
- `lsblk` displays block devices
- `top` displays processes, but what's much better is `htop`. may need to apt install or brew install

## networking

- `ifconfig` the old school way. shows ip address and other info
- the newer way to check network info is `ip a`. (will need brew install iproute2mac for mac)

## GREP (Global Regular Expression Print)

- used to search for text in files

### GREP search in one file

- `grep "search string" <fileName>` is the basic pattern. Without any flags, it only prints out instances without other info. It also prints all instances of the string, even inside other words "hell" would return "hello". It is also case sensitive by default
  - use -w for whole-words
  - use -i to ignore-case
  - use -n line-number
  - use -B + int for before context lines, -A for after context lines. -C is -A and -B but for the same lines numbers (grep -B 2 -A 2 "hi" fileName is same as grep -C 2 "hi" fileName)

### GREP multiple files

- you can NOT grep a directory with just "./" as the file arg. You must use wildstar `*` `grep -win "hello" ./*`. This will search through all files in this directory, but not dig into sub directories
- best practice to indicate file types when searching so `grep -win "hello" ./*.txt` is better. (any file that ends with .txt)
- if you do want a recursive search through all subdirectories starting at the source directory, add -r
  - `grep -winr "struct" ./` note that you don't need a _ here since a _ indicates all files within only one directory. In this case, it will search through every file inside every subdirectory starting at current dir
- if going through large collections of files, you may only want the file matches instead of string instance matches to reduce clutter `grep -wilr "hello" .` note that the "/" is optional for recursive source dir, and "-n" (line number) is omitted since it's pointless in a file-only match
- adding "-c" instead of "-l" will add a count of numbers for all files searched, but it will include 0 matches, so be careful with large data

### Piping with Grep

- if you prepend grep with a source and "|", you are searching within that scope. `history | grep -wi "graph"` will show all previous commands with the string match
- you can pipe as many times as you want. from the above output, we can grep even more `history | grep -win "graph" | grep -win "git commit"` will now search for all "graph" matches and search for all "git commit" matches after that!
- to log the result of a grep to a file, append with `> textName`

### Grep with Regex

- you can use regex instead of hardcoded strings inside ""

- without going too much in the weeds, a lot can be done just with wildcard . which matches length. f
- `grep -wirl "...-...-...."./`

- if you want to use more detailed regex like "\d{3}-\d{3}-\d{4}", you need to use the GNU version
- Linux and Unix have different versions of Regex. check by `grep -V`
- Linux comes with GNU regex out of the box which uses the Perl Compatible Regular Expressions. Unix comes with BSD which uses POSIX Compatible Regex.
- Generally, the GNU version is much easier to use. `brew install grep` will install the GNU version but you need to use `ggrep -wirlP "\d{3}-\d{3}-\d{4}" ./`

### Most useful commands

- first start with just file overview `grep -wilr "string" ./` for a recursive search to see full surface area
  - use regex for more control
- if you see interesting files, then switch to single file searches `grep -win -C 2 "string" filePath`

## xargs

- the previous output becomes the arg of the next command. Usually used with a pipe
- grep stuff | xargs sed (common usage)

## SED (Stream Editor) command

- must use SINGLE quotes
- a no flag operation will just return the content with the change. use it as a draft
- to finalize the change, add -i flag to modify in place

### REPLACE operation

- 's/findString/replaceString/' is the syntax to find and replace a string. don't forget to terminate with "/" -`sed 's/hello/goodbye/' test.txt` - this does NOT modify the file, but simply returns a copy of the content

### DELETE operation

- same as replace operation, but simply don't include the replace string. keep the delimiters the same
  - `sudo 's/hello// fileName` - will output the content without "hello"

### SED delimiters (same as %s in vim)

- the forward slash "/" is the standard delimiter in a sed command (again, always inside a single uote)
  - if you need the actual forward slash as a string, it's possible to use other chars as dlimiters like [".", "|"]
- if you want to remove "/erase" from the string "/erase/hello" , a forward slash delimiter will not work
  - use one of the alternate delimiters instead like `sed 's./erase..' example.txt`

### grep with sed and xargs

- search through all files starting this one for a string. -> outputs all files
- use that output, pipe it, xarg it, and use it as a replace with sed
- grep -wirl "/home/hideaki" | xargs sed -i "" 's./home./root.' - note that in macOS, you need an additional arg for backup (in this case, empty arg of ""). This is only necessary if you are modifying in place

### awk

- string manipulation based on whitespace. $1 is first word (not 0 indexed)
- write commands inside curly brackets
- `print` is the most common command, but can manipulate strings
- `awk '{ print $1 }'` // print the second word of a line
- `awk { $1="newFirstWord"; print}` // change the first word to "newFirstWord", then print entire line

### uniq

- merges duplicates of lines
- `-c` will add a count at first position of line
- often used before or after `sort`

### sort

- sorts lines in ascending or descending with `-r`
- often used with `uniq`. If it has a count, adding `-n` will sort by number

### examples

```
history | grep "git" | awk '{ $1=""; print }' | sort | uniq -c | sort -n -r | head -n 10 > ~Desktop/linx.text
```

1. get all git history
2. filter by "git" being included in line
3. remove history number, which is the first word of each line and print the new line
4. sort it in order of text
5. merge all duplicates and add count at first position $1
6. sort it again, this time based on the count number and in descending order
7. output just top 10 occurances
8. Pipe to a new file
