
#include "manage_command.h"

void	set_sphere(char *s, int *is_error)
{
	t_material	*mat;
	t_vector	center;
	double		r;

	center = read_vector(&s);
	r = read_dbl(&s) / 2.0;
	mat = (t_material *)malloc(sizeof(t_material));
	if (!mat || r <= 0)
		return (set_errflag(is_error));
	mat->albedo = divide(read_vector(&s), 255);
	if (!is_valid_vector(mat->albedo, 0, 1.0))
			*is_error = TRUE;
	set_fuzz_scatter(s, mat, is_error);
	if (*is_error)
		return free(mat);
	make_sphere(center, r, mat);
	return ;
}

void	set_plane(char *s, int *is_error)
{
	t_vector	p;
	t_vector	normal;
	t_material	*mat;

	p = read_vector(&s);
	normal = read_vector(&s);
	mat = (t_material *)malloc(sizeof(t_material));
	if (!mat)
		return (set_errflag(is_error));
	mat->albedo = divide(read_vector(&s), 255.0);
	if (! is_valid_vector(mat->albedo, 0, 1.0))
		*is_error = TRUE;
	set_fuzz_scatter(s, mat, is_error);
	if (*is_error)
		return (free(mat));
	make_plane(p, normal, mat);
	return ;
}
