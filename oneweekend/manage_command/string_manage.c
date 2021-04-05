
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
			break;
	}
	return (*s1 - *s2);
}

int		is_element(const char *set, char c)
{
	if (!set)
		return (-1);
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

void		pass_charset(char **str, const char *set)
{// if doesn't work correctly, refactor use is_element in libft

	if (!str || !(*str))
		return ;
	while (**str)
	{
		if (is_element(set, **str))
			(*str)++;
		else
			return;
	}
	return ;
}
