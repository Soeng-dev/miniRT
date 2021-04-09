
#include "../miniRT.h"

int		select_figure(char *cmd, int *is_error)
{
	t_list	*same_kind;
	int		fig;

	if (!cmd)
		return (set_errflag(is_error));
	fig = get_figtype(cmd);
	if (fig == CMD_ERROR)
		return resize(is_error);
	fig = 0;
	same_kind = g_figures[fig];
	while (same_kind)
	{
		printf("%d. position : %f %f %f\n", fig, same_kind->pos->x, same_kind->pos->y, same_kind->pos->z);
		same_kind = same_kind->next;
		fig++;
	}
	printf("Enter number of figure to resize\n");
	read_stdin_command(cmd, is_error);
	if (*is_error)
		return (CMD_ERROR);
	fig = ft_atoi(cmd);
	free(cmd);
	return (fig);
}

void	resize(int *is_error)
{
	char	*cmd;
	char	*trimmed;
	int		fig;

	cmd = NULL;
	printf("Enter object type\n");
	read_stdin_command(cmd, is_error);
	trimmed = ft_strtrim(cmd, " \t\n\v\f\r");
	fig = select_figure(trimmed, is_error);
	if (*is_error)
		return ;
	if (trimmed)
		free(trimmed);
	
	free(cmd);

}
