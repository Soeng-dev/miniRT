
#ifndef RAY_H
# define RAY_H
# include "../utils/myvector.h"
# include "figure.h"

struct	s_ray
{
	t_vec		orig;
	t_vec		dir;
};
typedef struct s_ray	t_ray;
void		initray(t_ray *ray, t_vec orig, t_vec dir);
t_vec		getvec(double x, double y, double z);
t_ray		cast(t_ray ray, double t);
double		hitsp(const t_sp *sp, const t_ray *ray);
int 		ray_color(const t_ray *ray, const t_sp *sp);

#endif