
#include "manage_command.h"

void	set_mlx_resolution(char *s, t_setup *setup, int *is_error)
{
	ft_memset(scr, sizeof(t_setup));

	get_mlx_screen_size(setup->mlx_vars.mlx, &setup->scr.width, &setup->scr.height);
	setup->scr.width = dbl_min(ft_atoi(s), setup->scr.width);
	pass_charset(&s, " \t\n\v\f\r");
	pass_charset(&s, "0123456789");
	setup->scr.height= dbl_min(ft_atoi(s), setup->scr.height);
	if (setup->mlx_vars.width <= 0 || setup->mlx_vars.height <= 0)
		*is_error = 1;
	return ;
}

void	set_ambient(char *s, int *is_error)
{
	double		bright;
	t_vector	ambient;

	bright = read_dbl(&s);
	if (bright < 0)
		*is_error = 1;
	ambient = read_vector(&s);
	if (ambient.x < 0 || ambient.y < 0 || ambient.z < 0)
		*is_error = 1;
	ambient = multi(ambient, bright);
	g_light_data.ambient = ambient;
	return ;
}

void	set_camera(char *s, t_camlist *camlist, double *scr_ratio, int *is_error)
{
	t_campos	campos;
	t_camview	camview;

	campos.upward = get_vector(0, 1, 0);
	campos.origin = read_vector(&s);
	campos.dir = read_vector(&s);
	camview.angle = M_PI * (read_dbl(&s) / 180);
	if (camview.angle >= M_PI || camview.angle <=0)
		*is_error = 1;
	camview.focallen = 1.0;
	camview.ratio = *scr_ratio;
}

void	set_light(char *s, int *is_error)
{
	t_vector	pos;
	t_vector	color;
	double		bright;

	pos = read_vector(&s);
	bright = read_dbl(&s);
	color = read_vector(&s);
	if (bright < 0 || color.x < 0 || color.y < 0 || color.z < 0)
		*is_error = 1;
	make_light(pos, color, bright);
}
