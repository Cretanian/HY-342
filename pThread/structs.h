#ifndef __STRUCTS_H
#define __STRUCTS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#include <pthread.h>


struct node
{
    int id;
    double pagerank;
    double give_each_neigbour;
    struct neighbours *my_neighbours;
    int neighbour_num;
    pthread_mutex_t lock;
};

struct neighbours
{
    struct node *node_of_neighbours;
    struct neighbours *next;
};

struct list_of_nodes
{
    struct node *node_entry;
    struct list_of_nodes *next;
};

struct thread_arguments
{
  struct node **array_ptr;
  int from;
  int to;
};

extern struct list_of_nodes *head;

//About STRUCT_NODES
struct node* node_exists_in_list(int num);

bool node_exists_in_neighbors_list(struct node *src_node, struct node *dst_node);

void sort_new_node(struct list_of_nodes *new_list_node);

void init_new_node(long num, struct node *new_node);

void init_new_list_node(struct node *new_node,struct list_of_nodes *new_list_node);

void add_neighbour(struct node *src_node, struct node *new_dst_node, struct neighbours* new_neighbor);

void get_lock(struct node *node);

void release_lock(struct node *node);

//About FILES
int read_file(char *str);

void create_write_file(struct node **array_ptr, int num_of_nodes);

//About MEMORY
void free_up_space(struct node **array_ptr, int num_of_nodes);

#endif //STRUCTS_H