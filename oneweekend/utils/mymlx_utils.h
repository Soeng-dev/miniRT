
#ifndef MYMLX_UTILS_H
# define MYMLX_UTILS_H
# include "myvector.h"

struct	s_vars 
{
	void	*mlx;
	void	*win;
};
typedef struct s_vars	t_vars;
struct	s_plane
{
	double width, height;
};
typedef struct s_plane	t_plane;
struct	s_data
{
	void *img;
	char *addr;
	int bpp, linelen, endian;
};
typedef struct s_data	t_data;
void	pixput(t_data *img, int x, int y, int color);
int		get_color(t_vector colvec, double gamma);
#endif
