
# include "../../miniRT.h"

void	init_plane(t_plane *plane, t_vector p, t_vector normal, t_material *material)
{
	plane->p = p;
	plane->normal = normal;
	plane->material = *material;
	return;
}

void	make_plane(t_vector p, t_vector normal, t_material *material)
{
	t_list	*plane_node;

	plane_node = (t_list *)malloc(sizeof(t_list));
	if (!plane_node)
		return ;
	plane_node->content = malloc(sizeof(t_plane));
	if (!plane_node->content)
		return ;
	init_plane((t_plane *)(plane_node->content), p, normal, material);
	ft_lstadd_front(&g_figures[PLANE], plane_node);
	return ;
}

void	hit_plane(void *plane, const t_ray *ray, t_hit_record *hitted)
{
	double	time;
	t_plane	*pl;

	pl = (t_plane *)plane;
	time = dot(minus(pl->p, ray->pos), pl->normal)\
		/ dot(ray->dir, pl->normal);
	if (time_is_valid(time))
	{
		hitted->pos = raypos_at_t(*ray, time);
		hitted->normal = pl->normal;
		hitted->time = time;
		hitted->is_front_face = TRUE;
		hitted->material = &pl->material;
	}
	else
		hitted->time = NOT_HIT;
	return ;
}
