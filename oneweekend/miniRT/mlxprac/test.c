#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bpp;
	int			linelen;
	int			endian;
}				t_data;

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->linelen + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void			put_sq(t_data *data, int* xrange, int* yrange, int color)
{
	for (int y = yrange[0] ; y < yrange[1]; ++y)
	{
		for (int x = xrange[0] ; x < xrange[1]; ++x)
			my_mlx_pixel_put(data, x, y, color);
	}
}

typedef struct	s_vars 
{
	void	*mlx;
	void	*win;
}				t_vars;

int		key_hook(int keycode, t_vars *vars)
{
	if (keycode == )
	else if (keycode == '\n')
		printf("\n");
	else 
		printf ("%c", keycode);
	return (keycode);
}

int		close(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
}

int main()
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "hello \n");
//	mlx_loop(mlx);
//	t_data	img;
//	img.img = mlx_new_image(vars.mlx, 1920, 1080);
//	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linelen, &img.endian);
//	int xr[] = {100, 1800}, yr[] ={100, 900};
//	put_sq(&img,xr, yr, 0x00FF0000);
//	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
//	mlx_key_hook(vars.win, key_hook,&vars);
	
	mlx_loop(vars.mlx);
}
