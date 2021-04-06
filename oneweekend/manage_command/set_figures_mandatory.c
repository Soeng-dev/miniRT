
#include "manage_command.h"

void	set_sphere(char *s, int *is_error)
{
	t_material	mat;
	t_vector	center;
	double		r;

	center = read_vector(&s);
	r = read_dbl(&s) / 2.0;
	mat.albedo = divide(read_vector(&s), 255);
	if (!is_valid_vector(mat.albedo, 0, 1.0) || r <= 0)
		return (set_errflag(is_error));
	set_fuzz_scatter(s, &mat, is_error);
	if (*is_error)
		return ;
	make_sphere(center, r, &mat);
	return ;
}

void	set_plane(char *s, int *is_error)
{
	t_vector	p;
	t_vector	normal;
	t_material	mat;

	p = read_vector(&s);
	normal = read_vector(&s);
	mat.albedo = divide(read_vector(&s), 255.0);
	if (! is_valid_vector(mat.albedo, 0, 1.0))
		return (set_errflag(is_error));
	set_fuzz_scatter(s, &mat, is_error);
	if (*is_error)
		return ;
	make_plane(p, normal,& mat);
	return ;
}

void	set_square(char *s, int *is_error)
{
	t_vector	ctr;
	t_vector	normal;
	double		side_size;
	t_material	mat;

	ctr = read_vector(&s);
	normal = read_vector(&s);
	side_size = read_dbl(&s);
	mat.albedo = divide(read_vector(&s), 255);
	if (!is_valid_vector(mat.albedo, 0, 1.0) || side_size <= 0)
		return (set_errflag(is_error));
	set_fuzz_scatter(s, &mat, is_error);
	if (*is_error)
		return ;
	make_square(ctr, normal, side_size, &mat);
	return ;
}
