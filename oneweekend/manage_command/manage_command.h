
#ifndef MANAGE_COMMAND_H
# define MANAGE_COMMAND_H

# include "../libft/libft.h"
# include "../ray_tracing/ray_tracing.h"

//prog
void	error_exit(void);

//string
int		ft_strcmp(char *s1, char *s2);
void	pass_charset(char **str, const char *set);
double	read_dbl(char **s);
t_vector	read_vector(char **s);

//diverge_command
void	command(char *s, void *target);

//view
void	set_mlx_resolution(char *s, t_setup *setup, int *is_error);
void	set_ambient(char *s, int *is_error);
void	set_camera(char *s, t_camlist *camlist, double *scr_ratio, int *is_error);
#endif

