
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
	t_material	*material;
};
typedef struct s_sphere	t_sphere;

t_list		*g_figures[NUM_OF_FIGTYPES];
t_lightdata	g_light_data;

void		init_ray(t_ray *ray, t_vector pos, t_vector dir);
void		init_sphere(t_sphere *sp, t_vector center, double r, t_material *material);
t_vector	raypos_at_t(t_ray ray, double t);
void		hit_sphere(void *sphere, const t_ray *ray, t_hit_record *hitted);
t_vector	ray_color(const t_ray *ray, double ambience, int depth);
void		init_hit_record(t_hit_record *hitted);
int			check_front_face(const t_ray *ray, const t_vector * outward_normal);
void		make_sphere(t_vector center, double radius, t_material *material);
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
#endif
