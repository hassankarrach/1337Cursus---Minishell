/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:08:27 by aelbasri          #+#    #+#             */
/*   Updated: 2023/11/02 17:03:42 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	c1;
	int				i;

	c1 = (unsigned char)c;
	i = (int)ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c1)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
