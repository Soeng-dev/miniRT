
# include "bmp_tools.h"

void	set_bmpheader(t_bh *bh)
{
	ft_memset(bh, 0, sizeof(t_bh));
	bh->bfh.bf_type = 0x4d42;
	bh->bfh.bf_off_bits = 54;
	

