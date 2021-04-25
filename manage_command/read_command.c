/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double		read_dbl(char **s, int *is_error)
{
	double	intiger;
	double	small;
	int		is_positive;

	intiger = 0;
	small = 0;
	is_positive = TRUE;
	pass_charset(s, " \t\f");
	intiger = (double)ft_atoi(*s);
	if (**s == '-')
	{
		is_positive = FALSE;
		++(*s);
	}
	else if (ft_isdigit(**s) == FALSE)
		*is_error = TRUE;
	pass_charset(s, "0123456789");
	if (**s == '.' && ft_isdigit(*(*s + 1)))
		while (ft_isdigit(*(++(*s))))
			small = (small / 10.0) + ((**s - '0') / 10.0);
	else if (**s == '.' && ft_isdigit(*(*s + 1)) != FALSE)
		*is_error = TRUE;
	if (!is_element(" \t\n,", **s) && **s != '\0')
		*is_error = TRUE;
	return ((is_positive) ? intiger + small : intiger - small);
}

t_vector	read_vector(char **s, int *is_error)
{
	t_vector	v;

	v.x = read_dbl(s, is_error);
	pass_charset(s, " \t\f");
	if (**s != ',')
		*is_error = TRUE;
	*s += 1;
	v.y = read_dbl(s, is_error);
	pass_charset(s, " \t\f");
	if (**s != ',')
		*is_error = TRUE;
	*s += 1;
	v.z = read_dbl(s, is_error);
	return (v);
}

void		set_fuzz_scatter(char *s, t_material *mat, int *is_error)
{
	int		idlen;

	mat->fuzz = 0;
	mat->scatter = lambertian;
	pass_charset(&s, " \t\f");
	idlen = get_idlen(s, " \t\f");
	if (!(*s))
		return ;
	if (!ft_strncmp(s, "metal", idlen) && idlen > 0)
		mat->scatter = metal;
	else if (ft_strncmp(s, "lambertian", idlen))
		*is_error = TRUE;
	while (ft_isalpha(*s))
		s++;
	if (*s != '\0')
		mat->fuzz = read_dbl(&s, is_error);
	pass_charset(&s, " \t\f");
	if (mat->fuzz < 0 || *s != '\0')
		*is_error = TRUE;
	return ;
}

int			read_target_type(char *cmd)
{
	if (!cmd)
		return (CMD_ERROR);
	if (!ft_strcmp(cmd, "plane") || !ft_strcmp(cmd, "pl"))
		return (PLANE);
	else if (!ft_strcmp(cmd, "sphere") || !ft_strcmp(cmd, "sp"))
		return (SPHERE);
	else if (!ft_strcmp(cmd, "cylinder") || !ft_strcmp(cmd, "cyl"))
		return (CYLINDER);
	else if (!ft_strcmp(cmd, "square") || !ft_strcmp(cmd, "sq"))
		return (SQUARE);
	else if (!ft_strcmp(cmd, "triangle") || !ft_strcmp(cmd, "tr"))
		return (TRIANGLE);
	else if (!ft_strcmp(cmd, "camera") || !ft_strcmp(cmd, "cam"))
		return (CAMERA);
	else if (!ft_strcmp(cmd, "light") || !ft_strcmp(cmd, "l"))
		return (LIGHT);
	else if (!ft_strcmp(cmd, "filter"))
		return (FILTER);
	else
	{
		printf("Wrong input\n");
		return (CMD_ERROR);
	}
}

void		read_stdin_command(char **cmd, int *is_error, int *quit_cmdmode)
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
