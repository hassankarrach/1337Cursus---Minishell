#include "../includes/minishell.h"

void	*ft_malloc(size_t bytes)
{
	void	*ptr = malloc(bytes);
	if (!ptr)
		return (NULL);
	add_garbage(&g_lobal_minishell.garbage_head, new_garbage(ptr));
	return (ptr);
}

garbage_node	*new_garbage(void *garbage_ptr)
{
	garbage_node	*garbage;

	garbage = (garbage_node *)malloc(sizeof(garbage_node));
	if (!garbage)
		return (NULL);
	garbage->garbage_ptr = garbage_ptr;
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

static void free_token_nodes(t_token **head)
{
    t_token *_head = *head;
    t_token *_tmp;

    while (_head)
    {
        _tmp = _head;
        _head = _head->next;
        free (_tmp->value);
        free (_tmp);
    }
    *head = NULL;
}

void    add_double_ptr_garbages(char **double_ptr)
{
    int i = 0;
    while (double_ptr[i])
    {
        add_garbage(&g_lobal_minishell.garbage_head, new_garbage(double_ptr[i]));
        i++;
    }
    add_garbage(&g_lobal_minishell.garbage_head, new_garbage(double_ptr));
}

void clear_garbage(garbage_node **head) {
    garbage_node *curr_node;
    garbage_node *next;

    free_token_nodes(&g_lobal_minishell.tokens);

    curr_node = *head;
    if (!curr_node)
        return;

    while (curr_node) {
        next = curr_node->next;
        if (curr_node->garbage_ptr)
            free(curr_node->garbage_ptr);
        free(curr_node);
        curr_node = next;
    }
    *head = NULL;
}
