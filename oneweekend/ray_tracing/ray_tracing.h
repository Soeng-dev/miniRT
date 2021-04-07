
#ifndef RAY_TRACING_H
# define RAY_TRACING_H
# include <float.h>
# include "../libft/libft.h"
# include "../utils/myvector.h"
# include "camera.h"
# include "light.h"
# define NOT_HIT DBL_MAX 
# define T_MAX DBL_MAX
# define T_MIN 0.001
# define PLANE 0
# define SPHERE 1
# define CYLINDER 2
# define SQUARE 3
# define TRIANGLE 4
# define NUM_OF_FIGTYPES 5
# define TRUE 1
# define FALSE 0

struct	s_ray
{
	t_vector	pos;
	t_vector	dir;
};
typedef struct s_ray	t_ray;
struct	s_material
{
	t_vector	albedo;
	double		fuzz;
	int			(*scatter)(const t_ray*, void *, t_ray *);
};
typedef struct s_material	t_material;
struct s_hit_record
{
	t_vector	pos;
	t_vector	normal;
	double		time;
	int			is_front_face;
	t_material	*material;
};
typedef struct s_hit_record	t_hit_record;
//figure
struct	s_sphere
{
	t_vector	ctr;
	double		r;
	t_material	material;
};
typedef struct s_sphere	t_sphere;
struct	s_plane
{
	t_vector	p;
	t_vector	normal;
	t_material	material;
};
typedef struct s_plane	t_plane;
struct	s_square
{
	t_vector	ctr;
	t_vector	normal;
	double		half_size;
	t_material	material;
};
typedef struct s_square	t_square;
struct	s_cylinder
{
	t_vector	ctr;
	t_vector	normal;
	double		r;
	double		half_h;
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

t_list		*g_figures[NUM_OF_FIGTYPES];
t_lightdata	g_light_data;

void		init_ray(t_ray *ray, t_vector pos, t_vector dir);
t_vector	raypos_at_t(t_ray ray, double t);
t_vector	ray_color(const t_ray *ray, int depth);
void		init_hit_record(t_hit_record *hitted);
int			check_front_face(const t_ray *ray, const t_vector * outward_normal);
int			time_is_valid(long double time);
void		record_hitted(t_list *same_kind_figures, void (*hit)(void *figure, const t_ray *, t_hit_record *), const t_ray *ray, t_hit_record *hitted);
void		raycast(const t_ray *ray, t_hit_record *hitted);
t_vector	get_scattered_dir(const t_vector *normal);
void		init_material(t_material *material, t_vector color, double fuzz, \
							int (*scatter)(const t_ray*, void *, t_ray *));
t_material	*get_material(t_vector color, double fuzz, \
							int (*scatter)(const t_ray*, void *, t_ray *));

int			metal(const t_ray *r_in, void *hitted_record, t_ray *scattered);
int			lambertian(const t_ray *r_in, void *hitted_record, t_ray *scattered);
t_ray		get_ray(t_vector pos, t_vector dir);
void		init_light(t_light *light, t_vector pos, t_vector color, double bright);
void		make_light(t_vector pos, t_vector color, double bright);
void		delete_light(void);
void		light_hitted(const t_hit_record *hitted, t_vector *color);

//figures
//sphere
void		init_sphere(t_sphere *sp, t_vector center, double r, t_material *material);
void		hit_sphere(void *sphere, const t_ray *ray, t_hit_record *hitted);
void		make_sphere(t_vector center, double radius, t_material *material);

//plane
void		init_plane(t_plane *plane, t_vector p, t_vector normal, t_material *material);
void	make_plane(t_vector p, t_vector normal, t_material *material);
void	hit_plane(void *plane, const t_ray *ray, t_hit_record *hitted);

//square
void	hit_square(void *square, const t_ray *ray, t_hit_record *hitted);
void	make_square(t_vector ctr, t_vector normal, double side_size, t_material *material);

//cylinder

//triangle
void	init_triangle(t_triangle *tr, t_vector *points, t_material *mat);
void	make_triangle(t_vector first, t_vector second, t_vector third, t_material *mat);
void	hit_triangle(void *triangle, const t_ray *ray, t_hit_record *hitted);

#endif
