/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:49:48 by hkarrach          #+#    #+#             */
/*   Updated: 2024/05/23 13:51:11 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

typedef struct s_garbage_node
{
	void					*garbage_ptr;
	struct s_garbage_node	*next;
}	t_garbage_node;

t_garbage_node	*new_garbage(void *garbage_ptr);
void			add_garbage(t_garbage_node **lst, t_garbage_node *new_garbage);
void			clear_garbage(t_garbage_node **head);
void			add_double_ptr_garbages(char **double_ptr);

#endif