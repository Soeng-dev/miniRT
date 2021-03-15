/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:27:54 by soekim            #+#    #+#             */
/*   Updated: 2021/03/15 21:03:57 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void			pixput(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int		get_color(t_vector colorvec, double gamma)
{
	int		color;

	colorvec = power(colorvec, 1.0 / gamma);
	color = (((int)colorvec.x << 16) | ((int)colorvec.y << 8) | ((int)colorvec.z));
	printf("%d\n", color);
	return (color);
}
