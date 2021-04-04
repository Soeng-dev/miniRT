
#include "manage_command.h"

void	set_fuzz_scatter(char *s, t_material *mat, int *is_error)
{
	char	*trimmed;

	trimmed = ft_strtrim(s, " \t\n\v\f\r");
	if (!ft_strcmp(trimmed, "metal"))
		mat->scatter = metal;
	else if (ft_strcmp(trimmed, "lambertian") != 0)
		return (set_errflag(is_error));
	pass_charset(&s, trimmed);
	free(trimmed);
	mat->fuzz = read_dbl(&s);
	if (mat->fuzz < 0)
		*is_error = TRUE;
	return ;
}

void	set_material(char *s, t_material **mat, int *is_error)
{
	double		fuzz;
	t_vector	color;
	int			(*scatter)(const t_ray *, void *, t_ray *);

	fuzz = 0;
	scatter = lambertian;
	color = divide(read_vector(&s), 255.0);
	pass_charset(&s, " \t\n\v\f\r");
	*mat = get_material(color, fuzz, scatter);
	if (!(*mat) || color.x < 0 || color.y < 0 || color.z < 0)
		return (set_errflag(is_error));
	if (*s)
		set_fuzz_scatter(s, *mat, is_error);
	return ;
}
void	set_sphere(char *s, int *is_error)
{
	t_material	*mat;
	t_vector	center;
	double		r;

	center = read_vector(&s);
	r = read_dbl(&s) / 2.0;
	if (r <= 0)
		return (set_errflag(is_error));
	set_material(s, &mat, is_error);
	if (*is_error)
		return ;
	make_sphere(center, r, mat);
	return ;
}

