<div align="center">
  <img height="200" src="https://raw.githubusercontent.com/Benjamin-poisson/My_image_bank/refs/heads/main/gnl.png"  />
</div>

# Get Next Line - Line Reading Function

Get Next Line is a project that focuses on developing a function to read a single line from a file descriptor. This exercise introduces you to handling file input, managing static variables, and dealing with various buffer sizes in C.

## Status
<div align="center">
  <img height="200" src="https://raw.githubusercontent.com/Benjamin-poisson/My_image_bank/refs/heads/main/gnl_success.png"  />
</div>

## Objectives

The goal of this project is to implement a function that reads a line from a file descriptor. It will enhance your understanding of file I/O operations and static variables in C programming.

## Great resources

<li><a href="https://suspectedoceano.notion.site/get_next_line-b3fa44d60dc24817bfd6a642183a93a0">Notion's Oceano - Get_next_line</a></li>
<li><a href="https://github.com/xicodomingues/francinette">Get_next_ine Tester Francinette</a></li>

## Mandatory

<table>
  <tr>
    <th>Function name</th>
    <td>get_next_line</td>
  </tr>
  <tr>
    <th>Prototype</th>
    <td>char *get_next_line(int fd);</td>
  </tr>
  <tr>
    <th>Turn in files</th>
    <td>get_next_line.h, get_next_line.c, get_next_line_utils.c</td>
  </tr>
  <tr>
    <th>Makefile</th>
    <td>No</td>
  </tr>
  <tr>
    <th>External functions</th>
    <td>read, malloc, free</td>
  </tr>
  <tr>
    <th>Libft authorized</th>
    <td>No</td>
  </tr>
  <tr>
    <th>Description</th>
    <td>Implement a function to read a single line from a file descriptor.</td>
  </tr>
</table>

- The project must be written in C.
- The code should adhere to Norm.
- No global variables are allowed.
- Memory allocated on the heap must be freed when necessary; no leaks are tolerated.
- Provide a Makefile to compile the sources with flags -Wall, -Wextra, and -Werror.
- The Makefile must include rules for $(NAME), all, clean, fclean, and re.
- Include a rule for bonus features if applicable.
- Do not use the libft library or lseek().
- The program must compile with the option: `-D BUFFER_SIZE=n` to define the buffer size during compilation.

## Functionality

The `get_next_line` function should:

- Read one line at a time from the file descriptor until the end of the file.
- Return the line read, including the newline character, unless it's the end of the file and there is no newline.
- Return NULL if there's nothing left to read or if an error occurs.
- Work correctly for standard input as well as files.

The program must handle varying buffer sizes efficiently, with a default of 42. You should compile with and without the `-D BUFFER_SIZE` flag.

## Bonus

If the mandatory part is completed perfectly, consider the following bonus features:

- Implement `get_next_line` using a single static variable.
- Extend `get_next_line` to handle multiple file descriptors, allowing for simultaneous reading from different file descriptors.

Bonus files should be named with the `_bonus` suffix:

- `get_next_line_bonus.c`
- `get_next_line_bonus.h`
