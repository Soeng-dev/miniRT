
#ifndef BMP_TOOLS_H
# define BMP_TOOLS_H

struct	s_bmpfile_header
{
	short int	bf_type;
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
typedef struct s_bmpinfo_header t_bih;

struct	s_bmp_header
{
	t_bfh	bfh;
	t_bih	bih;
};
typedef struct s_bmp_header		t_bh;

#endif
