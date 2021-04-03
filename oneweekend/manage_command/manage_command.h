
#ifndef MANAGE_COMMAND_H
# define MANAGE_COMMAND_H
# define _USE_MATH_DEFINES

# include <math.h>
# include "../libft/libft.h"
# include "../utils/mymlx_utils.h"
# include "../ray_tracing/ray_tracing.h"
struct s_info
{
	t_camlist	*camlist;
	t_setup		setup;
};
typedef struct s_info	t_info;

//error
void	error_exit(t_info *info);
void	set_errflag(int *is_error);

//string
int		ft_strcmp(char *s1, char *s2);
void	pass_charset(char **str, const char *set);
double	read_dbl(char **s);
t_vector	read_vector(char **s);

//diverge_command
void	command(char *s, t_info *info);

//view
void	set_mlx_resolution(char *s, t_setup *setup, int *is_error);
void	set_ambient(char *s, int *is_error);
void	set_camera(char *s, t_info *info, int *is_error);
void	set_light(char *s, int *is_error);

//fiugres
void	set_fuzz_scatter(char *s, t_material *mat, int *is_error);
void	set_material(char *s, t_material **mat, int *is_error);
void	set_sphere(char *s, int *is_error);


#endif

