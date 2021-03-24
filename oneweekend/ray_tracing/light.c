
#include "../miniRT.h"

void	init_light(t_light *light, t_vector pos, double bright)
{
	light->bright = bright;
	light->pos = pos;
	return ;
}

void	make_light(t_vector pos, double bright)
{
	t_light		*lights;

	lights = g_light_data.lights;
	if (lights)
		lights = realloc(lights, (g_light_data.count + 2) * sizeof(t_light));
	else
		lights = malloc(lights, sizeof(t_light));
	if (!lights)
		return ;
	g_light_data.lights = lights;
	lights += g_light_data.count;
	init_light(lights, pos, bright);
	g_light_data.count++;
}

void	delete_light(void)
{
	free(g_light_data.lights);
	g_light_data.lights = NULL;
	g_light_data.count = 0;
}
