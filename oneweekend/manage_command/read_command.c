
#include "../minirt.h"

double	read_dbl(char **s)
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

int		read_target_type(char *cmd)
{
	int		type;

	if (!cmd)
		return (CMD_ERROR);
	if (!ft_strcmp(cmd, "plane") || !ft_strcmp(cmd, "pl"))
		type = PLANE;
	else if (!ft_strcmp(cmd, "sphere") || !ft_strcmp(cmd, "sp"))
		type = SPHERE;
	else if (!ft_strcmp(cmd, "cylinder") || !ft_strcmp(cmd, "cyl"))
		type = CYLINDER;
	else if (!ft_strcmp(cmd, "square") || !ft_strcmp(cmd, "sq"))
		type = SQUARE;
	else if (!ft_strcmp(cmd, "triangle") || !ft_strcmp(cmd, "tr"))
		type = TRIANGLE;
	else if (!ft_strcmp(cmd, "camera") || !ft_strcmp(cmd, "cam"))
		type = CAMERA;
	else if (!ft_strcmp(cmd, "light") || !ft_strcmp(cmd, "l"))
		type = LIGHT;
	else
	{
		printf("Wrong input\n");
		type = CMD_ERROR;
	}
	return (type);
}

void	read_stdin_command(char **cmd, int *is_error, int *quit_cmdmode)
{
	printf("quit for stop command mode\n");
	if (get_next_line(STDIN, cmd) == ERROR)
	{
		printf("Input Read failed\n");
		*is_error = TRUE;
		if (*cmd)
			free(*cmd);
		return ;
	}
	else if (!ft_strcmp(*cmd, "quit"))
	{
		*quit_cmdmode = TRUE;
		free(*cmd);
	}
	return ;
}
