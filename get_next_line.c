/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamleh <ojamleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:12:47 by ojamleh           #+#    #+#             */
/*   Updated: 2026/11/04 15:25:03 by ojamleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		*temp;
	int			i;

	i = 0;
	if (fd < 0 || fd > 1023 || BUFF_SIZE <= 0)
		return (NULL);
	line = malloc((BUFF_SIZE + 1));
	line[BUFF_SIZE + 1] = '\0';
	read(fd, line, BUFF_SIZE);
	temp = malloc(BUFF_SIZE + 1);
	while (check_nl(line) == 0)
	{
		read(fd, temp, BUFF_SIZE);
		temp[BUFF_SIZE + 1] = '\0';
		line = merge(line, temp);
	}
	free(temp);
	temp = seperate(&line);
	return (temp);
}

#include <stdio.h>
#include <fcntl.h>
int main(void)
{
    int fd;

    fd = open("hello.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    printf("%s",get_next_line(fd));
    // printf("%s",get_next_line(fd));
	// printf("%s",get_next_line(fd));

    close(fd);
    return (0);
}
