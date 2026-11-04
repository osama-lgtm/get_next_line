

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFF_SIZE
# define BUFF_SIZE 4
#endif

#include <unistd.h>
# include <stdlib.h>
char *ft_substr(char const *s, unsigned int start, size_t len);
char *get_next_line(int fd);
char *merge(char const *s1, char const *s2);
int len(char *str);
char *seperate(char **remain);
int check_nl(char *line);
char   *substr(const char *s1, unsigned int start, size_t len);
#endif