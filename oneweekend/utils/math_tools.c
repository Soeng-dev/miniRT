/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:06:51 by soekim            #+#    #+#             */
/*   Updated: 2021/03/10 16:18:46 by soekim           ###   ########.fr       */
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
