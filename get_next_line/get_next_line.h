/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:32:19 by soekim            #+#    #+#             */
/*   Updated: 2021/01/27 16:17:54 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libft.h"

# define ERROR			-1
# define END			0
# define SUCCESS		1
# define BUFFER_SIZE	8

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dst, const char *src);
int		strdel_len(char *s, char delimiter);
int		strcat_del(char **line, char *to_catenate, char delimiter);
int		min(int a, int b);
int		get_next_line(int fd, char **line);
int		get_oneline_and_next(char **next, char *buffer, char **temp, int fd);
#endif
