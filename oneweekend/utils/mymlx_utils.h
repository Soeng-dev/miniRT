/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYMLX_UTILS_H
# define MYMLX_UTILS_H

# define MLX_KEY_PRESS		2
# define MLX_BUTTON_PRESS	4
# define MLX_RED_CROSS		17

# define BUTTON_LEFT	1
# define BUTTON_RIGHT	2

# define KEY_RIGHT	124
# define KEY_LEFT	123
# define KEY_UP		126
# define KEY_DOWN	125
# define KEY_ESC	53
# define KEY_TAB	48
# define KEY_ENT	36

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>

# include "../get_next_line/get_next_line.h"
# include "../ray_tracing/ray_tracing.h"
# include "math/myvector.h"

struct	s_screen
{
	double	width;
	double	height;
	double	ratio;
};
typedef struct s_screen		t_screen;

struct	s_mlx_vars
{
	void	*mlx;
	void	*win;
};
typedef struct s_mlx_vars	t_mlx_vars;

struct	s_img_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		linelen;
	int		endian;
};
typedef struct s_img_data	t_img_data;

struct	s_setup
{
	t_mlx_vars	mlx_vars;
	t_img_data	img_data;
	t_screen	scr;
};
typedef struct s_setup		t_setup;

struct	s_info
{
	t_caminfo	caminfo;
	t_setup		setup;
};
typedef struct s_info		t_info;

void	pixput(const t_img_data *img, int x, int y, int color);
int		get_color(t_vector colvec, double gamma);
int		key_check(int key, t_info *info);
int		mouse_check(int button, int x, int y);
void	render_img(const t_img_data *img, const t_screen *scr,\
					const t_camera *cam);

#endif
