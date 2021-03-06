/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diverge_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int			get_idlen(char *s, char *delimiters)
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

static void	diverge_command(char *s, t_info *info, \
							int *is_error)
{
	int		idlen;

	idlen = get_idlen(s, " \t\n\v\f\r");
	if (!ft_strncmp("R", s, idlen))
		set_mlx_resolution(s + idlen, info, is_error);
	else if (!ft_strncmp("A", s, idlen))
		set_ambient(s + idlen, info, is_error);
	else if (!ft_strncmp("c", s, idlen))
		set_camera(s + idlen, info, is_error);
	else if (!ft_strncmp("l", s, idlen))
		set_light(s + idlen, is_error);
	else if (!ft_strncmp("sp", s, idlen) && idlen > 1)
		set_sphere(s + idlen, is_error);
	else if (!ft_strncmp("pl", s, idlen))
		set_plane(s + idlen, is_error);
	else if (!ft_strncmp("sq", s, idlen) && idlen > 1)
		set_square(s + idlen, is_error);
	else if (!ft_strncmp("cy", s, idlen) && idlen > 1)
		set_cylinder(s + idlen, is_error);
	else if (!ft_strncmp("tr", s, idlen))
		set_triangle(s + idlen, is_error);
	else
		*is_error = TRUE;
	if (*is_error)
		printf("Error line :%s\n", s);
}

int			check_command(char *s, t_info *info)
{
	int		quit_cmdmode;
	int		is_error;

	if (!s || !info)
		return (CMD_COMMENT);
	pass_charset(&s, " \t\n\v\f\r");
	if (!(*s) || !ft_strncmp("//", s, 2))
		return (CMD_COMMENT);
	is_error = FALSE;
	quit_cmdmode = 0;
	if (!ft_strcmp("change", s))
		change(info, &is_error, &quit_cmdmode);
	else
		diverge_command(s, info, &is_error);
	if (info->err_exit)
		exit_program(info);
	if (is_error)
		return (CMD_ERROR);
	else if (quit_cmdmode == TRUE)
		return (CMD_QUIT);
	else
		return (CMD_CORRECT);
}
