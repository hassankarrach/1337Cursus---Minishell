/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:15:51 by aelbasri          #+#    #+#             */
/*   Updated: 2023/11/13 10:06:09 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	setup(char *str, char const *s, size_t j, unsigned char start)
{
	size_t	i;

	i = 0;
	while (i < j)
		str[i++] = s[start++];
	str[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	char	*str;

	if (!s || (start >= ft_strlen(s)))
		return (NULL);
	if (len > (ft_strlen(s) - start))
		j = ft_strlen(s) - start;
	else
		j = len;
	str = (char *)malloc((j + 1) * sizeof(char));
	if (!str)
		return (NULL);
	setup(str, s, j, start);
	return (str);
}
