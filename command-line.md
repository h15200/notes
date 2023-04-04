# using terminal (linux)

- `man` + command to look at documentation. The most important command!


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
- `sudo apt install <packageName>`  (brew in macOS)
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
