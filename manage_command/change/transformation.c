/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	translate(t_vector *pos, char *cmd, int *is_error)
{
	t_vector	input;

	pass_charset(&cmd, " \t\n\v\f\r");
	if (!(*cmd))
		return (set_errflag(is_error));
	input = read_vector(&cmd, is_error);
	*pos = add(*pos, input);
	return ;
}

void	rotate(t_vector *target, char *cmd, int *is_error)
{
	t_vector	axis;
	double		angle;

	pass_charset(&cmd, " \t\n\v\f\r");
	if (!(*cmd))
		return (set_errflag(is_error));
	axis = read_vector(&cmd, is_error);
	if (vector_is_same(axis, get_vector(0, 0, 0)))
		return (set_errflag(is_error));
	pass_charset(&cmd, " \t\n\v\f\r");
	if (!ft_isdigit(*cmd) && (*cmd != '-' && !ft_isdigit(*(cmd + 1))))
		return (set_errflag(is_error));
	angle = read_dbl(&cmd, is_error) * (M_PI / 180);
	*target = rotate_vector(*target, axis, angle);
	return ;
}

void	rotate_square(t_square *sq, char *cmd, int *is_error)
{
	t_vector	axis;
	char		*temp;

	temp = cmd;
	pass_charset(&temp, " \t\n\v\f\r");
	if (!(*temp))
		return (set_errflag(is_error));
	axis = normalize(read_vector(&temp, is_error));
	sq->normal = normalize(sq->normal);
	if (absol(dot(sq->normal, axis))  == 1.0)
	{
		rotate(&sq->u, cmd, is_error);
		rotate(&sq->v, cmd, is_error);
	}
	else
		rotate(&sq->normal, cmd, is_error);
	return ;
}
