/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_property.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	change_color(t_vector *target, char *cmd, int *is_error)
{
	t_vector	color;

	pass_charset(&cmd, " \t\n\v\f\r");
	if (!(*cmd))
		return (set_errflag(is_error));
	color = divide(read_vector(&cmd), 255);
	if (!is_valid_vector(color, 0, 1))
		return (set_errflag(is_error));
	else
		*target = color;
	return ;
}

void	change_material(t_material *target, char *cmd, int *is_error)
{
	int		idlen;

	pass_charset(&cmd, " \t\n\v\f\r");
	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "metal", idlen))
		target->scatter = metal;
	else if (!ft_strncmp(cmd, "lambertian", idlen))
		target->scatter = lambertian;
	else
		*is_error = TRUE;
	return ;
}

void	change_length(double *target, char *cmd, int *is_error)
{
	double	input;

	pass_charset(&cmd, " \t\n\v\f\r");
	if (!(*cmd))
		return (set_errflag(is_error));
	input = read_dbl(&cmd);
	if (input <= 0)
		return (set_errflag(is_error));
	*target = input;
	return ;
}
