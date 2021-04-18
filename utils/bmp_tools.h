/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_tools.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_TOOLS_H
# define BMP_TOOLS_H
# include <fcntl.h>
# include "mymlx_utils.h"

# pragma pack(push, 1)

struct	s_bmpfile_header
{
	char		bf_type[2];
	int			bf_size;
	short int	bf_reserved1;
	short int	bf_reserved2;
	int			bf_off_bits;
};
typedef struct s_bmpfile_header	t_bfh;

struct	s_bmpinfo_header
{
	int			bi_size;
	int			bi_width;
	int			bi_height;
	short int	bi_planes;
	short int	bi_bit_count;
	int			bi_compression;
	int			bi_size_image;
	int			bi_xpels_permeter;
	int			bi_ypels_permeter;
	int			bi_clr_used;
	int			bi_clr_important;
};
typedef struct s_bmpinfo_header	t_bih;

struct	s_bmp_header
{
	t_bfh	bfh;
	t_bih	bih;
};
typedef struct s_bmp_header		t_bh;
# pragma pack(pop)

void	set_bmpheader(t_bh *bh, const t_screen *scr);
void	save_bmp(const t_img_data *img_data, const t_screen *scr, \
					t_bh bh, const char *path);

#endif
