#include "../includes/minishell.h"

void	*ft_malloc(size_t bytes, garbage_type type)
{
	void	*ptr = malloc(bytes);
	if (!ptr)
		return (NULL);
	add_garbage(&global_minishell.garbage_head, new_garbage(ptr, type));
	return (ptr);
}

garbage_node	*new_garbage(void *garbage_ptr, garbage_type type)
{
	garbage_node	*garbage;

	garbage = (garbage_node *)malloc(sizeof(garbage_node));
	if (!garbage)
		return (NULL);
	garbage->garbage_ptr = garbage_ptr;
	garbage->_garbage_type = type;
	garbage->next = NULL;
	return (garbage);
}

void    add_garbage(garbage_node **lst, garbage_node *new_garbage)
{
	garbage_node	*curr_garbage;

	if (!(*lst))
	{
		(*lst) = new_garbage;
		return ;
	}
	curr_garbage = *lst;
	while (curr_garbage && curr_garbage -> next)
		curr_garbage = curr_garbage -> next;
	curr_garbage -> next = new_garbage;
}

void	clear_garbage(garbage_node **head)
{
	garbage_node    *curr_node;
	garbage_node    *next;

	curr_node = *head;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		if (curr_node->_garbage_type == node_garbage)
		{
			free(curr_node->garbage_ptr);
			next = curr_node->next;
			free(curr_node);
			curr_node = next;
		}
		else if (curr_node->_garbage_type == ptr_garbage)
		{

		}
		else if (curr_node->_garbage_type == double_ptr_garbage)
		{
			int i = 0;
			while ()
			{
			}
		}
	}
	*head = NULL;
}

// void    garbage_collector(void *ptr, int to_be_clean)
// {
//     static garbage_node *garbage_list;

//     if (to_be_clean)
//     {
//         clear_garbage(garbage_list);
//         return (NULL);
//     }
//     else
//     {

//     }
// }
