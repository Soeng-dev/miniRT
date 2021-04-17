/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_property.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static void	change_figure(int figtype, int fignum, \
							int *is_error, int *quit_cmdmode)
{
	char	*cmd;
	t_list	*target;

	if (fignum < 1 || fignum >= NUM_OF_FIGTYPES)
		return (set_errflag(is_error));
	target = g_figures[figtype];
	while (--fignum > 0)
		target = target->next;
	printf("Enter command for change\n");
	cmd = NULL;
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	if (*is_error || *quit_cmdmode)
		return ;
	if (figtype == PLANE)
		change_plane(target->content, cmd, is_error);
	else if (figtype == SPHERE)
		change_sphere(target->content, cmd, is_error);
	else if (figtype == CYLINDER)
		change_cylinder(target->content, cmd, is_error);
	else if (figtype == SQUARE)
		change_square(target->content, cmd, is_error);
	else if (figtype == TRIANGLE)
		change_triangle(target->content, cmd, is_error);
	return (free(cmd));
}

static void	select_fignum(t_info *info, int figtype, \
							int *is_error, int *quit_cmdmode)
{
	t_list	*same_kind;
	int		fignum;
	char	*cmd;

	cmd = NULL;
	fignum = 1;
	same_kind = g_figures[figtype];
	printf("%d\n", figtype);
	printf("%p\n%p\n", same_kind, g_figures[figtype]);
	while (same_kind)
	{
		printf("%d. position : %f %f %f\n", fignum++, same_kind->pos->x, \
										same_kind->pos->y, same_kind->pos->z);
		same_kind = same_kind->next;
	}
	printf("Enter number of figure to change\n");
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	if (*is_error)
		return (change(info, is_error, quit_cmdmode));
	if (*quit_cmdmode == TRUE)
		return ;
	fignum = ft_atoi(cmd);
	free(cmd);
	change_figure(figtype, fignum, is_error, quit_cmdmode);
	return ;
}

static void	prt_tglist(int type, t_info *info)
{
	void	*target;
	int		tgnum;

	tgnum = 1;
	if (type == CAMERA)
	{
		target = (void *)info->caminfo.camlist;
		while (target)
		{
			printf("%d. position : ", tgnum++);
			prt_vector(NULL, ((t_camlist *)target)->cam->origin, NULL);
			target = (void *)(((t_camlist *)target)->next);
		}
	}
	else if (type == LIGHT)
	{
		target = (void *)(g_light_data.light_arr);
		while (tgnum <= g_light_data.count)
		{
			printf("%d. position : ", tgnum++);
			prt_vector(NULL, ((t_light *)target)->pos, NULL);
			target += sizeof(t_light);
		}
	}
	return ;
}

static void	select_targetnum(t_info *info, int type, \
							int *is_error, int *quit_cmdmode)
{
	int		tgnum;
	char	*cmd;

	prt_tglist(type, info);
	printf("Enter number of target to change\n");
	cmd = NULL;
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	if (*is_error)
		return (change(info, is_error, quit_cmdmode));
	if (*quit_cmdmode == TRUE)
		return ;
	tgnum = ft_atoi(cmd);
	free(cmd);
	if (tgnum < 1)
		return (set_errflag(is_error));
	if (type == CAMERA)
		change_camera(info->caminfo.camlist, tgnum, is_error, quit_cmdmode);
	else if (type == LIGHT)
		change_light(tgnum, is_error, quit_cmdmode);
}

void		change(t_info *info, int *is_error, int *quit_cmdmode)
{
	char	*cmd;
	char	*trimmed;
	int		type;

	cmd = NULL;
	*quit_cmdmode = FALSE;
	*is_error = FALSE;
	printf("Enter target type\n");
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	if (*quit_cmdmode == TRUE)
		return ;
	trimmed = ft_strtrim(cmd, " \t\n\v\f\r");
	free(cmd);
	type = read_target_type(trimmed);
	free(trimmed);
	if (type == CMD_ERROR)
		return (change(info, is_error, quit_cmdmode));
	if (0 <= type && type < NUM_OF_FIGTYPES)
		select_fignum(info, type, is_error, quit_cmdmode);
	else if (type == LIGHT || type == CAMERA)
		select_targetnum(info, type, is_error, quit_cmdmode);
	if (*is_error || *quit_cmdmode)
		return ;
}
