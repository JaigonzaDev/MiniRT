# Libft - Your First C Library
## Overview
Libft is a project at 42 that requires building a C library from scratch. The purpose is to implement several general-purpose functions that will be useful throughout your cursus, mimicking functions from the standard C library (libc) and adding some additional utility functions. The project is an excellent way to deepen your understanding of the C language, memory management, and how basic functions in standard libraries work.

## Project Objectives
- Understand the mechanics of basic libc functions.
- Learn to implement common C functions without relying on external libraries.
- Gain experience in managing memory dynamically.
- Create a reusable library that will assist in future projects.
## Project Requirements
- Language: C
- Compilation Flags: -Wall -Wextra -Werror
- Output: A static library libft.a
- Makefile: Required with rules all, clean, fclean, re, and bonus.
## Learning Goals
- Understand how standard functions like strlen, strcpy, memset, etc., are implemented.
- Develop better memory management skills, preventing memory leaks and handling dynamic allocation correctly.
- Apply advanced function handling (function pointers, iterating over structures).
- Improve your use of Makefiles and shell commands.
## Instructions
### Part 1: Recreating libc Functions
You will implement the following functions, which mimic the behavior of standard C library functions:

- Character checks and transformations: ft_isalpha, ft_isdigit, ft_isalnum, ft_isascii, ft_isprint, ft_toupper, ft_tolower
- String manipulation: ft_strlen, ft_strlcpy, ft_strlcat, ft_strchr, ft_strrchr, ft_strncmp, ft_strnstr, ft_strdup
- Memory manipulation: ft_memset, ft_bzero, ft_memcpy, ft_memmove, ft_memchr, ft_memcmp
- String to integer conversion: ft_atoi
- Memory allocation: ft_calloc
### Part 2: Additional Utility Functions
These functions add extended functionality beyond what's available in the standard C library:

- String operations: ft_substr, ft_strjoin, ft_strtrim, ft_split
- Integer to string conversion: ft_itoa
- String iteration and manipulation with function pointers: ft_strmapi, ft_striteri
- File descriptor output functions: ft_putchar_fd, ft_putstr_fd, ft_putendl_fd, ft_putnbr_fd
### Bonus Part: Linked List Functions
If you complete the mandatory part, you can extend your library with linked list management functions:

ft_lstnew, ft_lstadd_front, ft_lstsize, ft_lstlast, ft_lstadd_back, ft_lstdelone, ft_lstclear, ft_lstiter, ft_lstmap
## Evaluation Criteria
- All mandatory functions must compile and behave as expected.
- Memory management will be strictly evaluated, especially with dynamic allocation (use of malloc).
- Bonus functions will only be evaluated if the mandatory part is perfect.
