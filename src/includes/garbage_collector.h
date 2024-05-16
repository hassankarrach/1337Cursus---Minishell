#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

typedef enum garbage{
    node_garbage,
    ptr_garbage,
    double_ptr_garbage
}               garbage_type;

typedef struct s_garbage_node{
    void                    *garbage_ptr;
    garbage_type            _garbage_type;
    struct s_garbage_node   *next;
}               garbage_node;


garbage_node	*new_garbage(void *garbage_ptr, garbage_type type);
void            add_garbage(garbage_node **lst, garbage_node *new_garbage);
void	        clear_garbage(garbage_node **head);
void	        *ft_malloc(size_t bytes, garbage_type type);

#endif