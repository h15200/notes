# using terminal (linux)

## files and navigation

- always use `rm` with -i, especially for recursive deletes on directories `rm -ir my_dir` 
- mv will rename if no destination
- `file myFile.txt` will show file type
- `head`, `tail`, `more`, `less` will show file info
- `cat` will print to output if none is specified. if output is shown, it will overwrite `cat file_1 > file_2` // will overwrite file_2 with content of file_1
- `echo hello! > file1.txt` will add text to file

## systems

- `apt install` (for linux)
- `uptime` will show how long system has been running
- `free -h` displays amount of used and free memory. -h turns bytes into readable format
- `ps -A` displays snapshot of all processes
- `df -h` shows disk space info
- `fdisk -l` shows partition info. may need sudo depending on user
- `lsblk` displays block devices
- `top` displays processes, but what's much better is `htop`. may need to apt install or brew install
