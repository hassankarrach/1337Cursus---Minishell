/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:17:29 by aelbasri          #+#    #+#             */
/*   Updated: 2023/12/28 20:21:58 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ctozero(char const *s, char c)
{
	char	*str;
	size_t	i;

	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		if (s[i] == c)
			str[i] = '\0';
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	nbr_of_strings(const char *s, char c)
{
	size_t	j;
	size_t	i;
	size_t	k;

	j = 0;
	k = 0;
	i = 0;
	while (s[j])
	{
		if (s[j] != c && i == 0)
		{
			k++;
			i = 1;
		}
		else if (s[j] == c)
			i = 0;
		j++;
	}
	return (k);
}

void	ft_free(char **splited)
{
	int	i;

	i = 0;
	if (splited == NULL)
		return ;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}

static char	**allocation(char **splited, size_t i, char *str)
{
	size_t	z;
	size_t	j;
	size_t	k;

	j = 0;
	while (j < i)
	{
		while (*str == '\0')
			str++;
		k = ft_strlen(str);
		splited[j] = (char *)malloc((k + 1) * sizeof(char));
		if (!splited[j])
		{
			ft_free(splited);
			return (NULL);
		}
		z = 0;
		while (k > z)
			splited[j][z++] = *(str++);
		splited[j][z++] = '\0';
		j++;
	}
	splited[j] = NULL;
	return (splited);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	*str;
	char	**splited1;
	char	**splited;

	if (!s)
		return (NULL);
	str = ctozero(s, c);
	i = nbr_of_strings(s, c);
	splited = (char **)malloc((i + 1) * sizeof(char *));
	if (!splited)
		return (NULL);
	splited1 = allocation(splited, i, str);
	free(str);
	return (splited1);
}
