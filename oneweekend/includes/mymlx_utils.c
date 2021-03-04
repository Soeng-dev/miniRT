/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:27:54 by soekim            #+#    #+#             */
/*   Updated: 2021/03/04 21:31:18 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ray_tracing.h"

void			pixput(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int		get_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | (b));
}
