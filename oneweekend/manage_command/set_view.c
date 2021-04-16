
#include "manage_command.h"

void	set_mlx_resolution(char *s, t_screen *scr, int *is_error)
{
	if (scr->width || scr->height)
		return ;
	scr->width = read_dbl(&s);
	scr->height = read_dbl(&s);
	scr->ratio = scr->width / scr->height;
	if (scr->width <= 0 || scr->height <= 0)
	{
		//ft_memset//마무리할것
		*is_error = TRUE;
	}
	return ;
}

void	set_ambient(char *s, int *is_error)
{
	double		bright;
	t_vector	ambient;

	if (!vector_is_same(g_light_data.ambient, \
						get_vector (0, 0, 0)))
		return ;
	bright = read_dbl(&s);
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
	campos.dir = normalize(read_vector(&s));
	camview.angle = M_PI * (read_dbl(&s) / 180.0);
	if (camview.angle >= M_PI || camview.angle <= 0)
		return (set_errflag(is_error));
	camview.focallen = 1.0;
	camview.ratio = info->setup.scr.ratio;
	make_camera(&info->caminfo, &campos, &camview);
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
