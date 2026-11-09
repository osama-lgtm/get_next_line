/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamleh <ojamleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:08:09 by ojamleh           #+#    #+#             */
/*   Updated: 2026/11/04 15:29:19 by ojamleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	check_no_nl(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*merge(char const *s1, char const *s2)
{
	char	*s;
	size_t	i;
	size_t	j;

	s = malloc(sizeof(char) * (len((char *)s1) + len((char *)s2) + 1));
	if (!s)
	{
		free((char *)s1);
		return (NULL);
	}
	i = 0;
	while (s1 && s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	free((char *)s1);
	return (s);
}

int	len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*seperate(char **remaining)
{
	int		i;
	char	*line;
	char	*temp;

	i = 0;
	while ((*remaining)[i] && (*remaining)[i] != '\n')
		i++;
	if ((*remaining)[i] == '\n')
		i++;
	line = substr(*remaining, 0, i);
	temp = substr(*remaining, i, len(*remaining) - i);
	free(*remaining);
	*remaining = temp;
	if (!temp)
	{
		free(line);
		line = NULL;
	}
	else if (!line || temp[0] == '\0')
	{
		free(temp);
		*remaining = NULL;
	}
	return (line);
}

char	*substr(const char *s, unsigned int start, size_t len_sub)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	sub = malloc(len_sub + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len_sub && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
