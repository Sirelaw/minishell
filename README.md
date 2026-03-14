# Minishell: A Miniature UNIX Shell
Minishell is a compact partly POSIX compatibly shell supporting the most basic commands and functionalities. </br>
Minishell is able to execute binaries, read from files, redirect output as well as navigating the file system.

## The Engineering Perspective

In embedded systems, understanding how an Operating System manages processes and communication is vital. Minishell demonstrates my expertise in:

- Process Management: Utilizing fork, execve, and waitpid to manage lifecycle and execution.

- Inter-Process Communication (IPC): Implementing pipes (|) to redirect data flow between decoupled processes.

- Signal Handling: Managing asynchronous events like Ctrl-C, Ctrl-D, and Ctrl-\ to ensure system stability.

- File Descriptor Manipulation: Handling redirections (>, <, >>, <<) by manipulating system-level file descriptors.

## Features Implementation

**1. Command Execution & Path Finding**

The shell searches for executables in the PATH environment variable, handles absolute and relative paths, and executes them with proper argument vectors.

**2. Built-in Commands**

We implemented several essential shell built-ins from scratch:

- ```echo``` (with -n option)
- ```cd``` (with relative and absolute paths)
- ```env```
- ```exit```
- ```export```
- ```pwd```
- ```unset```

**3. Operators**

- ```>```
- ```<```
- ```>>```
- ```<<```
- ```|```


**3. Syntax Parsing & Lexing**

The project includes a custom-built lexer and parser to handle:

- Quoting: Correctly interpreting single (') and double (") quotes, including environment variable expansion inside double quotes.

- Redirections: Directing output and input to/from files.

- Pipes: Enabling complex command chains where the output of one command becomes the input of the next.

## Technical Challenges: Memory & Leaks

As a shell is a long-running process, memory management is critical. We utilized Valgrind throughout development to ensure that all allocated memory is properly freed upon command completion or shell exit, and that no file descriptors are left "leaking" open.

## Compile
Minishell is dependent on ```GNU readline```.</br>

```bash
git clone https://github.com/Sirelaw/minishell.git
cd minishell
make
./minishell
```
