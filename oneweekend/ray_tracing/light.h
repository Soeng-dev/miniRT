
#include "../utils/myvector.h"

struct	s_light
{
	t_vector	pos;
	double		bright;
};
typedef s_light	t_light;
struct	s_lightdata
{
	t_light	*lights;
	int		count;
};
typedef s_lightdata	t_lightdata;

void		init_light(t_light *light, t_vector pos, double bright);
void		make_light(t_vector pos, double bright);
void		delete_light(void);



