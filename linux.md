# Linux - a free implementatin of the UNIX operating system

- Linux interface includes system calls, library funcs, and other low-level apis to perform tasks such as file I/O, creating and deleting files, and directories, creating new processes and threads on the same computer, and communciating between processes on different computers via RPC

- this entire set of low-level apis is also known as `system programming` interface

- the 1st UNIX implementation was developed in 1969 by AT&T. The OS involved a tree-structured file system, a separate program for interpreting commands (the shell), and the notion of files as unstructured streams of bytes

- the first implementations of UNIX were written in `assembly` code, but `C` has become popular enough by 1973 so the OS was re-written in C, paving the way as the main system programming language

- `GNU` project (GNU's not UNIX), founded by Richard Stallman in 1984 called for a free implementation of UNIX that allowed users to see the source code. Essentially, the start of the idea of open-source in programming! By the 1990s, the GNU project had produced a system that was almost complete except for the `kernel` (the core computer program that governs all software/hardware, with device managers, and I/O memory) It's the system that sits between Application -> Kernel -> [CPU, Memory, Hardware Devices]

- in 1991, Linus Torvalds started working on a new kernel based on the Minix kernel. It eventually because the `Linux` kernel, which combined with the `GNU` project, became what we know was Linux. First release of Linux 1.0 was 1994.

- the concept of major/minor/patch release started with linux kernal versioning to not disrupt users
