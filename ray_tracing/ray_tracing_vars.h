/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_vars.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:29:17 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:48:22 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_VARS_H
# define RAY_TRACING_VARS_H

struct	s_ray
{
	t_vector				pos;
	t_vector				dir;
};
typedef struct s_ray		t_ray;

struct	s_material
{
	t_vector	albedo;
	double		fuzz;
	int			(*scatter)(const t_ray*, void *, t_ray *);
};
typedef struct s_material	t_material;

struct	s_hit_record
{
	t_vector	pos;
	t_vector	normal;
	double		time;
	int			is_front_face;
	t_material	*material;
	void		*object;
};
typedef struct s_hit_record	t_hit_record;

struct	s_sphere
{
	t_vector	ctr;
	double		r;
	t_material	material;
};
typedef struct s_sphere		t_sphere;

struct	s_plane
{
	t_vector	p;
	t_vector	normal;
	t_material	material;
};
typedef struct s_plane		t_plane;

struct	s_square
{
	t_vector	ctr;
	t_vector	normal;
	t_vector	u;
	t_vector	v;
	double		half_size;
	t_material	material;
};
typedef struct s_square		t_square;

struct	s_cylinder
{
	double		r;
	double		height;
	t_plane		bottom;
	t_plane		top;
	t_vector	normal;
	t_material	material;
};
typedef struct s_cylinder	t_cylinder;

struct	s_triangle
{
	t_vector	p;
	t_vector	edge1;
	t_vector	edge2;
	t_vector	normal;
	t_material	material;
};
typedef struct s_triangle	t_triangle;

#endif
