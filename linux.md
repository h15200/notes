# Linux - a free implementatin of the UNIX operating system

- Linux interface includes system calls, library funcs, and other low-level apis
  to perform tasks such as file I/O, creating and deleting files, and
  directories, creating new processes and threads on the same computer, and
  communciating between processes on different computers via RPC
- this entire set of low-level apis is also known as `system programming` interface
- the 1st UNIX implementation was developed in 1969 by AT&T. The OS involved a
  tree-structured file system, a separate program for interpreting commands
  (the shell), and the notion of files as unstructured streams of bytes
- the first implementations of UNIX were written in `assembly` code, but `C`
  has become popular enough by 1973 so the OS was re-written in C, paving the
  way as the main system programming language
- `GNU` project ([G]NU's [n]ot [U]NIX), founded by Richard Stallman in 1984 called
  for a free implementation of UNIX that allowed users to see the source code.
  Essentially, the start of the idea of open-source in programming! By the
  1990s, the GNU project had produced a system that was almost complete except
  for the `kernel` (the core computer program that governs all
  software/hardware, with device managers, and I/O memory) It's the system
  that sits between Application -> Kernel -> [CPU, Memory, Hardware Devices]
- in 1991, Linus Torvalds started working on a new kernel based on the
  Minix kernel. It eventually because the `Linux` kernel, which combined with
  the `GNU` project, became what we know was Linux. First release of Linux 1.0
  was 1994.
- the concept of major/minor/patch release started with linux kernal versioning
  to not disrupt users
- Linux code gets patched multiple times a day, 24/7 to reflect the changing world

# Linux Foundation

- world's leading home for collaboration on open source projects including software,
  hardware, standards and data
- oversee projects that support the world's infrastructure including Linux,
  Kubernetes, Node, Graphql, Jenkins and many more.

# Distributions

- currently 3 major families of distro
- the main differences are package mangement, software versions, and file locations
- once you grasp the fundamentals of these differences, switching between distributions
  become relatively painless

- 3 Families:

1. Red Hat Family Systems (including Red Hat Enterprise Linux, CentOS and Fedora)

   - uses RPM-based package manager `dnf`
   - RHEL is widely used by enterprises which host their own systems
   - CentOS is virtually identical to RHEL but for no cost for the end user
     and gets the same updates a bit after RHEL

2. SUSE Family Systems (including SLES, openSUSE)

   - uses RPM-based `zypper` package manager
   - is of German origin "Software und System-Entwicklung" (Software and systems developmente)
     and was developed main in Europe
   - SLES is the enterprise version of the SUSE family distro
   - OpenSUSE is the reference distribution for this family and is available
     at no cost
   - widely used in retail and many other sectors

3. Debian Family Systems (including Ubuntu and Linux Mint)

   - uses DPKG-based `APT` package manager
   - Debian distribution is upstream for several others including Ubuntu.
   - Ubuntu is upstream for Linux Mint and a number of other distros.
   - commonly used on both servers and desktop computers
   - Debian is a pure open source community not owned by any corporation and
     has a strong focus on stability
   - Debian provides by far the largest and most complete software repository
     to its users of any Linux distrubution
   - Ubuntu is widely used for cloud deployments

## Kernel

- the term `operating system` is commonly used in 2 ways

1. the entire package consisting of the central software managing a computer
   including command-line interpreters, gui, editors

2. more specifically, the central software that manages memory, (CPU, RAM) and
   devices

- the term `kernel` refers to #2
- the `kernel` software is an executable

- `process` is an instance of executing a program
- a `daemon` is a special `process` that runs in the background and is usually
  running through the lifecycle of the system until shutdown (think windows
  background services for OVR)
