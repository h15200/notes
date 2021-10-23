# Terms and Concepts

## File Formats

- ALL computer files can be sorted into 2 categories. Text files or Binary files
- Binaries are read byte by byte. Small "problems" in a binary will corrupt the entire file.
- Text includes ALL non binary files
- Binaries are sometimes used interchangeably as executables, but this is technically not correct
- example of binaries include in windows .dll files

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
    - a background process that runs on startup is launched by a `program`, but since the user never interacts with that logic, it is not an `application` but a `service`. In this case specifically a `background service`

## Runtime

- `runtime` describes software instructions that are executed WHILE your main program is running. Runtime code is not in the main program itself, but is needed for execution of the main program.
- context is usually within programming languages. for example, a C runtime is library code that is needed to implement the features of C itself.
  - ex. node is a runtime of js. .js code can't be executed without node library code.