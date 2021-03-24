
#include "../miniRT.h"

void	init_light(t_light *light, t_vector pos, double bright)
{
	light->bright = bright;
	light->pos = pos;
	return ;
}

void	make_light(t_vector pos, double bright)
{
	t_light		*light;

	light = g_light_data.light_arr;
	if (light)
		light = realloc(light, (g_light_data.count + 2) * sizeof(t_light));
	else
		light = malloc(sizeof(t_light));
	if (!light)
		return ;
	g_light_data.light_arr = light;
	light += g_light_data.count;
	init_light(light, pos, bright);
	g_light_data.count++;
}

void	delete_light(void)
{
	free(g_light_data.light_arr);
	g_light_data.light_arr = NULL;
	g_light_data.count = 0;
}
