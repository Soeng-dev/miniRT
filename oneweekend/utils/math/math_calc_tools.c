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

double		dbl_min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double		dbl_max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double		get_valid_2nd_eqsol(double *coef, double ret_of_invalid, \
								int (*sol_is_valid)(long double sol))
{
	double	sol;
	double	discriminant;
	double	sqrt_dis;

	discriminant = coef[1] * coef[1] - 4 * coef[0] * coef[2];
	if (discriminant < 0)
		return (ret_of_invalid);
	sqrt_dis = sqrt(discriminant);
	sol = (-coef[1] - sqrt_dis) / (2 * coef[0]);
	if (sol_is_valid(sol))
		return (sol);
	sol = (-coef[1] + sqrt_dis) / (2 * coef[0]);
	if (sol_is_valid(sol))
		return (sol);
	else
		return (ret_of_invalid);
}
