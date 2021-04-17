
#ifndef MANAGE_COMMAND_H
# define MANAGE_COMMAND_H
# define _USE_MATH_DEFINES
# define CMD_ERROR		-1
# define CMD_CORRECT	1
# define CMD_COMMENT	0
# define CMD_NONE		0
# define CMD_QUIT		-2

# include <math.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../utils/mymlx_utils.h"
# include "../ray_tracing/ray_tracing.h"
# include "../get_next_line/get_next_line.h"
# include "../mlx_mms/mlx.h"
int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);

/*
**	exit and error
*/
void		exit_program(t_info *info);
void		set_errflag(int *is_error);
void		free_allocated(t_info *info);

//string
int			ft_strcmp(char *s1, char *s2);
int			is_element(const char *set, char c);
void		pass_charset(char **str, const char *set);

//read
double		read_dbl(char **s);
t_vector	read_vector(char **s);
int			read_figtype(char *cmd);
void		set_fuzz_scatter(char *s, t_material *mat, int *is_error);
void		read_stdin_command(char **cmd, int *is_error, int *quit_cmdmode);
int			read_target_type(char *cmd);

//diverge_command
int			check_command(char *s, t_info *info);
int			get_idlen(char *s, char *delimiters);

//view
void		set_mlx_resolution(char *s, t_info *info, int *is_error);
void		set_ambient(char *s, int *is_error);
void		set_camera(char *s, t_info *info, int *is_error);
void		set_light(char *s, int *is_error);

//fiugres
void		set_sphere(char *s, int *is_error);
void		set_plane(char *s, int *is_error);
void		set_square(char *s, int *is_error);
void		set_cylinder(char *s, int *is_error);
void		set_triangle(char *s, int *is_error);

/*
**	select change
*/
void		change(t_info *info, int *is_error, int *quit_cmdmode);
/*
**	change property
*/
void		change_color(t_vector *target, char *cmd, int *is_error);
void		change_material(t_material *target, char *cmd, int *is_error);
void		change_length(double *target, char *cmd, int *is_error);
/*
**	change figure
*/
void		change_plane(t_plane *pl, char *cmd, int *is_error);
void		change_sphere(t_sphere *sp, char *cmd, int *is_error);
void		change_square(t_square *sq, char *cmd, int *is_error);
void		change_cylinder(t_cylinder *cyl, char *cmd, int *is_error);
void		change_triangle(t_triangle *tr, char *cmd, int *is_error);
/*
**	transformation
*/
void		translate(t_vector *pos, char *cmd, int *is_error);
void		rotate(t_vector *target, char *cmd, int *is_error);
/*
**	change cam, light
*/
void		change_light(int lightnum, int *is_error, int *quit_cmdmode);
void		change_camera(t_camlist *camlist, int camnum, int *is_error, int *quit_cmdmode);
void		rotate_camera(t_camlist *camlist, char *cmd, int *is_error);

#endif

