
# include <stdio.h>
# include "../miniRT.h"

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

void	command(char *s)
{
	s = ft_strtrim(s, " \t\n\v\f\r");
	if (!ft_strcmp("resize", s))
	{}
	else if (!ft_strcmp("translate", s))
	{}
	else if (!ft_strcmp("rotate", s))
	{}
	else if (!ft_strcmp("light", s))
	{}
	else if (!ft_strcmp("

