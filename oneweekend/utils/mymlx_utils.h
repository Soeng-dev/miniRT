
#ifndef MYMLX_UTILS_H
# define MYMLX_UTILS_H
# define MLX_KEY_PRESS 2
# define MLX_BUTTON_PRESS 4
# define MLX_RED_CROSS 17
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_ESC 53
# include "myvector.h"
# include "../ray_tracing/ray.h"

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
void	pixput(const t_mlx_data *img, int x, int y, int color);
int		get_color(t_vector colvec, double gamma);
int		key_check(int key, t_camera *cam);
int		mouse_check(int mouse, int x, int y);
void	render_img(const t_mlx_data *img, const t_screen *scr, const t_camera *cam);
int		red_cross_exit(void);

#endif
