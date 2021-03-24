/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:06:51 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 11:31:04 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double		max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

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
	static int	r = 13;

	r = (109 * r+ 1021) % 32768;
	return (r);
}
