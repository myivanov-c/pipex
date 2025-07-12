# Pipex – Shell-like Pipeline Reproduction in C

**42 Project | ✅ Grade: 125%**  
**Goal:** Recreate shell pipelines using `fork`, `pipe`, and `execve` in C, simulating the behavior of Bash commands.

---

## Overview

This project simulates the following Bash pipeline:

```bash
<infile cmd1 | cmd2 >outfile
```

It executes two or more commands connected via pipes.  
The program handles process creation, file redirection, pipe chaining, and command path resolution.

I passed with the maximum grade (125%) after facing 3 evaluations — including one that tested my code with **80 piped commands**, all handled without leaks or crashes.

---

## Features Implemented

| Component        | Description |
|------------------|-------------|
| `fork()`         | Process creation for each command |
| `execve()`       | Executes the command binary |
| `pipe()`         | Connects stdout of one command to stdin of the next |
| `dup2()`         | Redirects input/output file descriptors |
| `access()`       | Checks if command exists and is executable |
| `PATH` parsing   | Locates command binaries using environment variables |
| Error handling   | Custom error messages aligned with Bash |
| Memory safety    | No leaks (tested with Valgrind) |
| Bonus            | Support for unlimited commands + here_doc

---

## Usage

### ➤ Mandatory

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Example:

```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```

### ➤ Bonus (Multiple pipes)

```bash
./pipex infile "cmd1" "cmd2" "cmd3" ... outfile
```

### ➤ Bonus (here_doc)

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```

Example:

```bash
./pipex here_doc END "cat" "wc -l" result.txt
```

---

## 🔧 Compilation

```bash
make            # Compile the project
make clean      # Remove .o files
make fclean     # Remove .o files and binary
make re         # Recompile everything
```

> 💡 The project uses a local `libft/` included in this repository. No need to install anything else!

---

## What I Learned

- Deep understanding of UNIX process management
- File descriptors, piping and inter-process communication
- Implementing real shell behavior (command parsing, path resolution)
- Writing defensive and robust C code with malloc protection
- How to explain and defend complex code during evaluation
- How to simulate edge cases like a 80-command pipeline with no leaks

---

## Evaluation Highlights

*"Great code. Managed to explain everything. Keep up the great work!"*  
 *"Very clean code. Good luck with Push_swap!"*  
 *"Pipeline with 80 commands passed. No memory leaks."*

> ✅ Evaluation: 3/3  
> ✅ Grade: **125%**

---

## Project Structure

```
pipex/
├── libft/                 # Custom C library (included)
├── main.c                 # Main entry
├── pipex.h                # Header file
├── Makefile               # Compilation script
├── fork_and_wait.c        # Forking logic
├── get_cmd_path.c         # Path resolution
├── open_files.c           # infile/outfile handlers
├── handle_cmd_errors.c    # Error messages
├── pipeline.c             # Command loop
├── pipes_helper.c         # Pipe utils
```

---

## Author

**Mykyta Ivanov**  
Student at [42 Lisboa](https://42lisboa.com)  
- GitHub: [@myivanov-c](https://github.com/myivanov-c)  
- Twitter: [@myivanov_c](https://x.com/myivanov_c)

---

## License

This project is open-source and free to use for learning purposes.

