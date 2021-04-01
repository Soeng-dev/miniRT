
# include <stdio.h>
# include "manage_command.h"

int		ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	pass_charset(char **str, const char *set)
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

void	command(char *s, void *target)
{
	//need to trim before strcmp
	//need to pass incremented char_ptr s 
	pass_charset(&s, " \t\n\v\f\r");
	if (!ft_strcmp("R", s))
		set_mlx_resolution(++s, (t_setup *)target);
	else if (!ft_strcmp("A", s))
		set_ambient(++s);
	else if (!ft_strcmp("c", s))

	else if (!ft_strcmp("l", s))
	{}
	else if (!ft_strcmp("sp", s))
	{}
	else if (!ft_strcmp("pl",s))
	{}
	else if (!ft_strcmp("sq", s))
	{}
	else if (!ft_strcmp("cy", s))
	{}
	else if (!ft_strcmp("tr", s))
	{}
	return ;
}

