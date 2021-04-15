
#include "../../minirt.h"

void	init_square(t_square *sq, const t_plane *pl, const double side_size)
{
	double		p;
	double		t;
	t_vector	omega;

	sq->ctr = pl->p;
	sq->normal = normalize(pl->normal);
	sq->half_size = side_size / 2.0;
	sq->material = pl->material;
	p = asin(sq->normal.x);
	t = asin(sq->normal.y / (-cos(p)));
	init_vector(&omega, 0, cos(t), sin(t));
	sq->u = rotate_vector(get_vector(1, 0, 0), omega, p);
	sq->v = rotate_vector(get_vector(0, 1, 0), get_vector(1, 0, 0), t);
	sq->v = rotate_vector(sq->v, omega, p);
	return ;
}

void	make_square(const t_plane *pl, const double side_size)
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
	init_square(sq, pl, side_size);
	square_node->pos = &sq->ctr;
	ft_lstadd_front(&g_figures[SQUARE], square_node);
	return ;
}

int		pos_in_square(const t_vector *pos, const t_square *sq)
{
	t_vector	diff;
	double		vert;
	double		horiz;

	diff = minus(*pos, sq->ctr);
	vert = dot(diff, sq->v) / dot(sq->v, sq->v);
	horiz = dot(diff, sq->u) / dot(sq->u, sq->u);
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
