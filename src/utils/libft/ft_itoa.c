/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 08:29:37 by aelbasri          #+#    #+#             */
/*   Updated: 2023/11/13 10:02:06 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count(long int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	if (i == 0)
		i = 1;
	return (i);
}

static char	*allocation(char *str, int i, int j, long int nb)
{
	while (i > 0)
	{
		str[--i] = (nb % 10) + 48;
		nb = nb / 10;
	}
	if (j == 1)
		str[i] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	long int	nb;
	char		*str;
	int			i;
	int			j;
	int			k;

	nb = (long int)n;
	j = 0;
	if (nb < 0)
	{
		j = 1;
		nb *= -1;
	}
	i = count(nb) + j;
	k = i;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	allocation(str, i, j, nb);
	str[k] = '\0';
	return (str);
}
