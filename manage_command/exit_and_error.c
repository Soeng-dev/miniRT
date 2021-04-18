/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
