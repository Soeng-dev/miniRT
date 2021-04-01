
#include "manage_command.h"

void	set_mlx_resolution(char *s, t_setup *setup)
{
	ft_memset(scr, sizeof(t_setup));

	get_mlx_screen_size(setup->mlx_vars.mlx, &setup->scr.width, &setup->scr.height);
	setup->scr.width = dbl_min(ft_atoi(s), setup->scr.width);
	pass_charset(&s, " \t\n\v\f\r");
	pass_charset(&s, "0123456789");
	setup->scr.height= dbl_min(ft_atoi(s), setup->scr.height);
	if (setup->mlx_vars.width <= 0 || setup->mlx_vars.height <= 0)
	{
		printf("Error\n");
		exit(0);
	}
	return ;
}

void	set_ambient(char *s)
{
	double		bright;
	t_vector	ambient;

	pass_charseet(&s, " \t\n\v\f\r");
	bright = extract_dbl(s);
	pass_charset(&s, "0123456789.");
	pass_charseet(&s, " \t\n\v\f\r");
	ambient = extract_vector(s);
	ambient = multi(ambient, bright);
	g_light_data.ambient = ambient;
	return ;
}

void	set_camera(char *s, t_camlist *camlist)
{
	
}
