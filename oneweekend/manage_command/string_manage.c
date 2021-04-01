
#include "manage_command.h"

void		pass_charset(char **str, const char *set)
{
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

double		extract_dbl(char *s)
{
	double	intiger;
	double	small;

	intiger = 0;
	pass_charset(&s, " \t\n\v\f\r");
	intiger = (double)ft_atoi(s);
	pass_charset(&s, "0123456789");
	if (*s == '.' && (s + 1))
	{
		small = 0;
		while(ft_isdigit(*(++s)))
			small = small / 10 + (*s) / 10;
		bright += small;
		pass_charset(&s, "0123456789");
	}
	if (intiger > 0)
		return (intiger + small);
	else
		return (intiger - small);
}

t_vector	extract_vector(char *s)
{
	t_vector	v;

	pass_charset(&s, " \t\n\v\f\r");
	v.x = extract_dbl(s);
	pass_charset(&s, "0123456789.");
	pass_charseet(&s, " \t\n\v\f\r,");
	v.y = extract_dbl(s);
	pass_charset(&s, "0123456789.");
	pass_charseet(&s, " \t\n\v\f\r,");
	v.z = extract_dbl(s);
	return (v);
}
