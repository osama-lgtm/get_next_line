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
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			free(line);
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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = init_line(line);
	if (!line)
		return (NULL);
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
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
