
#ifndef RAY_H
# define RAY_H
# include <float.h>
# include "../libft/libft.h"
# include "../utils/myvector.h"
# define NOT_HIT DBL_MAX 
# define T_MAX DBL_MAX
# define T_MIN 0.001
# define PLANE 0
# define SPHERE 1
# define CYLINDER 2
# define SQUARE 3
# define TRIANGLE 4
# define NUM_OF_FIGTYPES 5

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
	int		is_front_face;
};
typedef struct s_sphere		t_sphere;
typedef struct s_ray		t_ray;
typedef struct s_hit_record	t_hit_record;
t_list		*g_figures[NUM_OF_FIGTYPES];
void		init_ray(t_ray *ray, t_vector pos, t_vector dir);
void		init_sphere(t_sphere *sp, t_vector center, double r);
t_vector	raypos_at_t(t_ray ray, double t);
void		hit_sphere(void *sphere, const t_ray *ray, t_hit_record *hitted);
t_vector	ray_color(const t_ray *ray);
double		min(double a, double b);
double		max(double a, double b);
void		init_hit_record(t_hit_record *hitted);
int			check_front_face(const t_ray *ray, const t_vector * outward_normal);
void		make_sphere(t_vector center, double radius);
double		get_sphere_hitted_time(double a, double b, double sqrt_dis);
t_vector	ray_color_of_diffuse(const t_ray *ray, int depth);
int			time_is_valid(long double time);
void	record_hitted(t_list *same_kind_figures, void (*hit)(void *figure, const t_ray *, t_hit_record *), const t_ray *ray, t_hit_record *hitted);
void	raycast(const t_ray *ray, t_hit_record *hitted);

#endif
