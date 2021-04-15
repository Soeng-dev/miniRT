
#include "../minirt.h"

void	init_campos(t_campos *campos, t_vector origin, t_vector dir, t_vector upward)
{
	campos->dir= dir;
	campos->origin = origin;
	campos->upward = upward;
}

void	init_camview(t_camview *camview, double angle, double ratio, double focallen)
{
	camview->focallen = focallen;
	camview->angle = angle;
	camview->ratio = ratio;
}

void	init_camera(t_camera *cam, const t_campos *campos, const t_camview *camview)
{
	t_vector	w;
	t_vector	u;
	t_vector	v;
	t_screen	view;

	//check w if camera doesn't work
	w = multi(campos->dir, -1);
	u = normalize(cross(campos->upward, w));
	v = cross(w, u);
	view.height = 2.0 * camview->focallen * tan(camview->angle / 2.0);
	view.width = camview->ratio * view.height;

	cam->origin = campos->origin;
	cam->horizontal = multi(u, view.width);
	cam->vertical = multi(v, view.height);
	cam->lowerleft = add(divide(cam->horizontal, 2.0),\
						divide(cam->vertical, 2.0));
	cam->lowerleft = add(cam->lowerleft,\
						multi(w, camview->focallen));
	cam->lowerleft = minus(cam->origin, cam->lowerleft);
}

void	make_camera(t_camlist **camlist, const t_campos *campos, const t_camview *camview)
{
	if (*camlist)
	{
		(*camlist)->next = (t_camlist *)malloc(sizeof(t_camlist));
		if (!(*camlist)->next)
			return ;
		(*camlist)->next->prev = *camlist;
		(*camlist)->next->next = NULL;
		*camlist = (*camlist)->next;
	}
	else
	{
		(*camlist) = (t_camlist *)malloc(sizeof(t_camlist));
		if (!(*camlist))
			return ;
		(*camlist)->prev = NULL;
		(*camlist)->next = NULL;
	}
	(*camlist)->cam = (t_camera *)malloc(sizeof(t_camera));
	init_camera((*camlist)->cam, campos, camview);
}
