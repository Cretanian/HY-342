#ifndef __STRUCTS_H
#define __STRUCTS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>

#define DAYS N
#define DEAD -1
#define NEATRAL 0
#define INFECTED 1
#define TO_BE_INFECTED 2
#define IMMORTAL 3

#define NEIGHBOUR_NODE neighbour_node_ptr->node_of_neighbours
#define NEXT_NEIGHBOUR neighbour_node_ptr->next
#define NEIGHBOUR_FLAG NEIGHBOUR_NODE->infected_flag
#define NODE_NEIGHBOURS node_ptr->my_neighbours
#define NODE_FLAG node_ptr->infected_flag
#define NODE_INFECTED_DAYS node_ptr->days_infected
struct node
{
    int id;
    struct neighbours *my_neighbours;
    int neighbour_num;
    int infected_flag;
    int days_infected;
    
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

struct day_stats
{
  int NewCases;
  int Recovered;
  int Active;
  int NewDeaths;
};

extern struct list_of_nodes *head;

//About STRUCT_NODES

bool            got_infected();

bool            passed_away();

bool            node_exists_in_neighbors_list(struct node *src_node, struct node *dst_node);

void            init_new_node(long num, struct node *new_node);

struct node*    node_exists_in_list(long num);

void            init_new_list_node(struct node *new_node,struct list_of_nodes *new_list_node);

void            sort_new_node(struct list_of_nodes *new_list_node);

void            add_neighbour(struct node *src_node, struct node *dst_node);

int             read_file(char *str, int FLAG);

//About FILES
void            create_write_file(struct day_stats **array_ptr, int Days);

void            create_write_file(struct day_stats **array_ptr, int Days);

//About MEMORY
void            free_up_space(struct node **ppl_list_head,struct day_stats **HEAD, int num_of_nodes, int Days);

void            init_new_day_stat(struct day_stats *node);

void            init_output_days(struct day_stats **HEAD, int Days);

#endif //STRUCTS_H