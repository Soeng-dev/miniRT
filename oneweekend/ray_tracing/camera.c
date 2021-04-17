
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

void	make_camera(t_caminfo *caminfo, const t_campos *campos, const t_camview *camview)
{
	if (caminfo->camlist)
	{
		caminfo->camlist->prev = (t_camlist *)malloc(sizeof(t_camlist));
		if (!caminfo->camlist->prev)
			return ;
		caminfo->camlist->prev->prev = NULL;
		caminfo->camlist->prev->next = caminfo->camlist;
		caminfo->camlist = caminfo->camlist->prev;
	}
	else
	{
		caminfo->camlist = (t_camlist *)malloc(sizeof(t_camlist));
		if (!caminfo->camlist)
			return ;
		caminfo->camlist->prev = NULL;
		caminfo->camlist->next = NULL;
	}
	caminfo->camlist->cam = (t_camera *)malloc(sizeof(t_camera));
	init_camera(caminfo->camlist->cam, campos, camview);
	caminfo->curr_camnode = caminfo->camlist;
}

void	clear_camlist(t_caminfo *caminfo)
{
	t_camlist	*next;
	t_camlist	*curr;

	curr = caminfo->camlist;
	while (curr)
	{
		next = curr->next;
		free(curr->cam);
		free(curr);
		ft_memset(curr, 0, sizeof(t_camlist));
		curr = next;
	}
	ft_memset(caminfo, 0, sizeof(t_caminfo));
	return ;
}
