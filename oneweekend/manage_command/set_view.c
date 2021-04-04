
#include "manage_command.h"

void	set_mlx_resolution(char *s, t_setup *setup, int *is_error)
{
	setup->scr.width = ft_atoi(s);
	pass_charset(&s, " \t\n\v\f\r");
	pass_charset(&s, "0123456789");
	setup->scr.height= ft_atoi(s);
//	printf("width:%f	height:%f\n\n", setup->scr.width, setup->scr.height);
	if (setup->scr.width <= 0 || setup->scr.height <= 0)
		*is_error = 1;
	return ;
}

void	set_ambient(char *s, int *is_error)
{
	double		bright;
	t_vector	ambient;

	bright = read_dbl(&s);
	//printf("b %f\n", bright);
	if (bright < 0)
		return (set_errflag(is_error));
	ambient = divide(read_vector(&s), 255.0);
	if (ambient.x < 0 || ambient.y < 0 || ambient.z < 0)
		return (set_errflag(is_error));	
	ambient = multi(ambient, bright);
	g_light_data.ambient = ambient;
	return ;
}

void	set_camera(char *s, t_info *info, int *is_error)
{
	t_campos	campos;
	t_camview	camview;

	campos.upward = get_vector(0, 1, 0);
	campos.origin = read_vector(&s);
	campos.dir = read_vector(&s);
	camview.angle = M_PI * (read_dbl(&s) / 180.0);
	if (camview.angle >= M_PI || camview.angle <= 0)
		return (set_errflag(is_error));
	camview.focallen = 1.0;
	camview.ratio = info->setup.scr.ratio;
	make_camera(&info->camlist, &campos, &camview);
}

void	set_light(char *s, int *is_error)
{
	t_vector	pos;
	t_vector	color;
	double		bright;

	pos = read_vector(&s);
	bright = read_dbl(&s);
	color = divide(read_vector(&s), 255.0);
	if (bright < 0 || color.x < 0 || color.y < 0 || color.z < 0)
		return (set_errflag(is_error));
	make_light(pos, color, bright);
}
