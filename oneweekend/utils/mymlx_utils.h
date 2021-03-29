
#ifndef MYMLX_UTILS_H
# define MYMLX_UTILS_H
# define ESC 53
# include "myvector.h"

struct	s_mlx_vars 
{
	void	*mlx;
	void	*win;
};
typedef struct s_mlx_vars	t_mlx_vars;
struct	s_screen
{
	double	width;
	double	height;
	double	ratio;
};
typedef struct s_screen	t_screen;
struct	s_mlx_data
{
	void *img;
	char *addr;
	int bpp, linelen, endian;
};
typedef struct s_mlx_data	t_mlx_data;
void	pixput(t_mlx_data *img, int x, int y, int color);
int		get_color(t_vector colvec, double gamma);
int		key_check(int key);

#endif
