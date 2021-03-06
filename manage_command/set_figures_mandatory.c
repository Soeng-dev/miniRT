/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_figure_mandatory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manage_command.h"

void	set_sphere(char *s, int *is_error)
{
	t_material	mat;
	t_vector	center;
	double		r;

	center = read_vector(&s, is_error);
	r = read_dbl(&s, is_error) / 2.0;
	mat.albedo = divide(read_vector(&s, is_error), 255);
	if (!is_valid_vector(mat.albedo, 0, 1.0) || r <= 0)
		return (set_errflag(is_error));
	set_fuzz_scatter(s, &mat, is_error);
	if (*is_error)
		return ;
	make_sphere(center, r, &mat);
	return ;
}

void	set_plane(char *s, int *is_error)
{
	t_vector	p;
	t_vector	normal;
	t_material	mat;

	p = read_vector(&s, is_error);
	normal = read_vector(&s, is_error);
	if (absol(dot(normal, normal) - 1.0) > 0.1)
		return (set_errflag(is_error));
	normal = normalize(normal);
	mat.albedo = divide(read_vector(&s, is_error), 255.0);
	if (!is_valid_vector(mat.albedo, 0, 1.0))
		return (set_errflag(is_error));
	set_fuzz_scatter(s, &mat, is_error);
	if (*is_error)
		return ;
	make_plane(p, normal, &mat);
	return ;
}

void	set_square(char *s, int *is_error)
{
	t_plane	pl;
	double	side_size;

	pl.p = read_vector(&s, is_error);
	pl.normal = read_vector(&s, is_error);
	if (absol(dot(pl.normal, pl.normal) - 1.0) > 0.1)
		return (set_errflag(is_error));
	pl.normal = normalize(pl.normal);
	side_size = read_dbl(&s, is_error);
	pl.material.albedo = divide(read_vector(&s, is_error), 255);
	if (!is_valid_vector(pl.material.albedo, 0, 1.0) || side_size <= 0)
		return (set_errflag(is_error));
	set_fuzz_scatter(s, &pl.material, is_error);
	if (*is_error)
		return ;
	make_square(&pl, side_size);
	return ;
}

void	set_triangle(char *s, int *is_error)
{
	t_vector	first;
	t_vector	second;
	t_vector	third;
	t_material	mat;

	first = read_vector(&s, is_error);
	second = read_vector(&s, is_error);
	third = read_vector(&s, is_error);
	mat.albedo = divide(read_vector(&s, is_error), 255);
	if (!is_valid_vector(mat.albedo, 0, 1.0))
		return (set_errflag(is_error));
	set_fuzz_scatter(s, &mat, is_error);
	if (*is_error)
		return ;
	make_triangle(first, second, third, &mat);
	return ;
}

void	set_cylinder(char *s, int *is_error)
{
	t_plane		bottom;
	double		r;
	double		height;

	bottom.p = read_vector(&s, is_error);
	bottom.normal = read_vector(&s, is_error);
	if (absol(dot(bottom.normal, bottom.normal) - 1.0) > 0.1)
		return (set_errflag(is_error));
	bottom.normal = normalize(bottom.normal);
	r = read_dbl(&s, is_error) / 2.0;
	height = read_dbl(&s, is_error);
	bottom.material.albedo = divide(read_vector(&s, is_error), 255.0);
	if (!is_valid_vector(bottom.material.albedo, 0, 1.0) \
		|| r <= 0 || height <= 0)
		return (set_errflag(is_error));
	set_fuzz_scatter(s, &bottom.material, is_error);
	if (*is_error)
		return ;
	make_cylinder(&bottom, r, height);
	return ;
}
