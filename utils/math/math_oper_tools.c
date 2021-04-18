/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_calc_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:06:51 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 11:31:04 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_tools.h"

double		clamp(double n, double min, double max)
{
	if (n < min)
		return (min);
	else if (n > max)
		return (max);
	else
		return (n);
}

int			myrand(void)
{
	static int	r;

	r = (109 * r + 1021) % 32768;
	return (r);
}

double		absol(double n)
{
	if (n > 0)
		return (n);
	else
		return (-n);
}
