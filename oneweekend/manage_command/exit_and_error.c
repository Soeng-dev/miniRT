
#include "manage_command.h"

void	set_errflag(int *is_error)
{
	*is_error = TRUE;
	return ;
}

void	free_allocated(t_info *info)
{
	int	figtype;

	if (!info)
		return ;
	clear_camlist(&info->caminfo);
	if (g_light_data.light_arr)
		free(g_light_data.light_arr);
	figtype = -1;
	while (++figtype < NUM_OF_FIGTYPES)
		ft_lstclear(&g_figures[figtype], free);
	return ;
}

void	exit_program(t_info *info)
{
	free_allocated(info);
	if (info->err_exit)
		printf("Error\n");
	exit(0);
}
