
#include "../utils/myvector.h"

struct	s_camera
{
	t_vector	origin;
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	lowerleft;
};
typedef struct s_camera	t_camera;

struct	s_campos
{
	t_vector	origin;
	t_vector	lookat;
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

void	init_campos (t_campos *campos, t_vector origin, t_vector lookat, t_vector upward);
void	init_camview(t_camview *camview, double angle, double ratio, double focallen);
void	init_camera(t_camera *cam, const t_campos *campos, const t_camview *camview);
