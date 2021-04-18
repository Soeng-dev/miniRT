/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_cam_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	rotate_camera(t_camlist *camlist, char *cmd, int *is_error)
{
	rotate(&camlist->cam->horizontal, cmd, is_error);
	rotate(&camlist->cam->vertical, cmd, is_error);
	rotate(&camlist->cam->lowerleft, cmd, is_error);
}

void	change_camera(t_camlist *camlist, int camnum, \
						int *is_error, int *quit_cmdmode)
{
	char	*cmd;
	int		idlen;

	if (!camlist)
		return (set_errflag(is_error));
	while (--camnum > 0)
		camlist = camlist->next;
	printf("Enter command for change\n");
	cmd = NULL;
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	if (*quit_cmdmode || *is_error)
		return ;
	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "translate", idlen))
	{
		translate(&camlist->cam->origin, cmd + idlen, is_error);
		translate(&camlist->cam->lowerleft, cmd + idlen, is_error);
	}
	else if (!ft_strncmp(cmd, "rotate", idlen))
		rotate_camera(camlist, cmd + idlen, is_error);
	else
		*is_error = TRUE;
	free(cmd);
	return ;
}

void	change_light(int lightnum, int *is_error, int *quit_cmdmode)
{
	char	*cmd;
	int		idlen;

	if (!g_light_data.light_arr)
		return ;
	printf("Enter command for change\n");
	cmd = NULL;
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	if (*is_error || *quit_cmdmode)
		return ;
	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "translate", idlen))
		translate(&g_light_data.light_arr[lightnum - 1].pos, \
					cmd + idlen, is_error);
	else
		*is_error = TRUE;
	free(cmd);
	return ;
}
