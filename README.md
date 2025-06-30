# Minishell

A custom implementation of a basic UNIX shell, created as part of the 42 school curriculum. This project aims to replicate a subset of the functionality of the `bash` shell, including command execution, environment variable handling, I/O redirections, and pipes.

## Features

*   **Command Execution**: Executes simple and complex commands from the `PATH`.
*   **Built-in Commands**:
    *   `echo` with the `-n` option
    *   `cd` with relative or absolute paths
    *   `pwd` to display the current working directory
    *   `export` to manage environment variables
    *   `unset` to remove environment variables
    *   `env` to list environment variables
    *   `exit` to terminate the shell
*   **Pipes (`|`)**: Chains commands together, redirecting the standard output of one command to the standard input of the next.
*   **I/O Redirections**:
    *   `<` : Redirect standard input
    *   `>` : Redirect standard output
    *   `<<`: Heredoc for multi-line input
    *   `>>`: Append to a file
*   **Environment Variable Expansion**: Expands variables prefixed with `$` (e.g., `$USER`).
*   **Signal Handling**: Gracefully handles `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.

## Getting Started

### Prerequisites

*   A C compiler (e.g., `gcc` or `clang`)
*   `make`
*   The `readline` library. On macOS, you can install it with Homebrew:
    ```sh
    brew install readline
    ```

### Building the Project

1.  Clone the repository:
    ```sh
    git clone <your-repo-url>
    cd Minishell
    ```

2.  Compile the project using the Makefile:
    ```sh
    make
    ```
    This will create the `minishell` executable.

## Usage

To start the shell, run the compiled executable from your terminal:

```sh
./minishell
```

You will be greeted with a prompt, ready to accept commands.

### Examples

```sh
> echo "Hello, World!"
Hello, World!
> ls -l | grep "src" | wc -l
> cat < infile > outfile
> export MY_VAR="test"
> echo $MY_VAR
test
```

## Cleaning Up

To remove the object files:
```sh
make clean
```

To remove the object files and the `minishell` executable:
```sh
make fclean
```

To re-compile the project from scratch:
```sh
make re
```
