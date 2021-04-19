/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:29:17 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:48:22 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_H
# define RAY_TRACING_H

# define NOT_HIT	DBL_MAX
# define T_MAX		DBL_MAX
# define T_MIN		0.00001

# define PLANE 		0
# define SPHERE 	1
# define CYLINDER	2
# define SQUARE		3
# define TRIANGLE	4
# define NUM_OF_FIGTYPES 5

# define LIGHT	6
# define CAMERA	7
# define FILTER 8

# define TRUE	1
# define FALSE	0

# include <float.h>
# include "../libft/libft.h"
# include "../utils/math/myvector.h"
# include "camera.h"
# include "light.h"
# include "ray_tracing_vars.h"

/*
**		global vars used in ray tracing
*/
t_list		*g_figures[NUM_OF_FIGTYPES];
t_lightdata	g_light_data;

/*
**		ray
*/
void		init_ray(t_ray *ray, t_vector pos, t_vector dir);
t_ray		get_ray(t_vector pos, t_vector dir);
t_vector	raypos_at_t(t_ray ray, double t);
void		raycast(const t_ray *ray, t_hit_record *hitted);
t_vector	ray_color(const t_ray *ray, int depth);

/*
**		hit record
*/
void		init_hit_record(t_hit_record *hitted);
int			time_is_valid(long double time);
void		record_hitted(t_list *same_kind_figures, \
						void (*hit)(void *figure, const t_ray *, \
									t_hit_record *), \
						const t_ray *ray, t_hit_record *hitted);
int			check_front_face(const t_ray *ray, const t_vector *outward_normal);

/*
**		material
*/
void		init_material(t_material *material, t_vector color, double fuzz, \
							int (*scatter)(const t_ray*, void *, t_ray *));
t_vector	get_scattered_dir(const t_vector *normal);
t_vector	get_rand_in_unitsphere(void);
int			metal(const t_ray *r_in, void *hitted_record, t_ray *scattered);
int			lambertian(const t_ray *r_in, void *hitted_record, \
						t_ray *scattered);

/*
**		light
*/
void		init_light(t_light *light, t_vector pos, \
						t_vector color, double bright);
void		make_light(t_vector pos, t_vector color, double bright);
void		delete_light(void);
void		color_by_light(t_vector *color, const t_hit_record *hitted, \
							t_light *light);
void		light_hitted(const t_hit_record *hitted, t_vector *color);

/*
**		sphere
*/
void		init_sphere(t_sphere *sp, t_vector center, \
						double r, t_material *material);
void		hit_sphere(void *sphere, const t_ray *ray, t_hit_record *hitted);
void		make_sphere(t_vector center, double radius, t_material *material);

/*
**		plane
*/
void		init_plane(t_plane *plane, t_vector p, \
						t_vector normal, t_material *material);
void		make_plane(t_vector p, t_vector normal, t_material *material);
int			check_plane_hitpos(const t_plane *pl, \
								const t_ray *ray, t_hit_record *hitted);
void		record_hittedpl_normal_mat(const t_plane *pl, \
										const t_ray *ray, t_hit_record *hitted);
void		hit_plane(void *plane, const t_ray *ray, t_hit_record *hitted);

/*
**		square
*/
void		hit_square(void *square, const t_ray *ray, t_hit_record *hitted);
void		make_square(const t_plane *pl, const double side_size);
void		init_square(t_square *sq, const t_plane *pl, \
						const double side_size);

/*
**		cylinder
*/
void		init_cylinder(t_cylinder *cyl, \
							const t_plane *bottom, double r, double height);
void		make_cylinder(const t_plane *bottom, const double r, \
							const double height);
void		hit_circle(const t_plane *pl, double r, \
					const t_ray *ray, t_hit_record *hitted);
void		hit_cylinder(void *cylinder, const t_ray *ray, \
						t_hit_record *hitted);

/*
**		triangle
*/
void		init_triangle(t_triangle *tr, \
							t_vector *points, t_material *mat);
void		make_triangle(t_vector first, t_vector second, t_vector third, \
							t_material *mat);
void		hit_triangle(void *triangle, const t_ray *ray, \
						t_hit_record *hitted);

#endif
