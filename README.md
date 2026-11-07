*This project has been created as part of the 42 curriculum by ojamleh*

# get_next_line

## Description

`get_next_line` is a C function that returns **one line at a time** from a file
descriptor each time it is called. A "line" ends with `\n` (which is kept in the
returned string) or with the end of the file if the last line has no trailing
newline.

```c
char *get_next_line(int fd);
```

- Returns the next line, including the `\n` when there is one.
- Returns `NULL` when there is nothing left to read, or on error
  (invalid `fd`, `read` failure, or `malloc` failure).
- The returned string is allocated with `malloc`; the caller must `free` it.

The goal of the project is to learn about **static variables**, **file
descriptors**, the `read` system call, and careful **dynamic memory
management** (no leaks, no undefined behavior), while working with an
arbitrary `BUFFER_SIZE` chosen at compile time.

### Files

| File | Content |
|------|---------|
| `get_next_line.h` | Header: `BUFFER_SIZE` default, includes, prototypes |
| `get_next_line.c` | `get_next_line`, plus the static helpers `init_line` and `ft_read_loop` |
| `get_next_line_utils.c` | `check_no_nl`, `merge`, `len`, `seperate`, `substr` |

## Instructions

### Compilation

The buffer size is set at compile time with `-D BUFFER_SIZE=n`. If it is not
given, the header defaults it to `42`.

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

`main.c` is your own test file (it is not part of the project). Example:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("hello.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

### Execution

```sh
./gnl
```

### Testing suggestions

- Try several buffer sizes: `-D BUFFER_SIZE=1`, `4`, `42`, `10000000`.
- Try an empty file, a file with only `\n` characters, a file whose last line
  has no `\n`, and a file with a very long line.
- Check for leaks, e.g. `valgrind --leak-check=full ./gnl` or compile with
  `-fsanitize=address`.

## Algorithm

**Chosen approach: a static "stash" string plus chunked reads.**

1. A `static char *line` (the "stash") keeps whatever has been read from the
   file but not yet returned. Because it is `static`, it survives between
   calls. `init_line` makes sure it starts as an empty string.
2. `ft_read_loop` repeatedly calls `read(fd, temp, BUFFER_SIZE)` and appends
   the chunk to the stash (`merge`) **until the stash contains a `\n`**
   (checked by `check_no_nl`, which returns 1 while there is no newline)
   **or `read` returns 0 (end of file)**.
3. If the stash is empty after reading, there is nothing left: the stash is
   freed and `NULL` is returned.
4. Otherwise `seperate` scans for the first `\n`, copies everything up to
   and including it into a new string (the line that is returned), and copies
   the remainder into a new stash for the next call. The old stash is freed.
5. If `read` fails (`-1`), or any `malloc` fails, everything allocated is freed,
   the stash is reset to `NULL`, and `NULL` is returned.

### Why this algorithm?

- **Reads only as much as needed.** It stops reading as soon as a full line is
  available, so it never loads a whole file into memory, and it works on any
  file descriptor, including pipes and standard input, where seeking is
  impossible.
- **Independent of `BUFFER_SIZE`.** Lines longer than the buffer are handled by
  looping, and lines shorter than the buffer are handled by keeping the extra
  data in the stash. It behaves the same from `BUFFER_SIZE=1` to very large
  values.
- **No fixed maximum line length.** The stash grows with `malloc` as needed.
- **Simple and safe memory ownership.** `merge` always frees the old
  stash (even when its own `malloc` fails), and the temporary read buffer is
  freed on every path, which avoids leaks and double frees.
- **Trade-off.** Joining strings copies the stash on each read, so a very long
  line with a tiny `BUFFER_SIZE` costs more copying (quadratic in the worst
  case). This is acceptable for the project and keeps the code easy to verify.

## Resources

- GNU C documentation on macros (`-D` and preprocessor macros such as
  `BUFFER_SIZE`)
- `man 2 read`
- Stack Overflow discussions on `static` variables and file reading in C

### Use of AI

AI (Claude) was used for:

- **Code review** of my first version of `get_next_line.c`,
  `get_next_line_utils.c` and `get_next_line.h`, which pointed out the wrong
  macro name (`BUFF_SIZE` instead of `BUFFER_SIZE`), a leftover `main`, a memory
  leak on `read` errors, unchecked `malloc` results and header problems.
- **Applying those fixes** and drafting this README from the final code.

I reviewed, tested (multiple buffer sizes, edge-case files, AddressSanitizer,
`norminette`) and understand all of the submitted code.
