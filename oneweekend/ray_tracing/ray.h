
#ifndef RAY_H
# define RAY_H
# include <float.h>
# include "../libft/libft.h"
# include "../utils/myvector.h"
# define NOT_HIT DBL_MAX 
# define PLANE 0,
# define SPHERE 1
# define CYLINDER 2
# define SQUARE 3
# define TRIANGLE 4
# define NUM_OF_FIGS 5

//figure
struct	s_sphere
{
	t_vector	ctr;
	double	r;
};
//ray
struct	s_ray
{
	t_vector		pos;
	t_vector		dir;
};
struct	s_hit_record
{
	t_vector	pos;
	t_vector	normal;
	double		time;
};
typedef struct s_sphere		t_sphere;
typedef struct s_ray		t_ray;
typedef struct s_hit_record	t_hit_record;
t_list		*g_figures[NUM_OF_FIGS];
void		initray(t_ray *ray, t_vector orig, t_vector dir);
void		init_sphere(t_sphere *sp, t_vector center, double r);
t_vector		getvec(double x, double y, double z);
t_vector	pos_at_t(t_ray ray, double t);
void		hit_sphere(void *sphere, const t_ray *ray, t_hit_record *hitted);
int 		ray_color(const t_ray *ray);
double		min(double a, double b);
double		max(double a, double b);
void		init_hit_record(t_hit_record *hitted);
#endif
