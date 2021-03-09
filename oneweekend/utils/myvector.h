
#ifndef MYVECTOR_H
# define MYVECTOR_H

struct	s_vector
{
	double x,y,z;
};
typedef struct s_vector	t_vector;
void        initvec(t_vector *v, double x, double y, double z);
t_vector		getvec(double x, double y, double z);
t_vector		multi(t_vector v, double n);
t_vector		divide(t_vector v, double n);
t_vector		normalize(t_vector v);
t_vector		add(t_vector v1, t_vector v2);
t_vector		minus(t_vector v1, t_vector v2);
double      dot(t_vector v1, t_vector v2);
#endif