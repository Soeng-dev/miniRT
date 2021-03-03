
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

int main()
{
	t_vars	ex;
	t_data	img;
	const int imgwidth = 256, imgheight = 256;

	ex.mlx = mlx_init();
	ex.win = mlx_new_window(ex.mlx, 300, 300, "ex");
	img.img = mlx_new_image(ex.mlx, 256, 256);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linelen, &img.endian);
	for (int x = imgwidth - 1; x >= 0; --x)
	{
		for (int y = 0; y < imgheight; ++y)
		{
			int r = (int)floor(((double)x / (imgwidth - 1)) * (double)255 + 0.5);
			int g = (int)floor(((double)y / (imgheight - 1)) * (double)255 + 0.5);
			int b = (int)floor(0.25 * (double)255 + 0.5);
			int color = 0;
			color = (r << 16) | (g << 8) | (b);
			pixput(&img, x, y, color);
		}
	}
	mlx_put_image_to_window(ex.mlx, ex.win, img.img, 25, 25);
	mlx_loop(ex.mlx);

}
