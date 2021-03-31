/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:32:19 by soekim            #+#    #+#             */
/*   Updated: 2021/01/28 15:18:21 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	int		line_len;
	int		cat_len;
	char	*tab;
	char	*newstr;

	if (!to_catenate)
		return (0);
	line_len = strdel_len(*line, '\0');
	cat_len = strdel_len(to_catenate, delimiter);
	if (!(newstr = (char *)malloc(line_len + cat_len + 1)))
		return (ERROR);
	tab = ft_strncpy(newstr, *line, line_len);
	tab = ft_strncpy(tab, to_catenate, cat_len);
	*tab = '\0';
	if (*line)
		free(*line);
	*line = newstr;
	return (cat_len);
}

void	*ft_memmove(void *dst, const void *src, int len)
{
	char	*dst_tab;
	char	*src_tab;

	if (!src)
		return (NULL);
	src_tab = (char *)src;
	dst_tab = (char *)dst;
	if (dst_tab > src_tab)
	{
		dst_tab += len;
		src_tab += len;
		while (--len >= 0)
			*(--dst_tab) = *(--src_tab);
	}
	else
	{
		while (--len >= 0)
			*(dst_tab++) = *(src_tab++);
	}
	return (dst);
}

int		get_oneline_and_next(char **next, char *backup, char **temp, int fd)
{
	int is_oneline;
	int result;
	int catlen;

	is_oneline = 0;
	result = 1;
	while (!is_oneline)
	{
		if (!backup[0])
		{
			if ((result = read(fd, backup, BUFFER_SIZE)) == ERROR)
				return (ERROR);
			backup[result] = '\0';
			*next = backup;
		}
		if ((catlen = strcat_del(temp, *next, '\n')) == ERROR)
			return (ERROR);
		*next += catlen;
		if (**next == '\n' || result == END)
			is_oneline = 1;
		*next = (**next == '\n') ? (*next + 1) : (*next);
		if (**next == '\0')
			backup[0] = '\0';
	}
	return (result);
}
