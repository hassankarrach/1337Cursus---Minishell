/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:21:28 by aelbasri          #+#    #+#             */
/*   Updated: 2023/11/09 10:06:02 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*p;
	int		i;

	if (!lst)
		return (NULL);
	i = ft_lstsize(lst) - 1;
	p = lst;
	while (i > 0)
	{
		p = p->next;
		i--;
	}
	return (p);
}
