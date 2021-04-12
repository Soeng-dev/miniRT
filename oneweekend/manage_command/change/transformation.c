
#include "../../miniRT.h"

void	translate(t_vector *pos, char *cmd, int *is_error)
{
	t_vector	input;

	pass_charset(&cmd, " \t\n\v\f\r");
	if (!(*cmd))
		return (set_errflag(is_error));
	input = read_vector(&cmd);
	*pos = add(*pos, input);
	return ;
}

void	rotate(t_vector *target, char *cmd, int *is_error)
{
	t_vector	axis;
	double		angle;

	pass_charset(&cmd, " \t\n\v\f\r");
	if (!(*cmd))
		return (set_errflag(is_error));
	axis = read_vector(&cmd);
	if (vector_is_same(axis, get_vector(0, 0, 0)))
		return (set_errflag(is_error));
	pass_charset(&cmd, " \t\n\v\f\r");
	if (!ft_isdigit(*cmd) && (*cmd != '-' && !ft_isdigit(*(cmd + 1))))
		return (set_errflag(is_error));
	angle = read_dbl(&cmd) * (M_PI / 180);
	printf("bf %f %f %f\n", target->x, target->y, target->z);
	*target = rotate_vector(*target, axis, angle);
	printf("af %f %f %f\n", target->x, target->y, target->z);
	return ;
}
