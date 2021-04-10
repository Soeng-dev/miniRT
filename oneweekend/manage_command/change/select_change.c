
#include "../../miniRT.h"

static void	change_figure(int figtype, int fignum, int *is_error, int *quit_cmdmode)
{
	t_list	*target;

	target = g_figures[figtype];
	while (--fignum > 0)
		target = target->next;
	if (figtype == PLANE)
		change_plane(target->content, is_error, quit_cmdmode);
	else if (figtype == SPHERE)
		change_sphere(target->content, is_error, quit_cmdmode);
	else if (figtype == CYLINDER)
		change_cylinder(target->content, is_error, quit_cmdmode);
	else if (figtype == SQUARE)
		change_square(target->content, is_error, quit_cmdmode);
	else if (figtype == TRIANGLE)
		change_triangle(target->content, is_error, quit_cmdmode);
}

static void	select_and_change(int figtype, int *is_error, int *quit_cmdmode)
{
	t_list	*same_kind;
	int		fignum;
	char	*cmd;

	cmd = NULL;
	fignum = 1;
	same_kind = g_figures[figtype];
	while (same_kind)
	{
		printf("%d. position : %f %f %f\n", fignum, same_kind->pos->x, same_kind->pos->y, same_kind->pos->z);
		same_kind = same_kind->next;
		++fignum;
	}
	printf("Enter number of figure to change\n");
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	fignum = ft_atoi(cmd);
	free(cmd);
	if (*is_error)
		return (change(is_error, quit_cmdmode));
	if (*quit_cmdmode == TRUE)
		return ;
	change_figure(figtype, fignum, is_error, quit_cmdmode);
	if (*quit_cmdmode || *is_error)
		return ;
	return ;
}

void		change(int *is_error, int *quit_cmdmode)
{
	char	*cmd;
	char	*trimmed;
	int		figtype;

	cmd = NULL;
	*quit_cmdmode = FALSE;
	*is_error = FALSE;
	printf("Enter object type\n");
	read_stdin_command(&cmd, is_error, quit_cmdmode);
	if (*quit_cmdmode == TRUE)
		return (free(cmd));
	trimmed = ft_strtrim(cmd, " \t\n\v\f\r");
	free(cmd);
	figtype = read_figtype(trimmed);
	free(trimmed);
	if (figtype == CMD_ERROR)
		return (change(is_error, quit_cmdmode));
	select_and_change(figtype, is_error, quit_cmdmode);
	if (*is_error || *quit_cmdmode)
		return ;
}
