#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFF_SIZE
# define BUFF_SIZE 4
#endif
/*
osama
hamad
fares
*/
int find_nl(int fd,char *line)
{
        int i;
        static int bytes_read;
        static int count;

        i = 0;
        bytes_read += read(fd, line + bytes_read, BUFF_SIZE);
        while (i < BUFF_SIZE && bytes_read > 0)
        {
                if (line[i] == '\n')
                        return (count);
                i++;
                BUFF_SIZE--;
        }
        count += i;
        line[BUFF_SIZE + 1] = '\0';
        return (count);
}

char *get_next_line(int fd)
{
    static char *line;
    char *temp;
    int bytes_read;
    int new_line;

    if (fd < 0 || fd > 1023 ||BUFF_SIZE <= 0)
        return (NULL);
    line = malloc(sizeof(char) * (BUFF_SIZE + 1));
    line[BUFF_SIZE + 1] = '\0';
    new_line = find_nl(fd,line);
    line = malloc(sizeof(char) * (new_line + 1));
    line[new_line] = '\0';
    read(fd, line, new_line);
    return (line);
}

// char *expand_line(char *line, int fd)
// {
//     char *temp;

//     temp = malloc(sizeof(char) * (BUFF_SIZE + 1));
//     temp[BUFF_SIZE + 1] = '\0';
//     read(fd, temp + BUFF_SIZE * i, BUFF_SIZE);
//     if (check_nl(temp))

// }
int main(void)
{
    char *Buff;
    int fd;
    int i;

    fd = open("hello.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    printf("%s",get_next_line(fd));

    free(Buff);
    close(fd);
    return (0);
}