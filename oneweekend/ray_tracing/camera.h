
#ifndef CAMERA_H
# define CAMERA_H
# include "../utils/math/myvector.h"

struct	s_camera
{
	t_vector	origin;
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	lowerleft;
};
typedef struct s_camera	t_camera;

struct	s_camlist
{
	struct	s_camlist	*prev;
	struct	s_camlist	*next;
	t_camera			*cam;
};
typedef struct s_camlist	t_camlist;

struct	s_campos
{
	t_vector	origin;
	t_vector	dir;
	t_vector	upward;
};
typedef struct s_campos	t_campos;

struct	s_camview
{
	double		angle;
	double		ratio;
	double		focallen;
};
typedef struct s_camview	t_camview;

void	init_campos (t_campos *campos, t_vector origin, t_vector dir, t_vector upward);
void	init_camview(t_camview *camview, double angle, double ratio, double focallen);
void	init_camera(t_camera *cam, const t_campos *campos, const t_camview *camview);
void	make_camera(t_camlist **camlist, const t_campos *campos, const t_camview *camview);

#endif
