/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamleh <ojamleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:08:09 by ojamleh           #+#    #+#             */
/*   Updated: 2026/11/04 15:29:19 by ojamleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_nl(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*merge(char const *s1, char const *s2)
{
	static char	*s;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	i = len((char *)s1);
	j = len((char *)s2);
	s = malloc(sizeof(char) * (i + j + 1));
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}

int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char *seperate(char **remaining)
{
    int     i;
    char    *line;
    char    *temp;

    i = 0;
    while ((*remaining)[i] && (*remaining)[i] != '\n')
        i++;
    if ((*remaining)[i] == '\n')
        i++;
    line = substr(*remaining, 0, i);
    temp = substr(*remaining, i, len(*remaining) - i);
    free(*remaining);
    *remaining = temp;
    return (line);
}

char	*substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	i = 0;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	while (len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
