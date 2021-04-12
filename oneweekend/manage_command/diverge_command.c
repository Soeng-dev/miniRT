
# include "../miniRT.h"

int		get_idlen(char *s, char *delimiters)
{
	int		idlen;

	idlen = 0;
	while (!is_element(delimiters, *s) && *s)
	{
		++s;
		++idlen;
	}
	return (idlen);
}

int		check_command(char *s, t_info *info)
{
	int		idlen;
	int		quit_cmdmode;
	int		is_error;

	if (!s || !info)
		return (CMD_COMMENT);
	pass_charset(&s, " \t\n\v\f\r");
	if (!(*s) || !ft_strncmp("//", s, 2))
		return (CMD_COMMENT);
	is_error = FALSE;
	idlen = get_idlen(s, " \t\n\v\f\r");
	if (!ft_strncmp("R", s, idlen))
		set_mlx_resolution(s + idlen, info, &is_error);
	else if (!ft_strncmp("A", s, idlen))
		set_ambient(s + idlen, &is_error);
	else if (!ft_strncmp("c", s, idlen))
		set_camera(s + idlen, info, &is_error);
	else if (!ft_strncmp("l", s, idlen))
		set_light(s + idlen, &is_error);
	else if (!ft_strncmp("sp", s, idlen))
		set_sphere(s + idlen, &is_error);
	else if (!ft_strncmp("pl", s, idlen))
		set_plane(s + idlen, &is_error);
	else if (!ft_strncmp("sq", s, idlen))
		set_square(s + idlen, &is_error);
	else if (!ft_strncmp("cy", s, idlen))
		set_cylinder(s + idlen, &is_error);
	else if (!ft_strncmp("tr", s, idlen))
		set_triangle(s + idlen, &is_error);
	else if (!ft_strncmp("change", s, idlen))
		change(&is_error, &quit_cmdmode);
	else
		is_error = TRUE;
	if (is_error)
		return (CMD_ERROR);
	else if (quit_cmdmode == TRUE)
		return (CMD_QUIT);
	else
		return (CMD_CORRECT);
}
