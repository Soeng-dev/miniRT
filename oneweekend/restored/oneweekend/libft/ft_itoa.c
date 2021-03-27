/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <soekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 03:59:01 by soekim            #+#    #+#             */
/*   Updated: 2020/11/20 15:40:40 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long long int	temp;
	int				len;
	char			*arr;

	temp = (n > 0) ? (long long int)n : -(long long int)(n);
	len = (n > 0) ? 0 : 1;
	while (temp != 0)
	{
		len++;
		temp /= 10;
	}
	if (!(arr = (char *)malloc(len + 1)))
		return (0);
	arr[0] = (n < 0) ? '-' : '0';
	temp = (n < 0) ? -(long long int)n : (long long int)n;
	arr[len] = '\0';
	while (temp > 0)
	{
		len--;
		arr[len] = temp % 10 + '0';
		temp /= 10;
	}
	return (arr);
}
