 
#include "../../miniRT.h"

void		init_cylinder(t_cylinder *cyl, t_vector ctr, t_vector normal, t_material *material)
{
	cyl->ctr = ctr;
	cyl->normal = normal;
	cyl->material = *material;
	return ;
}

void		make_cylinder()
{
	t_list	*cyl_node;

	cyl_node = (t_list *)malloc(sizeof(t_list));
	if (!cyl_node)
		return ;
	cyl_node->content = malloc(sizeof(t_cylinder));
	if (!cyl_node->content)
		return ;
	init_cylinder((t_cylinder *)(cyl_node->content), ctr, normal, material);
	ft_lstadd_front(&g_figures[CYLINDER], cyl_node);
}

//뭐가 됬든 !is_front_face인데 범위안의 h 에서 만난다면 바닥또는 천장통과, 이때 범위밖의 h에서 반드시 만날것이므로 범위밖의 h를 이용해 바닥인지 천장인지 판단, h1, h2에 각각의 해를 저장한 후 바닥이나 천장을 통과한다면 비례식 이용해 t또는 raypos 구해서 나머지 전부구하기
static int	set_others(t_hit_record *hitted, const t_cylidner *cyl, const t_ray *ray, double time)
{
	double h;

	hitted->pos = raypos_at_t(*ray, time);
	h = dot(cyl->normal, minus(ray->pos, cyl->p)) \
	    / dot(cyl->normal, cyl->normal);
	if (h < 0 || cyl->height < h)
		return (FALSE);
	outward_normal = minus(ray->pos, add(cyl->p, multi(cyl->normal, h)));
	hitted->is_front_face = check_front_face(ray, &outward_normal);
	if (hitted->is_front_face)
	{
		hitted->time = time;
		hitted->pos = raypos_at_t(*ray, time);
	}
	else
	{
			



	
}


static void	set_cyl_hitrec(t_hit_record *hitted, const t_cylinder *cyl, const t_ray *ray)
{
	t_vector	outward_normal;

	hitted->time = NOT_HIT;
	time = (-b - sqrt_dis) / a;
	if (time_is_valid(time))
	{
		}

	{
		time = (-b + sqrt_dis) / a;
		if (time_is_valid(time))
			hitted->time = time;
	}
	if (hitted->time == NOT_HIT)
		return ;
		
	hitted->material = (t_material *)&cyl->material;
	if (hitted->is_front_face)
		hitted->normal = outward_normal;
	else
		hitted->normal = multi(outward_normal, -1);
	return ;
}

void		hit_cylinder(void *cylinder, const t_ray *ray, t_hit_record *hitted)
{
	double				a;
	double				b;
	double				c;
	double				discriminant;
	t_vector			delp;
	const t_cylinder	*cyl;

	cyl = (const t_cylinder *)cylinder;
	delp = minus(ray->pos, cyl->p);
	a = dot(minus(ray->dir, multi(cyl->normal, dot(ray->dir, cyl->normal))), \
			minus(ray->dir, multi(cyl->normal, dot(ray->dir, cyl->normal))));
	b = dot(minus(ray->dir, multi(cyl->normal, dot(cyl->normal, ray->dir))), \
			minus(delp, multi(cyl->normal, dot(delp, cyl->normal))));
	c = dot(minus(delp, multi(cyl->normal, dot(delp, cyl->normal))), \
			minus(delp, multi(cyl->normal, dot(delp, cyl->normal)))) \
		 - cyl->r * cyl->r;
	discriminant = b * b - a * c;
	if (discriminant > 0)
		hitted->time = get_cyl_hitted_time(a, b, sqrt(discriminant));
	set_cyl_hitrec(hitted, cyl, ray);
}
