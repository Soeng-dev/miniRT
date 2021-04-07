
#include <../../miniRT.h>

void	init_triangle(t_triangle *tr, t_vector *points, t_material *mat)
{
	tr->first = points[0];
	tr->second = minus(points[1], point[0]);
	tr->third = minus(points[2], point[0]);
	tr->material = *mat;
	return ;
}

void	make_triangle(t_vector first, t_vector second, t_vector third, t_material *mat)
{
	t_list		*triangle_node;
	t_triangle	*tr;

	triangle_node = (t_list *)malloc(sizeof(t_list));
	if (!triangle_node)
		return ;
	triangle_node->content = malloc(sizeof(t_triangle));
	if (!triangle_node->content)
		return ;
	tr = (t_triangle *)(triangle_node->content);
	tr->p = first;
	tr->edge1 = minus(second, first);
	tr->edge2 = minus(third, first);
	tr->mat = *mat;
	ft_lstadd_front(&g_figures[TRIANGLE], triangle_node);
	return ;
}

void	hit_triangle(void *triangle
