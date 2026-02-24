# Get Next Line

## Overview
The **Get Next Line** project at 42 involves creating a function that returns a line read from a file descriptor. This task is essential for handling data input in C and is useful for learning about memory management and the use of static variables.

## Project Objectives
- Learn how to read lines from a file descriptor.
- Understand the concept of static variables in C and their application in functions.
- Develop skills in dynamic memory management.
- Create a reusable function that facilitates line reading in future projects.

## Project Requirements
- **Language:** C
- **Compilation Flags:** `-Wall -Wextra -Werror`
- **Output:** A header file `get_next_line.h` and an implementation in `get_next_line.c` and `get_next_line_utils.c`.
- **Makefile:** Required with rules `all`, `clean`, `fclean`, `re`, and `bonus`.

## Learning Goals
- Understand how functions for reading lines from files are implemented in C.
- Improve memory management skills by avoiding leaks and handling dynamic allocation correctly.
- Learn to work with buffers and the importance of buffer size.
- Enhance the use of Makefiles and shell commands.

## Instructions
### Mandatory Part: Main Function
Implement the following function to read lines from a file descriptor:

- **Main Function:** `char *get_next_line(int fd);`
  - **Parameters:** 
    - `fd`: File descriptor from which to read.
  - **Return Value:** 
    - The line read if successful.
    - `NULL` in case of an error or if there is no more content to read.

#### Utility Functions
- **gnl_strlen:** Returns the length of a string.
- **ft_strjoin:** Joins two strings into a new one.
- **gnl_strchr:** Checks if a character is present in a string.
- **ft_strlcpy:** Copies a string into another with a maximum size.
- **initialize_buffer:** Initializes a buffer to empty.

### Bonus Part: Additional Features
- Implement `get_next_line` using only a single static variable.
- Allow handling multiple file descriptors simultaneously.
- Add files suffixed with `_bonus.c` and `_bonus.h` for the additional functions.

## Evaluation Criteria
- All mandatory functions must compile and behave as expected.
- Memory management will be strictly evaluated, especially with dynamic allocation (use of `malloc`).
- Bonus functions will only be evaluated if the mandatory part is complete and error-free.
