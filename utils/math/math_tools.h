/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_TOOLS_H
# define MATH_TOOLS_H
# include <math.h>

/*
**		calculation
*/
double		dbl_min(double a, double b);
double		dbl_max(double a, double b);
double		get_valid_2nd_eqsol(double *coef, double ret_of_invalid, \
								int (*sol_is_valid)(long double sol));
/*
**		operation
*/
double		clamp(double n, double min, double max);
int			myrand(void);
double		absol(double n);

#endif
