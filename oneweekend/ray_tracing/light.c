
#include "../miniRT.h"

void	init_light(t_light *light, t_vector pos, t_vector color, double bright)
{
	light->color = color;
	light->bright = bright;
	light->pos = pos;
	return ;
}

void	make_light(t_vector pos, t_vector color, double bright)
{
	t_light		*light;

	light = (t_light *)malloc((g_light_data.count + 2) * sizeof(t_light));
	if (!light)
		return ;
	if (g_light_data.light_arr)
	{
		ft_memcpy(light, g_light_data.light_arr, g_light_data.count);
		free(g_light_data.light_arr);
	}
	g_light_data.light_arr = light;
	light = g_light_data.light_arr + g_light_data.count;
	init_light(light, pos, color, bright);
	g_light_data.count++;
}

void	delete_light(void)
{
	free(g_light_data.light_arr);
	g_light_data.light_arr = NULL;
	g_light_data.count = 0;
}
