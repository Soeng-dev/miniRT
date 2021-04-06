
# include "manage_command.h"
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

void	command(char *s, t_info *info)
{
	int		idlen;
	int		is_error;

	pass_charset(&s, " \t\n\v\f\r");
	if (!s)
		return ;
	if (!(*s) || !ft_strncmp("//", s, 2))
		return ;
	is_error = FALSE;
	idlen = get_idlen(s, " \t\n\v\f\r");
	if (!ft_strncmp("R", s, idlen))
		set_mlx_resolution(s + idlen, &info->setup, &is_error);
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
		set_square(s+idlen, &is_error);
	else if (!ft_strncmp("cy", s, idlen))
	{}
	else if (!ft_strncmp("tr", s, idlen))
	{}
	else
		is_error = TRUE;
	if (is_error)
		error_exit(info);
	return ;
}
