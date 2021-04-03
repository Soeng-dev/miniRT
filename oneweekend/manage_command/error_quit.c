
#include "manage_command.h"

void	error_return(int *is_error)
{
	*is_error = TRUE;
	return ;
}

void	error_exit(void)
{
	printf("Error\n");
	exit(0);
}
