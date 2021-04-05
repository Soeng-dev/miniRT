
#include "manage_command.h"

double		read_dbl(char **s)
{
	double	intiger;
	double	small;
	int		is_positive;

	intiger = 0;
	small = 0;
	is_positive = TRUE;
	pass_charset(s, " \t\n\v\f\r");
	intiger = (double)ft_atoi(*s);
	if (**s == '-')
	{
		is_positive = FALSE;
		++(*s);
	}
	pass_charset(s, "0123456789");
	if (**s == '.' && *(*s + 1))
	{
		while(ft_isdigit(*(++(*s))))
			small = (small / 10.0) + ((**s - '0') / 10.0);
	}
	if (is_positive)
		return (intiger + small);
	else
		return (intiger - small);
}

t_vector	read_vector(char **s)
{
	t_vector	v;

	v.x = read_dbl(s);
	pass_charset(s, " \t\n\v\f\r,");
	v.y = read_dbl(s);
	pass_charset(s, " \t\n\v\f\r,");
	v.z = read_dbl(s);
	return (v);
}

void	set_fuzz_scatter(char *s, t_material *mat, int *is_error)
{
	char	*trimmed;

	mat->fuzz = 0;
	mat->scatter = lambertian;
	pass_charset(&s, " \t\n\v\f\r");
	if (!(*s))
		return ;
	trimmed = ft_strtrim(s, " \t\n\v\f\r");
	if (!ft_strcmp(trimmed, "metal"))
		mat->scatter = metal;
	else if (ft_strcmp(trimmed, "lambertian") != 0)
		*is_error = TRUE;
	pass_charset(&s, trimmed);
	free(trimmed);
	if (*s)
		mat->fuzz = read_dbl(&s);
	if (mat->fuzz < 0)
		*is_error = TRUE;
	return ;
}
