
#include "../../miniRT.h"

void	change_plane(t_plane *pl, int *is_error, int *quit_cmdmode)
{
	int			idlen;
	char		*cmd;

	printf("Enter command for change\n");
	cmd = NULL;
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	if (*is_error || *quit_cmdmode)
		return ;
	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "translate", idlen))
		translate(&pl->p, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "rotation", idlen))
		rotate(&pl->normal, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "color", idlen))
		change_color(&pl->material.albedo, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "material", idlen))
		change_material(&pl->material, cmd + idlen, is_error);
	else
		*is_error = TRUE;
	return free(cmd);
}

void	change_sphere(t_sphere *sp, int *is_error, int *quit_cmdmode)
{
	int			idlen;
	char		*cmd;

	printf("Enter command for change\n");
	cmd = NULL;
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	if (*is_error || *quit_cmdmode)
		return ;
	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "translate", idlen))
		translate(&sp->ctr, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "color", idlen))
		change_color(&sp->material.albedo, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "material", idlen))
		change_material(&sp->material, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "radius", idlen))
		change_length(&sp->r, cmd + idlen, is_error);
	else
		*is_error = TRUE;
	return free(cmd);
}

void	change_square(t_square *sq, int *is_error, int *quit_cmdmode)
{
	int			idlen;
	char		*cmd;

	printf("Enter command for change\n");
	cmd = NULL;
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	if (*is_error || *quit_cmdmode)
		return ;
	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "translate", idlen))
		translate(&sq->ctr, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "rotation", idlen))
		rotate(&sq->normal, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "color", idlen))
		change_color(&sq->material.albedo, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "material", idlen))
		change_material(&sq->material, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "side_size", idlen))
	{
		change_length(&sq->half_size, cmd + idlen, is_error);
		sq->half_size /= 2.0;
	}
	else
		*is_error = TRUE;
	return free(cmd);
}

void	change_cylinder(t_cylinder *cyl, int *is_error, int *quit_cmdmode)
{
	int			idlen;
	char		*cmd;
	t_plane		changed;

	printf("Enter command for change\n");
	cmd = NULL;
	changed = cyl->bottom;
	changed.normal = multi(cyl->bottom.normal, -1);
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	if (*is_error || *quit_cmdmode)
		return ;
	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "translate", idlen))
		translate(&changed.p, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "rotation", idlen))
		rotate(&changed.normal, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "color", idlen))
		change_color(&changed.material.albedo, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "material", idlen))
		change_material(&changed.material, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "radius", idlen))
		change_length(&cyl->r, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "height", idlen))
		change_length(&cyl->height, cmd + idlen, is_error);
	else
		*is_error = TRUE;
	init_cylinder(cyl, &changed, cyl->r, cyl->height);
	return free(cmd);
}

void	change_triangle(t_triangle *tr, int *is_error, int *quit_cmdmode)
{
	int			idlen;
	char		*cmd;

	printf("Enter command for change\n");
	cmd = NULL;
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	if (*is_error || *quit_cmdmode)
		return ;
	idlen = get_idlen(cmd, " \t\n\v\f\r");
	if (!ft_strncmp(cmd, "translate", idlen))
		translate(&tr->p, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "rotation", idlen))
	{
		rotate(&tr->edge1, cmd + idlen, is_error);
		rotate(&tr->edge2, cmd + idlen, is_error);
		rotate(&tr->normal, cmd + idlen, is_error);
	}
	else if (!ft_strncmp(cmd, "color", idlen))
		change_color(&tr->material.albedo, cmd + idlen, is_error);
	else if (!ft_strncmp(cmd, "material", idlen))
		change_material(&tr->material, cmd + idlen, is_error);
	else
		*is_error = TRUE;
	return free(cmd);
}
