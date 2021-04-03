
# include <stdio.h>
# include "manage_command.h"
# include "../miniRT.h"

void	command(char *s, t_info *info)
{
	char	*id;
	int		is_error;

	is_error = FALSE;
	pass_charset(&s, " \t\n\v\f\r");
	id = ft_strtrim(s, " \t\n\v\f\r");
	if (!ft_strcmp("R", id))
		set_mlx_resolution(++s, &info->setup, &is_error);
	else if (!ft_strcmp("A", id))
		set_ambient(++s, &is_error);
	else if (!ft_strcmp("c", id))
		set_camera(++s, info, &is_error);
	else if (!ft_strcmp("l", id))
		set_light(++s, &is_error);
	else if (!ft_strcmp("sp", id))
		set_sphere(s + 2, &is_error);
	else if (!ft_strcmp("pl", id))
	{}
	else if (!ft_strcmp("sq", id))
	{}
	else if (!ft_strcmp("cy", id))
	{}
	else if (!ft_strcmp("tr", id))
	{}
	else
		is_error = 1;
	free (id);
	if (is_error)
		error_exit(info);
	return ;
}
