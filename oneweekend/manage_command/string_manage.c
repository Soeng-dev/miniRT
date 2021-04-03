
#include "manage_command.h"

int		ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1)
	{
		if (*s1 == *s2)
		{
			s1++;
			s2++;
		}
		else
			return (*s1 - *s2);
	}
}

void		pass_charset(char **str, const char *set)
{// if doesn't work correctly, refactor use is_element in libft
	int		setlen;
	int		i;

	if (!str || !(*str))
		return ;
	i = setlen;
	setlen = ft_strlen(set);
	while (**str)
	{
		i = -1;
		while (++i < setlen && **str != set[i]);
		if (i == setlen)
			(*str)++;
		else
			return ;
	}
	return ;
}

double		read_dbl(char **s)
{
	double	intiger;
	double	small;

	intiger = 0;
	small = 0;
	pass_charset(s, " \t\n\v\f\r");
	intiger = (double)ft_atoi(*s);
	pass_charset(s, "0123456789");
	if (**s == '.' && *(*s + 1))
	{
		while(ft_isdigit(*(++(*s))))
			small = small / 10 + (**s) / 10;
		pass_charset(s, "0123456789");
	}
	if (intiger > 0)
		return (intiger + small);
	else
		return (intiger - small);
}

t_vector	read_vector(char **s)
{
	t_vector	v;

	v.x = read_dbl(s);
	pass_charset(s, " \t\n\v\f\r,");
	v.y = read_dbl(s);
	pass_charset(s, " \t\n\v\f\r,");
	v.z = read_dbl(s);
	return (v);
}
