#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

typedef struct s_garbage_node{
    void                    *garbage;
    struct s_garbage_node   *next;
}               garbage_node;

#endif