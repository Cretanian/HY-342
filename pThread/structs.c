#include "structs.h"

struct list_of_nodes *head = NULL;

struct node* node_exists_in_list(int num)
{
    assert(head != NULL);
    struct list_of_nodes* tmp_start = NULL;

    tmp_start = head;

    while
    (tmp_start->node_entry->id != num
     &&
     tmp_start->next != NULL)
    {
        tmp_start = tmp_start->next;
    }

    if(tmp_start->node_entry->id == num)
        return tmp_start->node_entry;
    else if(tmp_start->node_entry->id != num)
        return NULL;

    assert(0 == 1);
    
    return NULL;
}

bool node_exists_in_neighbors_list(struct node *src_node, struct node *dst_node)
{
    struct neighbours *tmp;
    tmp = src_node->my_neighbours;

    if(tmp == NULL)
        return false;

    while
    (tmp->node_of_neighbours->id != dst_node->id 
    && 
    tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    if(tmp->node_of_neighbours->id != dst_node->id)
        return false;

    return true;
}

void sort_new_node(struct list_of_nodes *new_list_node)
{
    if(head == NULL)
        head = new_list_node;
    else
    {
        new_list_node->next = head;
        head = new_list_node;     
    }

    return;
}

void init_new_node(long num, struct node *new_node)
{
    new_node->id = (int) num;
    new_node->pagerank = (double) 1.000;
    new_node->my_neighbours = NULL;
    new_node->neighbour_num = 0;
    new_node->give_each_neigbour = 0;
    new_node->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    return;
}

void init_new_list_node(struct node *new_node,struct list_of_nodes *new_list_node)
{
    new_list_node->node_entry = new_node;
    new_list_node->next = NULL;
    return;
}

void add_neighbour(struct node *src_node, struct node *new_dst_node, struct neighbours* new_neighbor)
{
    new_neighbor->next = src_node->my_neighbours;
    new_neighbor->node_of_neighbours = new_dst_node;
    src_node->my_neighbours = new_neighbor;
    src_node->neighbour_num++;
    return;
}

void get_lock(struct node *node)
{
    assert(pthread_mutex_lock(&(node->lock)) == 0);
}

void release_lock(struct node *node)
{
    assert(pthread_mutex_unlock(&(node->lock)) == 0);
}

int read_file(char *str)
{
    FILE *input_file;   
    input_file = fopen(str,"r");
    assert(input_file != NULL && "File can not open!\n");
    int num_of_nodes = 0;
    long src = -1, dst = -1;
    char line[4096];

    while (fgets(line, sizeof(line), input_file) != NULL)
    {
        char *hash = strchr(line, '#');
        if (hash != NULL)
            continue;

        if(sscanf(line,"%ld %ld", &src, &dst) != 2)
            continue;

        if(head == NULL)
        {
            struct node* new_src_node;
            new_src_node = (struct node*)malloc(sizeof(struct node));
            init_new_node(src, new_src_node);


            struct node* new_dst_node; 
            new_dst_node = (struct node*)malloc(sizeof(struct node));
            init_new_node(dst, new_dst_node);


            //adding node to neighbor list
            struct neighbours* new_neighbor;
            new_neighbor = (struct neighbours*)malloc(sizeof(struct neighbours));
            add_neighbour(new_src_node, new_dst_node, new_neighbor);

            struct list_of_nodes* new_list_node_src;
            new_list_node_src = (struct list_of_nodes*)malloc(sizeof(struct list_of_nodes));
            init_new_list_node(new_src_node, new_list_node_src);

            struct list_of_nodes* new_list_node_dst;
            new_list_node_dst = (struct list_of_nodes*)malloc(sizeof(struct list_of_nodes));
            init_new_list_node(new_dst_node, new_list_node_dst);
           
            sort_new_node(new_list_node_dst);
            sort_new_node(new_list_node_src);

            assert(new_dst_node->my_neighbours == NULL 
                            && new_src_node->my_neighbours != NULL);
            num_of_nodes = num_of_nodes + 2;
        }
        else
        {
           struct node *src_node = NULL, *dst_node = NULL;
           src_node = node_exists_in_list(src);
           dst_node = node_exists_in_list(dst);
           
           if(src_node != NULL)
           {
               if(dst_node != NULL)
               {
                   //Both node exist
                    
                   //Checking if destination node already in neighbor list
                   bool exists_flag = false;
                   exists_flag = node_exists_in_neighbors_list(src_node, dst_node);

                   if(!exists_flag)
                   {
                       struct neighbours* new_neighbor;
                       new_neighbor = (struct neighbours*)malloc(sizeof(struct neighbours));
                       add_neighbour(src_node, dst_node, new_neighbor);
                   }
                  
                   assert(src_node->my_neighbours != NULL);
                   continue;
               }
               else if(dst_node == NULL)
               {
                   //Destination node doesn't exist

                   //creating node
                   struct node *new_dst_node;
                   new_dst_node = (struct node*)malloc(sizeof(struct node));
                   init_new_node(dst, new_dst_node);

                   //adding node to neighbor list
                   struct neighbours* new_neighbor;
                   new_neighbor = (struct neighbours*)malloc(sizeof(struct neighbours));
                   add_neighbour(src_node, new_dst_node, new_neighbor);
             
                   //adding node to list
                   struct list_of_nodes* new_list_node;
                   new_list_node = (struct list_of_nodes*)malloc(sizeof(struct list_of_nodes));
                   init_new_list_node(new_dst_node, new_list_node);
                   
                   sort_new_node(new_list_node);
             
                   assert(new_dst_node->my_neighbours == NULL);
                   num_of_nodes++;
                   continue;
               }

                assert(0 == 1);
           }
           else if(src_node == NULL)
           {
              
               if(dst_node != NULL)
               {
                   //Source node doesn't exist

                   //creating node
                   struct node* new_src_node;
                   new_src_node = (struct node*)malloc(sizeof(struct node));
                   init_new_node(src, new_src_node);

                   //adding node to neighbor list
                   struct neighbours* new_neighbor;
                   new_neighbor = (struct neighbours*)malloc(sizeof(struct neighbours));
                   add_neighbour(new_src_node, dst_node, new_neighbor);

                    //adding node to list
                   struct list_of_nodes* new_list_node;
                   new_list_node = (struct list_of_nodes*)malloc(sizeof(struct list_of_nodes));
                   init_new_list_node(new_src_node, new_list_node);
                   
                   sort_new_node(new_list_node);
             
                   num_of_nodes++;
                   assert(new_src_node->my_neighbours != NULL);
                   continue;
               }
               else if(dst_node == NULL)
               {
                   //Both node doesn't exist
                   struct node* new_src_node;
                   new_src_node = (struct node*)malloc(sizeof(struct node));
                   init_new_node(src, new_src_node);

                   struct node* new_dst_node; 
                   new_dst_node = (struct node*)malloc(sizeof(struct node));
                   init_new_node(dst, new_dst_node);

                   //adding node to neighbor list
                   struct neighbours* new_neighbor;
                   new_neighbor = (struct neighbours*)malloc(sizeof(struct neighbours));
                   add_neighbour(new_src_node, new_dst_node, new_neighbor);
      

                   struct list_of_nodes* new_list_node_src;
                   new_list_node_src = (struct list_of_nodes*)malloc(sizeof(struct list_of_nodes));
                   init_new_list_node(new_src_node, new_list_node_src);

                   struct list_of_nodes* new_list_node_dst;
                   new_list_node_dst = (struct list_of_nodes*)malloc(sizeof(struct list_of_nodes));
                   init_new_list_node(new_dst_node, new_list_node_dst);

                   sort_new_node(new_list_node_dst); 
                   sort_new_node(new_list_node_src); 
          
                   num_of_nodes = num_of_nodes + 2;
                   assert(new_dst_node->my_neighbours == NULL 
                             && new_src_node->my_neighbours != NULL);
                   continue;
               }

                assert(0 == 1);
           }
           assert(0 == 1);
        }  
    } 

    assert(num_of_nodes != 0 && "File is empty!");
    fclose(input_file);
    return num_of_nodes;
}

void create_write_file(struct node **array_ptr, int num_of_nodes)
{
    FILE *output_file;
    char *filename = "pagerank.csv";
   
    output_file = fopen(filename,"w+");
    assert(output_file != NULL && "Can not create pagerank.csv file!\n");

    fprintf(output_file,"node ID, Pagerank\n");
    assert(array_ptr != NULL && num_of_nodes != -1);

    for (int i = 0; i < num_of_nodes; i++) 
        fprintf(output_file,"%d, %0.3f\n", array_ptr[i]->id, array_ptr[i]->pagerank);
    
    fclose(output_file);
    return;
}

void free_up_space(struct node **array_ptr, int num_of_nodes)
{
    struct node *tmp = NULL;
    struct neighbours *tmp_neibour = NULL;

    assert(array_ptr != NULL && num_of_nodes != -1);

    for (int i = 0; i < num_of_nodes; i++)
    {
        tmp = array_ptr[i];
        while(tmp->my_neighbours != NULL)
        {
            tmp_neibour = tmp->my_neighbours;
            tmp->my_neighbours = tmp->my_neighbours->next;
            free(tmp_neibour);
        }
        free(array_ptr[i]);
    }
    return;
}
