#include "libft.h"

int ft_is_space(char c)
{
    if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
        return (1);
    return (0);
}