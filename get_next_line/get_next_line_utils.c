/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:32:19 by soekim            #+#    #+#             */
/*   Updated: 2021/01/28 15:17:45 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dst, const char *src)
{
	if (!dst || !src)
		return (dst);
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	return (dst);
}

char	*ft_strncpy(char *dst, const char *src, int len)
{
	if (!dst || !src)
		return (dst);
	while (*src && --len >= 0)
	{
		*dst = *src;
		dst++;
		src++;
	}
	return (dst);
}

int		strdel_len(char *s, char delimiter)
{
	int		len;

	if (!s)
		return (0);
	len = 0;
	while (*s && *s != delimiter)
	{
		s++;
		len++;
	}
	return (len);
}

int		strcat_del(char **line, char *to_catenate, char delimiter)
{
	int		cat_len;
	char	*tab;
	char	*newstr;

	if (!to_catenate)
		return (0);
	cat_len = strdel_len(to_catenate, delimiter);
	if (!(newstr = (char *)malloc(strdel_len(*line, '\0') + cat_len + 1)))
		return (ERROR);
	tab = ft_strcpy(newstr, *line);
	tab = ft_strncpy(tab, to_catenate, cat_len);
	*tab = '\0';
	if (*line)
		free(*line);
	*line = newstr;
	return (cat_len);
}

int		get_oneline_and_next(char **next, char *buffer, char **temp, int fd)
{
	int is_oneline;
	int result;
	int catlen;

	is_oneline = 0;
	result = 1;
	while (!is_oneline)
	{
		if (!(*next))
		{
			if ((result = read(fd, buffer, BUFFER_SIZE)) == ERROR)
				return (ERROR);
			buffer[result] = '\0';
			*next = buffer;
		}
		if ((catlen = strcat_del(temp, *next, '\n')) == ERROR)
			return (ERROR);
		*next += catlen;
		if (**next == '\n' || result == END)
			is_oneline = 1;
		*next = (**next == '\n') ? (*next + 1) : (*next);
		if (**next == '\0')
			*next = NULL;
	}
	return (result);
}
