
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
	sq->normal = normalize(normal);
	sq->half_size = side_size / 2.0;
	sq->material = *material;
	sq->u.y = sqrt(pow(normal.x, 2) / (pow(normal.x, 2) + pow(normal.x, 2)));
	sq->u.x = -(sq->u.y * normal.y) / normal.x;
	sq->u.z = 0;
	sq->v.x = 0;
	sq->v.z = sqrt(pow(normal.y, 2) / (pow(normal.y, 2) + pow(normal.z, 2)));
	sq->v.y = -(sq->v.z * normal.z) / normal.y;
	sq->u = normalize(sq->u);
	sq->v = normalize(sq->v);
	square_node->pos = &sq->ctr;
	printf("%f %f %f\n", sq->u.x, sq->u.y, sq->u.z);
	printf("%f %f %f\n", sq->v.x, sq->v.y, sq->v.z);
	ft_lstadd_front(&g_figures[SQUARE], square_node);
	return ;
}

int		pos_in_square(const t_vector *pos, const t_square *sq)
{
	t_vector	diff;
	double		vert;
	double		horiz;

	diff = minus(*pos, sq->ctr);
	horiz = (diff.x * sq->v.y - diff.y * sq->v.x) / (sq->u.x * sq->v.y - sq->u.y * sq->v.x);
	vert = (diff.x - horiz * sq->u.x) / sq->v.x;
	if (-sq->half_size < horiz && horiz < sq->half_size &&\
		-sq->half_size < vert && vert < sq->half_size)
		return (TRUE);
	else
		return (FALSE);
}

void	hit_square(void *square, const t_ray *ray, t_hit_record *hitted)
{
	double		time;
	t_square	*sq;
	t_vector	pos;

	sq = (t_square *)square;
	time = dot(minus(sq->ctr, ray->pos), sq->normal)\
			/ dot(ray->dir, sq->normal);
	if (time_is_valid(time))
	{
		pos = raypos_at_t(*ray, time);
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
