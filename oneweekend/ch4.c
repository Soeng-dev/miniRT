
#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include "./myvector.h"

// basic mlx functions
typedef struct	s_vars 
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_data{
	void *img;
	char *addr;
	int bpp, linelen, endian;
}				t_data;

void			pixput(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

//ray tracing functions
typedef struct	s_ray
{
	t_vec		orig;
	t_vec		curr;
	t_vec		dir;
}				t_ray;

void		initray(t_ray *ray, t_vec orig, t_vec dir)
{
	ray->orig = orig;
	ray->curr = orig;
	ray->dir = normalize(dir);
}

void		cast(t_ray *ray, double t)
{
	r->curr.x += (r->dir.x * t);
	r->curr.y += (r->dir.y * t);
	r->curr.z += (r->dir.z * t);
}

typedef struct	s_plane
{
	double width, height;
}				t_plane;

int main()
{
	t_vars	ex;
	t_data	img;
 
	//	ch 4
	//	image
	const double scrratio = 16.0/9.0;
	t_plane	img;
	img.width = 400;
	img.height = img.width / scrratio;

	//camera
	t_plane	view;
	view.height = 2.0;
	view.width = scrraitio * view.height;
	double	focallen = 1.0;

	vec origin, horizontal, vertical, lowerleft;
	initvec(&origin, 0, 0, 0);
	initvec(&horizontal, view.width, 0, 0);
	initvec(&vertical, 0, view.height, 0);
	lowerleft = minus(origin, multi(add(horizontal, vertical), 0.5));
	lowerleft.z = origin.z - focallen;

	mlx_put_image_to_window(ex.mlx, ex.win, img.img, 25, 25);
	mlx_loop(ex.mlx);
	
}
