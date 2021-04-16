/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_tools.h"

void	set_bmpheader(t_bh *bh, const t_screen *scr)
{
	ft_memset(bh, 0, sizeof(t_bh));
	bh->bfh.bf_type[0] = 'B';
	bh->bfh.bf_type[1] = 'M';
	bh->bfh.bf_size = 54 + 4 * (int)scr->height * (int)scr->width;
	bh->bfh.bf_off_bits = 54;
	bh->bih.bi_size = 40;
	bh->bih.bi_width = (int)scr->width;
	bh->bih.bi_height = (int)scr->height;
	bh->bih.bi_planes = 1;
	bh->bih.bi_bit_count = 32;
	bh->bih.bi_size_image = ((((int)scr->width * sizeof(int) + 3) / 4) * 4)\
							* (int)scr->height;
	return ;
}

void	save_bmp(const t_img_data *img_data, const t_screen *scr, \
					t_bh bh, const char *path)
{
	int		fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	bh.bih.bi_height *= -1;
	write(fd, &bh, sizeof(t_bh));
	write(fd, img_data->addr, sizeof(int) * (int)scr->height * (int)scr->width);
	close(fd);
	return ;
}
