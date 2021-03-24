
#include "stdlib.h"

void	*ft_realloc(void *memblock, int size)
{
	void	*new;

	free(memblock);
	new = malloc(size);
	return (new);
}
