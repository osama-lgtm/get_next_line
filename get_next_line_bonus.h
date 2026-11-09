/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamleh <ojamleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:12:47 by ojamleh           #+#    #+#             */
/*   Updated: 2026/11/07 13:30:02 by ojamleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 67
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int *fd);
char	*merge(char const *s1, char const *s2);
int		len(char *str);
char	*seperate(char **remaining);
int		check_no_nl(char *line);
char	*substr(const char *s, unsigned int start, size_t len_sub);

#endif
