
#include "../ray_tracing.h"

void	init_cylinder(t_cylinder *cyl, t_vector ctr, t_vector normal, t_material *material)
{
	cyl->ctr = ctr;
	cyl->normal = normal;
	cyl->material = *material;
	return ;
}

void	make_cylinder(t_vector ctr, t_vector normal, t_material *material)
{
	t_list	*cyl_node;

	cyl_node = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cyl_node)
		return ;
	cyl_node->content = malloc(sizeof(t_cylinder));
	if (!cyl_node->content)
		return ;
	init_cylinder((t_cylinder *)(cyl_node->content), ctr, normal, material);
	ft_lstadd_front(&g_figures[CYLINDER], cyl_node);
}

void	hit_cylinder(void *cylinder, const t_ray *ray, t_hit_record *hitted)
{
	t_vector	p;
	t_cylinder	*cyl;
	double		a;
	double		b;
	double		c;
	double		time;

	cyl = (t_cylinder *)cylinder;
	
