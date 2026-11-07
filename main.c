#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
int main()
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    int fd3 = open("file3.txt", O_RDONLY);

    //int fd[] = {fd1, fd2,fd3};
    printf("%s",get_next_line(fd1));
    printf("%s",get_next_line(fd2));
    printf("%s",get_next_line(fd3));
    return 0;
}