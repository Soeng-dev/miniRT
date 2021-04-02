
#include <manage_command.h>

void	set_fuzz_scatter(char *s, t_vector *color, void **scatter, int *is_error)
{
	char	*trimmed;

	trimmed = ft_strtrim(s, " \t\n\v\f\r");
	if (!ft_strcmp(trimmed, "metal"))
		*scatter = metal;
	else if (ft_strcmp(trimmed, "lambertian") != 0)
		*is_error = TRUE;
	else
		*scatter = lambertian;
	free(trimmed);
	pass_charset(&s, "abcdefghijklmnopqrstuvwxyz");
	pass_charset(&s, " \t\n\v\f\r");
	if (*s)
	{
		fuzz = read_dbl(&s);
		if (fuzz < 0)
			*is_error = TRUE;
	}
}

void	set_material(char *s, t_material **mat, int *is_error)
{
	double		fuzz;
	t_vector	color;
	int			(*scatter)(const t_ray *, void *, t_ray *);

	fuzz = 0;
	scatter = NULL;
	color = read_vector(&s);
	pass_charset(&s, " \t\n\v\f\r");
	if (*s)
		set_fuzz_scatter(s, &color, &scatter, is_error);
	*mat = get_material(color, fuzz, scatter);
	if (!(*mat))
		*is_error = 1;
	return ;
}

void	set_sphere(char *s, int *is_error)
{
	t_material	*mat;
	t_vector	center;
	double		r;

	center = read_vector(&s);
	r = read_dbl(&s) / 2.0;
	set_material(s, &mat, is_error);
	make_sphere
	return ;
}

