
#include "fd_flush.h"

void	fd_flush(int fd)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0) {printf("flushed : %s\n", s);}
	if (s)
		free(s);
	return ;
}
