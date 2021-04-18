/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:06:56 by soekim            #+#    #+#             */
/*   Updated: 2020/11/22 18:21:08 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_element(const char *set, char c)
{
	if (!set)
		return (-1);
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*ret;

	if (!s1)
		return (0);
	while (is_element(set, *s1) && *s1)
		s1++;
	len = ft_strlen(s1);
	while (--len > 0 && is_element(set, s1[len]))
		;
	len++;
	if (!(ret = (char *)malloc(len + 1)))
		return ((void *)0);
	ret[len] = '\0';
	while (--len >= 0)
		ret[len] = s1[len];
	return (ret);
}
