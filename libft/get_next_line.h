/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:35:21 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/16 15:42:36 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>

int		gnl_strlen(char *str);

char	*gnl_substrchr(char *s, char *to_find);
char	*gnl_strdup(char *s);
char	*gnl_strjoin(char *s1, char *s2);
char	*filled_line(int fd, char *buffer, char *line, char *lim);
char	*adjust_line(char *line, char *lim);
char	*left_char(char *line, char *lim);
char	*get_next_line(int fd, char *lim);

void	*gnl_calloc(size_t nmemb, size_t size);

#endif
