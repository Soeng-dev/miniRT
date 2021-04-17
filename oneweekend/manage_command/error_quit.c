
#include "manage_command.h"

void	set_errflag(int *is_error)
{
	*is_error = TRUE;
	return ;
}

void	error_exit(t_info *info)
{
	int	figtype;

	if (!info)
		return ;
	//clear_camlist(info->camlist);
	if (g_light_data.light_arr)
		free(g_light_data.light_arr);
	figtype = -1;
	while (++figtype < NUM_OF_FIGTYPES)
		ft_lstclear(&g_figures[figtype], free);
	printf("Error\n");
	exit(0);
}
