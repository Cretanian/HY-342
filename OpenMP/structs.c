#include "structs.h"

struct list_of_nodes *head = NULL;

bool            node_exists_in_neighbors_list(struct node *src_node, struct node *dst_node)
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

// DONE
bool            got_infected()
{
    int random_value;
    random_value =  rand() % 2;

    if(random_value == 0)
        return false;
    else
        return true;
}

// DONE
bool            passed_away()
{
    int random_value;
    random_value =  rand() % 10000;

    if(random_value >= 34)
        return false;
    else
        return true;
}

/*--------------------------------*/

// DONE
void            init_new_node(long num, struct node *new_node)
{
    new_node->id = (int) num;
    new_node->my_neighbours = NULL;
    new_node->neighbour_num = 0;
    new_node->infected_flag = 0;
    new_node->days_infected = 0;
    return;
}

// DONE
struct node*    node_exists_in_list(long num)
{
    if(head == NULL)
        return NULL;

    struct list_of_nodes* tmp_start = head;

    while(tmp_start != NULL)
    {
        if(tmp_start->node_entry->id == (int) num)
            break;
        tmp_start = tmp_start->next;
    }

    if(tmp_start != NULL)
        return tmp_start->node_entry;
    else 
        return NULL;

}

// DONE
void            init_new_list_node(struct node *new_node,struct list_of_nodes *new_list_node)
{
    new_list_node->node_entry = new_node;
    new_list_node->next = NULL;
    return;
}

// DONE
void            sort_new_node(struct list_of_nodes *new_list_node)
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

// DONE
struct node*    check_existing_neigbor(struct node *src_node, struct node *dst_node)
{
    if(src_node->my_neighbours == NULL)
        return NULL;
    
    struct neighbours* neighbor = src_node->my_neighbours;

    while(neighbor != NULL)
    {
        if(neighbor->node_of_neighbours == dst_node)
            return  dst_node;
        neighbor = neighbor->next;     
    }
    
    return dst_node;
}

// DONE
void            add_neighbour(struct node *src_node, struct node *dst_node)
{
    if(check_existing_neigbor(src_node,dst_node) != NULL)
        return;
    
    struct neighbours* new_neighbor;
    new_neighbor = (struct neighbours*)malloc(sizeof(struct neighbours));

    new_neighbor->next = src_node->my_neighbours;
    new_neighbor->node_of_neighbours = dst_node;
    src_node->my_neighbours = new_neighbor;
    src_node->neighbour_num++;
    return;
}

