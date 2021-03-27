
#ifndef LIGHT_H
# define LIGHT_H
# include "../utils/myvector.h"

struct	s_light
{
	t_vector	pos;
	t_vector	color;
	double		bright;
};
typedef struct s_light	t_light;
struct	s_lightdata
{
	t_light	*light_arr;
	int		count;
};
typedef struct s_lightdata	t_lightdata;

void		init_light(t_light *light, t_vector pos, t_vector color, double bright);
void		make_light(t_vector pos, t_vector color, double bright);
void		delete_light(void);

#endif