
#include "../../miniRT.h"

void		init_triangle(t_triangle *tr, t_vector *points, t_material *mat)
{
	tr->p = points[0];
	tr->edge1 = minus(points[1], points[0]);
	tr->edge2 = minus(points[2], points[0]);
	tr->normal = cross(tr->edge1, tr->edge2);
	tr->material = *mat;
	return ;
}

void		make_triangle(t_vector first, t_vector second, t_vector third, t_material *mat)
{
	t_list		*triangle_node;
	t_vector	points[3];

	triangle_node = (t_list *)malloc(sizeof(t_list));
	if (!triangle_node)
		return ;
	triangle_node->content = malloc(sizeof(t_triangle));
	if (!triangle_node->content)
		return ;
	points[0] = first;
	points[1] = second;
	points[2] = third;
	init_triangle((t_triangle *)(triangle_node->content), points, mat);
	triangle_node->pos = &((t_triangle *)triangle_node->content)->p;
	ft_lstadd_front(&g_figures[TRIANGLE], triangle_node);
	return ;
}

static int	pos_in_triangle(const t_vector *pos, const t_triangle *tr)
{
	double		alpha;
	double		beta;
	t_vector	delp;

	delp = minus(*pos, tr->p);
	alpha = (delp.x * tr->edge2.y - delp.y - tr->edge2.x)		\
			/ (tr->edge1.x * tr->edge2.y - tr->edge1.y * tr->edge2.x);
	beta = (delp.x - alpha * tr->edge1.x) / tr->edge2.x;
	if (0 < alpha && 0 < beta && alpha + beta < 1)
		return (TRUE);
	return (FALSE);
}

void		hit_triangle(void *triangle, const t_ray *ray, t_hit_record *hitted)
{
	double		time;
	t_vector	pos;
	t_triangle	*tr;

	tr = (t_triangle *)triangle;
	time = dot(minus(tr->p, ray->pos), tr->normal) \
			/ dot(ray->dir, tr->normal);
	hitted->time = NOT_HIT;
	if (time_is_valid(time))
	{
		pos = raypos_at_t(*ray, time);
		if (pos_in_triangle(&pos, tr))
		{
			hitted->time = time;
			hitted->pos = pos;
			hitted->normal = tr->normal;
			hitted->time = time;
			hitted->is_front_face = TRUE;
			hitted->material = &tr->material;
		}
	}
	return ;
}