// DONE
int             read_file(char *str, int FLAG)
{
    FILE *input_file;   
    input_file = fopen(str,"r");
    assert(input_file != NULL && "File can not open!\n");
    int num_of_nodes = 0;
    long src = -1, dst = -1;
    char line[4096];
    struct node             *src_node = NULL;
    struct node             *dst_node = NULL;
    struct list_of_nodes    *new_list_node_src = NULL;
    struct list_of_nodes    *new_list_node_dst = NULL;
  
    if(FLAG != -1)
    {
        while (fgets(line, sizeof(line), input_file) != NULL)
        {
            char *hash = strchr(line, '#');
            if (hash != NULL)
                continue;
            
            if(sscanf(line,"%ld", &src) != 1)
                continue;
        
            src_node = node_exists_in_list(src);

            if(src_node != NULL)
                continue;

            src_node = (struct node*)malloc(sizeof(struct node));
            assert(src_node != NULL);
            init_new_node(src, src_node); 
            src_node->infected_flag = 1;
            src_node->days_infected = 1;

            new_list_node_src = NULL;
            new_list_node_src = (struct list_of_nodes*)malloc(sizeof(struct list_of_nodes));
            assert(new_list_node_src != NULL);

            init_new_list_node(src_node, new_list_node_src);
            sort_new_node(new_list_node_src);
            ++num_of_nodes;
        }
    }
    else
    {
        while (fgets(line, sizeof(line), input_file) != NULL)
        {
            char *hash = strchr(line, '#');
            if (hash != NULL)
                continue;

            if(sscanf(line,"%ld %ld", &src, &dst) != 2)
                continue;

            src_node = node_exists_in_list(src);
            dst_node = node_exists_in_list(dst);
            
            if(src_node == NULL)
            {
                src_node = (struct node*)malloc(sizeof(struct node));
                assert(src_node != NULL);
                init_new_node(src, src_node); 

                new_list_node_src = NULL;
                new_list_node_src = (struct list_of_nodes*)malloc(sizeof(struct list_of_nodes));
                assert(new_list_node_src != NULL);

                init_new_list_node(src_node, new_list_node_src);

                sort_new_node(new_list_node_src);
                ++num_of_nodes;
            }

            if(dst_node == NULL)
            {
                dst_node = (struct node*)malloc(sizeof(struct node));
                assert(dst_node != NULL);
                init_new_node(dst, dst_node); 

                new_list_node_dst = NULL;
                new_list_node_dst = (struct list_of_nodes*)malloc(sizeof(struct list_of_nodes));
                assert(new_list_node_dst != NULL);

                init_new_list_node(dst_node, new_list_node_dst);

                sort_new_node(new_list_node_dst);
                ++num_of_nodes;
            }
    
            add_neighbour(src_node, dst_node);
            add_neighbour(dst_node, src_node);
        }
    } 

    fclose(input_file);
    return num_of_nodes;
}

// DONE
void            create_write_file(struct day_stats **array_ptr, int Days)
{
    FILE *output_file;
    char *filename = "analytics.csv";
    int TotalDeaths = 0;
    int TotalCases = 0;

    output_file = fopen(filename,"w+");
    assert(output_file != NULL && "Can not create analytics.csv file!\n");

    fprintf(output_file,"Day, NewCases, TotalCases, Recoverd, Active, NewDeaths, TotalDeaths");
    assert(array_ptr != NULL && Days != -1);

    for (int i = 0; i < Days; ++i)
    {
        TotalCases  +=  array_ptr[i]->NewCases;
        TotalDeaths +=  array_ptr[i]->NewDeaths;
        if(array_ptr[i]->Active < 0)
            array_ptr[i]->Active = 0;
        fprintf(output_file,"\n%d, %d, %d, %d, %d, %d, %d"
        ,i + 1, array_ptr[i]->NewCases,TotalCases,array_ptr[i]->Recovered,array_ptr[i]->Active,array_ptr[i]->NewDeaths,TotalDeaths);
    }

    fclose(output_file);
    return;
}

// DONE
void            free_up_space(struct node **ppl_list_head,struct day_stats **HEAD, int num_of_nodes, int Days)
{
    struct node *tmp = NULL;
    struct neighbours *tmp_neibour = NULL;

    assert(ppl_list_head != NULL && HEAD != NULL && Days != -1);

    for(int i = 0; i < num_of_nodes; ++i)
    {
        tmp = ppl_list_head[i];
        while(tmp->my_neighbours != NULL)
        {
            tmp_neibour = tmp->my_neighbours;
            tmp->my_neighbours = tmp->my_neighbours->next;
            free(tmp_neibour);
        }
        free(tmp);
    }
  
    for (int i = 0; i < Days; i++)    
        free(HEAD[i]);
    
    return;
}


/*--------------------------------*/

// DONE
void            init_new_day_stat(struct day_stats *node)
{
  node->NewCases    = 0;
  node->Recovered   = 0;
  node->Active      = 0;
  node->NewDeaths   = 0;
}

// DONE
void            init_output_days(struct day_stats **HEAD, int Days)
{
    for(int i = 0; i < Days; ++i)
    {
        HEAD[i] = (struct day_stats*)malloc(sizeof(struct day_stats));
        assert(HEAD[i] != NULL);
        init_new_day_stat(HEAD[i]);
    }
}

/*--------------------------------*/