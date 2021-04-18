/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <soekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 00:50:03 by soekim            #+#    #+#             */
/*   Updated: 2020/08/13 02:46:16 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		go_test(char *string, char *find, int index)
{
	int j;

	j = 0;
	while (find[j] != '\0')
	{
		if (string[index] != find[j])
			return (0);
		index++;
		j++;
	}
	return (1);
}

char	*ft_strstr(char *str, char *to_find)
{
	char	*temp;
	int		i;

	if (!(*to_find))
		return (str);
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == to_find[0])
		{
			temp = &str[i];
			if (go_test(str, to_find, i))
			{
				temp = &str[i];
				return (temp);
			}
		}
	}
	return (0);
}
