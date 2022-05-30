#include "lib_philosophers.h"

int	ft_error(char *str)
{
	ft_putstr("❌\e[1;91m Error: ");
	ft_putstr(str);
	return (1);
}
