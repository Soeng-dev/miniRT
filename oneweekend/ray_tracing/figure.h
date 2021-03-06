
#ifndef FIGURE_H
# define FIGURE_H
# include "../utils/myvector.h"

struct	s_sphere
{
	t_vec	ctr;
	double	r;
};
typedef struct s_sphere	t_sp;
void			initsp(t_sp *sp, t_vec center, double r);

#endif
