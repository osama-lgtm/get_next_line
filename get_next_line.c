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

static char	*init_line(char *line)
{
	if (!line)
	{
		line = malloc(1);
		if (line)
			line[0] = '\0';
	}
	return (line);
}

static char	*ft_read_loop(int fd, char *line, char *temp)
{
	int	bytes_read;

	bytes_read = 1;
	while (check_no_nl(line) == 1 && bytes_read != 0)
	{
		bytes_read = read(fd, temp, BUFF_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		line = merge(line, temp);
	}
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*temp;

	if (fd < 0 || fd > 1023 || BUFF_SIZE <= 0)
		return (NULL);
	line = init_line(line);
	if (!line)
		return (NULL);
	temp = malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!temp)
		return (NULL);
	line = ft_read_loop(fd, line, temp);
	if (!line || line[0] == '\0')
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	return (seperate(&line));
}
/*
#include <stdio.h>
#include <fcntl.h>
int main()
{
        int fd;
        char *line;

        line = NULL;
        puts(line);
        fd = open("hello.txt", O_RDONLY);
        printf("%s\n", line);
        // printf("%s", get_next_line(fd));
        // printf("%s", get_next_line(fd));
        // printf("%s", get_next_line(fd));
        // printf("%s", get_next_line(fd));
        // printf("%s", get_next_line(fd));
        // printf("%s", get_next_line(fd));
        // printf("\n");
        return 0;
}*/
