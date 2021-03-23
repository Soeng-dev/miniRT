
#include "../miniRT.h"

void	init_campos (t_campos *campos, t_vector origin, t_vector lookat, t_vector upward)
{
	campos->lookat = lookat;
	campos->origin = origin;
	campos->upward = upward;
}

void	init_camview(t_camview *camview, double angle, double ratio, double focallen)
{
	camview->focallen = focallen;
	camview->angle = angle;
	camview->ratio = ratio;
}

void	init_camera(t_camera *cam, t_campos *campos, t_camview *camview)
{
	t_vector	w;
	t_vector	u;
	t_vector	v;
	double		view_height;
	double		view_width;

	w = normalize(minus(campos->origin, campos->lookat));
	u = normalize(cross(campos->upward, w));
	v = cross(w, u);
	view_height = 2.0 * camview->focallen * tan(camview->angle / 2.0);
	view_width = camview->ratio * view_height;

	cam->origin = campos->origin;
	cam->horizontal = multi(u, view_width);
	cam->vertical = multi(v, view_height);
	cam->lowerleft = add(divide(cam->horizontal, 2.0), \
				divide(cam->vertical, 2.0));
	cam->lowerleft = add(cam->lowerleft,\
						multi(w, camview->focallen));
	cam->lowerleft = minus(cam->origin, cam->lowerleft);
}
