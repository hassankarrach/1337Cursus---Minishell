#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*last;

	i = 0;
	last = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			last = ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char)c)
		last = ((char *)&str[i]);
	return (last);
}