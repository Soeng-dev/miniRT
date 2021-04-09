
#include "../miniRT.h"

void	prt_figures(char *cmd)
{
	int		fig;
	t_list	*same_kind;

	if (!ft_strcmp(cmd, "plane") || !ft_strcmp(cmd, "pl"))
		fig = PLANE;
	else if (!ft_strcmp(cmd, "sphere") || !ft_strcmp(cmd, "sp"))
		fig = SPHERE;
	else if (!ft_strcmp(cmd, "cylinder") || !ft_strcmp(cmd, "cyl"))
		fig = CYLINDER;
	else if (!ft_strcmp(cmd, "square") || !ft_strcmp(cmd, "sq"))
		fig = SQUARE;
	else if (!ft_strcmp(cmd, "triangle") || !ft_strcmp(cmd, "tr"))
		fig = TRIANGLE;
	same_kind = g_figures[fig];
	fig = 0;
//	while (same_kind)
//	{
//		fig++;
//		printf("%d: %f
//		same_kind = same_kind->next;
//	}
	if (cmd)
		free(cmd);
}

void	resize(int *is_error)
{
	char	*cmd;

	cmd = NULL
	printf("Enter object type\n");
	if (get_next_line(STDIN, &cmd) == ERROR)
	{
		printf("Input Read failed\n");
		*is_error = TRUE;
		return ;
	}
	prt_figures(ft_strtrim, " \t\n\v\f\r");
	printf("Enter number of object to resize\n");
