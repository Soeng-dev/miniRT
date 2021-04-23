/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_figures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	change_plane(t_plane *pl, char *cmd, int *is_error)
{
	int			idlen;

	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "translate", idlen))
		translate(&pl->p, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "rotate", idlen))
		rotate(&pl->normal, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "color", idlen))
		change_color(&pl->material.albedo, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "material", idlen))
		change_material(&pl->material, cmd + idlen, is_error);
	else
		*is_error = TRUE;
	return ;
}

void	change_sphere(t_sphere *sp, char *cmd, int *is_error)
{
	int			idlen;

	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "translate", idlen))
		translate(&sp->ctr, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "color", idlen))
		change_color(&sp->material.albedo, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "material", idlen))
		change_material(&sp->material, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "radius", idlen))
		change_length(&sp->r, cmd + idlen, is_error);
	else
		*is_error = TRUE;
	return ;
}

void	change_square(t_square *sq, char *cmd, int *is_error)
{
	int			idlen;
	t_plane		pl;

	init_plane(&pl, sq->ctr, sq->normal, &sq->material);
	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "translate", idlen))
		translate(&pl.p, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "rotate", idlen))
	{
		rotate_square(sq, &pl.normal, cmd + idlen, is_error);
		return ;
	}
	else if (!ft_strncmp(cmd, "color", idlen))
		change_color(&pl.material.albedo, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "material", idlen))
		change_material(&pl.material, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "side_size", idlen))
	{
		change_length(&sq->half_size, cmd + idlen, is_error);
		sq->half_size /= 2.0;
	}
	else
		*is_error = TRUE;
	if (!(*is_error))
		init_square(sq, &pl, 2 * sq->half_size);
}

void	change_cylinder(t_cylinder *cyl, char *cmd, int *is_error)
{
	int			idlen;
	t_plane		changed;

	changed = cyl->bottom;
	changed.normal = multi(cyl->bottom.normal, -1);
	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "translate", idlen))
		translate(&changed.p, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "rotate", idlen))
		rotate(&changed.normal, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "color", idlen))
		change_color(&changed.material.albedo, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "material", idlen))
		change_material(&changed.material, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "radius", idlen))
		change_length(&cyl->r, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "height", idlen))
		change_length(&cyl->height, cmd + idlen, is_error);
	else
		*is_error = TRUE;
	if (*is_error)
		return ;
	init_cylinder(cyl, &changed, cyl->r, cyl->height);
	return ;
}

void	change_triangle(t_triangle *tr, char *cmd, int *is_error)
{
	int			idlen;

	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "translate", idlen))
		translate(&tr->p, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "rotate", idlen))
	{
		rotate(&tr->edge1, cmd + idlen, is_error);
		rotate(&tr->edge2, cmd + idlen, is_error);
		rotate(&tr->normal, cmd + idlen, is_error);
	}
	else if (!ft_strncmp(cmd, "color", idlen))
		change_color(&tr->material.albedo, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "material", idlen))
		change_material(&tr->material, cmd + idlen, is_error);
	else
		*is_error = TRUE;
	return ;
}
