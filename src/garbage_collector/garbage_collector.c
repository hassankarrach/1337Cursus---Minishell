#include "../includes/minishell.h"

garbage_node	*new_garbage(void *garbage_ptr)
{
	garbage_node	*garbage;

	garbage = (garbage_node *)malloc(sizeof(garbage_node));
	if (!garbage)
		return (NULL);
	garbage->garbage = garbage_ptr;
	return (garbage);
}

void    add_garbage(garbage_node **lst, garbage_node *new_garbage)
{
	garbage_node	*curr_garbage;

	if (!*lst)
	{
		*lst = new_garbage;
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
		free(curr_node->garbage);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*head = NULL;
}

void    garbage_collector(void *ptr, int to_be_clean)
{
    static garbage_node *garbage_list;

    if (to_be_clean)
    {
        clear_garbage(garbage_list);
        return (NULL);
    }
    else
    {

    }
}