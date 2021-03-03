
#include <stdio.h>
#include <math.h>
#include <mlx.h>

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

typedef struct	direction
{
	int x,y,z;
}				t_dir;

typedef struct	s_ray
{
	t_dir	orig;
	t_dir	curr;
	t_dir	dir;
}				t_ray;

void		initray(t_ray *r, t_dir orig, t_dir dir)
{
	r->orig = orig;
	r->curr = orig;
	r->dir = dir;
}

void			cast(t_ray *r, double t)
{
	r->curr.x += (r->dir.x * t);
	r->curr.y += (r->dir.y * t);
	r->curr.z += (r->dir.z * t);
}

int main()
{
	t_vars	ex;
	t_data	img;
	const int imgwidth = 256, imgheight = 256;
 
	//	ch 4
	mlx_put_image_to_window(ex.mlx, ex.win, img.img, 25, 25);
	mlx_loop(ex.mlx);
	
}
