/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:25:21 by soekim            #+#    #+#             */
/*   Updated: 2021/03/04 21:30:54 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_H
# define RAY_TRACING_H
# include <math.h>
# include <stdio.h>

struct	s_vars 
{
	void	*mlx;
	void	*win;
};
typedef struct s_vars	t_vars;
struct	s_plane
{
	double width, height;
};
typedef struct s_plane	t_plane;
struct	s_data
{
	void *img;
	char *addr;
	int bpp, linelen, endian;
};
typedef struct s_data	t_data;
struct	s_vector
{
	double x,y,z;
};
typedef struct s_vector	t_vec;
struct	s_ray
{
	t_vec		orig;
	t_vec		curr;
	t_vec		dir;
};
typedef struct s_ray	t_ray;
struct	s_sphere
{
	t_vec	ctr;
	double	r;
};
typedef struct s_sphere	t_sp;
//figure
void		initsp(t_sp *sp, t_vec center, double r);
//my mlx utils
void		pixput(t_data *img, int x, int y, int color);
int			get_color(int r, int g, int b);
//vector
void		initvec(t_vec *v, double x, double y, double z);
t_vec		multi(t_vec v, double n);
t_vec		div(t_vec v, double n);
t_vec		normalize(t_vec v);
t_vec		add(t_vec v1, t_vec v2);
t_vec		minus(t_vec v1, t_vec v2);
double		dot(t_vec v1, t_vec v2);
//ray
void		initray(t_ray *ray, t_vec orig, t_vec dir);
void		cast(t_ray *ray, double t);
int			hitsp(const t_sp *sp, const t_ray *ray);
int			ray_color(const t_ray *ray, const t_sp *sp);

#endif
