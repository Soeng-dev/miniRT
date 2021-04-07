
#include "../../miniRT.h"

void	make_square(t_vector ctr, t_vector normal, double side_size, t_material *material)
{
	t_list		*square_node;
	t_square	*sq;

	square_node = (t_list *)malloc(sizeof(t_list));
	if (!square_node)
		return ;
	square_node->content = malloc(sizeof(t_square));
	if (!square_node->content)
		return ;
	sq = (t_square *)square_node->content;
	sq->ctr = ctr;
	sq->normal = normal;
	sq->half_size = side_size / 2.0;
	sq->material = *material;
	ft_lstadd_front(&g_figures[SQUARE], square_node);
	return ;
}

int		pos_in_square(const t_vector *pos, const t_square *sq)
{
	return (absol(pos->x - sq->ctr.x) < sq->half_size &&\
			absol(pos->y - sq->ctr.y) < sq->half_size);
}

void	hit_square(void *square, const t_ray *ray, t_hit_record *hitted)
{
	double		time;
	t_square	*sq;
	t_vector	pos;

	sq = (t_square *)square;
	time = dot(minus(sq->ctr, ray->pos), sq->normal)\
		   / dot(ray->dir, sq->normal);
	pos = raypos_at_t(*ray, time);
	hitted->time = NOT_HIT;
	if (time_is_valid(time))
	{
		if (pos_in_square(&pos, sq))
		{
			hitted->time = time;
			hitted->pos = pos;
			hitted->normal = sq->normal;
			hitted->time = time;
			hitted->is_front_face = TRUE;
			hitted->material = &sq->material;
		}
	}
	return ;
}
