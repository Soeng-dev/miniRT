
#ifndef MYVECTOR_H
# define MYVECTOR_H

struct	s_vector
{
	double x,y,z;
};
typedef struct s_vector	t_vector;
void			init_vector(t_vector *v, double x, double y, double z);
t_vector		get_vector(double x, double y, double z);
t_vector		multi(t_vector v, double n);
t_vector		divide(t_vector v, double n);
t_vector		normalize(t_vector v);
t_vector		add(t_vector v1, t_vector v2);
t_vector		minus(t_vector v1, t_vector v2);
t_vector		power(t_vector v, double n);
double			dot(t_vector v1, t_vector v2);
#endif
