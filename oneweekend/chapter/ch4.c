
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
	ray->dir = dir;
}

void		cast(t_ray *ray, double t)
{
	ray->curr.x += (ray->dir.x * t);
	ray->curr.y += (ray->dir.y * t);
	ray->curr.z += (ray->dir.z * t);
}

typedef struct	s_plane
{
	double width, height;
}				t_plane;

int		get_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | (b));
}

int		ray_color(const t_ray *ray)
{
	double	ratio;
	int		r, g, b;

	ratio = 0.5 * (ray->dir.y + 1.0);
	//printf("%g\n", ray->dir.y);
	r = (int)((1.0 - ratio) * 255.0 + ratio * 255.0 * 0.5);
	g = (int)((1.0 - ratio) * 255.0 + ratio * 255.0 * 0.7);
	b = 255;
	//printf("%d %d %d\n", r, g,b);
	return (get_color(r, g, b));
}

int main()
{
	t_vars	ex;
	t_data	img;
 
	//  make image with mlx
	ex.mlx = mlx_init();
 	ex.win = mlx_new_window(ex.mlx, 500, 500, "ex");
 	img.img = mlx_new_image(ex.mlx, 400, 225);
 	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linelen, &img.endian);

	//	ch 4
	//	image
	const double scrratio = 16.0/9.0;
	t_plane	scr;
	scr.width = 400;
	scr.height = scr.width / scrratio;

	//camera
	t_plane	view;
	view.height = 2.0;
	view.width = scrratio * view.height;
	double	focallen = 1.0;

	t_vec origin, horizontal, vertical, lowerleft;
	initvec(&origin, 0, 0, 0);
	initvec(&horizontal, view.width, 0, 0);
	initvec(&vertical, 0, view.height, 0);

	lowerleft = minus(origin, multi(add(horizontal, vertical), 0.5));
	lowerleft.z = origin.z - focallen;

	for (int j = scr.height - 1; j >= 0; --j)
	{
		for (int i = 0; i < scr.width; ++i)
		{
			t_ray ray;
			double u = (double)i / (scr.width - 1);
			double v = (double)j / (scr.height - 1);
			t_vec castdir = add(multi(horizontal, u), multi(vertical, v));
			initray(&ray, origin, minus(add(lowerleft, castdir), origin));
			int color = ray_color(&ray);
			pixput(&img, i, j, color);
		}
	}

	mlx_put_image_to_window(ex.mlx, ex.win, img.img, 0, 0);
	mlx_loop(ex.mlx);
}
