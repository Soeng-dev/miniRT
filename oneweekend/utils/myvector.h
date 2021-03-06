
#ifndef MYVECTOR_H
# define MYVECTOR_H

struct	s_vector
{
	double x,y,z;
};
typedef struct s_vector	t_vec;
void        initvec(t_vec *v, double x, double y, double z);
t_vec		getvec(double x, double y, double z);
t_vec		multi(t_vec v, double n);
t_vec		div(t_vec v, double n);
t_vec		normalize(t_vec v);
t_vec		add(t_vec v1, t_vec v2);
t_vec		minus(t_vec v1, t_vec v2);
double      dot(t_vec v1, t_vec v2);
#endif