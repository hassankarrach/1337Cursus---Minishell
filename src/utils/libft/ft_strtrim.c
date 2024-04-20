/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:16:54 by aelbasri          #+#    #+#             */
/*   Updated: 2023/11/09 14:57:12 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_position(const char *s1, const char *set, int a)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(s1);
	if (a == 1)
		j = 0;
	else
		j = i - 1;
	while (i > 0)
	{
		k = 0;
		while (set[k])
		{
			if (set[k] == s1[j])
				break ;
			k++;
		}
		if (k == ft_strlen(set))
			break ;
		j += a;
		i--;
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	c;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = find_position(s1, set, 1);
	if (i == ft_strlen(s1))
	{
		str = (char *)malloc(1 * sizeof(char));
		if (!str)
			return (NULL);
		str[0] = 0;
		return (str);
	}
	j = find_position(s1, set, -1);
	str = (char *)malloc((j - i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	c = 0;
	while (i <= j)
		str[c++] = s1[i++];
	str[c] = '\0';
	return (str);
}
