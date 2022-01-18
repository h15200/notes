# Terms and Concepts

## File Formats

- ALL computer files can be sorted into 2 categories. Text files or Binary files
- Binaries are read byte by byte. Small "problems" in a binary will corrupt the entire file.
- Text includes ALL non binary files
- Binaries are sometimes used interchangeably as executables, but this is technically not correct
- example of binaries that are NOT executables include windows .dll files

## Executables vs Binaries (most of the time)

- as outlined above, binaries technically refer to all non-text format computer files
- Executables are files that can be run from the command line by writing the name of the file itself.
  - ex. compiled C code, in Windows all .exe files
  - if you need to use a compiler in the command line to run the file, it is NOT technially an executable. example of non-executables include node code, js code
- "executables" are sometimes used interchangeably with "binaries" depending on context such as compiling languages. See next topic
- Not all binary files are executables
  - ex. .dll and .so files are binaries but not executables as they can't be run directly from command line. A binary file that is non-executable.
- Not all executable files are binary files
  - ex. python scripts are written as text file, but on Unix systems the python file's "executable" flag can be set and be run directly from the command line. An exectuable, text file.

## Executables == Binaries (sometimes)

- as written on one topic above, the strict definition of executable files and binary files are not equal to each other. Binary files refer to all non-text files in computer files. However, in certain contexts, executables == binaries
- In the context of programming languages that require compiling, things are often divided into human-written code and machine-readable code.
- all human written code might be referred to as `text`, `source code`, `pre-compiled code`
- all compiled code might be referred as `binary`, `executable`, `machine-code`, `compied code`
  - in this context, "executable" is used interchangeably with "binary" as to refer to COMPILED code as opposed to human-written code.

## Program vs Executable vs Process

- a `program` is instructions (either human-readable if it is a script or perhaps a compiled binary file) read by a computer
- an `executable` is a subset of a program, that is callable by the command line directly
- `process` is the result of the OS executing the program.

## Program vs Application vs Service

- `Program` is just instructions for the computer. Same as `Software`
  - A `Program` can be divided into `application` or a `service`
  - `Application` is a subset of program which specifically interfaces with a user to perform tasks. It is designed to be installed and managed by users.
    - ex. VSCode is an application downloaded by users to write code.
  - `Service` is a program that does not involve the user but managed by systems
    - a background process that runs on startup is launched by a `program`, but since the user never interacts with that logic, it is not an `application` but a `service`. With Windows systems, a `Windows Service` or `Windows Background Service` refers to a specific program that runs in the background. In Macs, they are called `agents` or `daemons`

## Server

- servers provide services. Services (see above for details) are just programs that don't interface with users
- servers can exist in the same machine or can be else where, for ex web servers.
- a web server is a specific type of servers that communicate data via RPCs
- a Windows background server is a service that runs in the same machine

## Runtime

- `runtime` describes software instructions that are executed WHILE your main program is running. Runtime code is not in the main program itself, but is needed for execution of the main program.
- context is usually within programming languages. for example, a C runtime is library code that is needed to implement the features of C itself.
  - ex. node is a runtime of js. .js code can't be executed without node library code.

## Platform

- general term for a BIG piece of software that contains various smaller programs. a system that contains many programs
- ex. an OS is a platform

## Library files

- .dll in Windows, .so in Linux/Unix are both shared library code
- they are not run by themselves, but other programs use them by linking at runtime
- they can be shared by multiple programs
- they are binaries but are not executable on their own

## Architecture, System Architecture

- a very high level view of the entire system
- if a small system, may consist of classes
- if a big system, will consist of other sub-systems

## Routine

- what is generally known as functions
- divided into 2 types
  - `function` - a routine that returns a value
  - `procedure` - a routine that doesn't return anything
- can be inside classes (class routines) or outside

## threads, locks, race condition, and mutex (can be also called gate or guard)

- in multi-threaded languages, a `race condition` will occur if multiple threads are trying to mutate global data, which cause unexpected issues. The solution to this problem is to LOCK the write access to this while one thread is working onit
- the mechanism of locking/unlocking is handled by a mutex (mutual exclusive).
- in terms of code, each thread should call mutex.lock() before making changes to global data, then only after the op is done, call mutex.unlock(). While the data is locked, other threads will have to wait until it is unlocked
