#include "structs.h"

pthread_barrier_t   barrier_phase_end;
#define ITERATION 50
#define GET_NODE thread_args->array_ptr
#define FROM thread_args->from
#define TO thread_args->to
#define NEIGHBOUR_NODE neighbour_node_ptr->node_of_neighbours


void * thread_function (void *myargs)
{
  struct thread_arguments *thread_args = (struct thread_arguments *)myargs;
  struct neighbours *neighbour_node_ptr;
  pthread_barrier_wait(&barrier_phase_end);
  double give_rank = -1, give_each_neigbour_rank = -1;

  for(int i = 0; i < ITERATION; ++i)
  {
    pthread_barrier_wait(&barrier_phase_end);

    for(int j = FROM ; j < TO; ++j)
    {
     
      if(GET_NODE[j]->neighbour_num == 0)
        continue;

      give_rank = 0.85 * GET_NODE[j]->pagerank;
      GET_NODE[j]->pagerank -= give_rank;
      
      GET_NODE[j]->give_each_neigbour = (double)(give_rank / GET_NODE[j]->neighbour_num);

    }

    pthread_barrier_wait(&barrier_phase_end);

    for(int k = FROM ; k < TO; ++k)
    {
     
      if(GET_NODE[k]->neighbour_num == 0)
        continue;

      neighbour_node_ptr = GET_NODE[k]->my_neighbours;
      give_each_neigbour_rank = GET_NODE[k]->give_each_neigbour;

      while(neighbour_node_ptr != NULL)
      {
        get_lock(NEIGHBOUR_NODE);
        NEIGHBOUR_NODE->pagerank += give_each_neigbour_rank;
        release_lock(NEIGHBOUR_NODE);
        neighbour_node_ptr = neighbour_node_ptr->next;
      }
    }
  }

  return NULL;
}


int main(int argc, char *argv[]) {
  assert(argv[1] != NULL && argv[2] != NULL && "Wrong input format!");
  //head = NULL;
  int num_of_nodes = 0;
  int num_of_threads = atoi(argv[2]);

  num_of_nodes = read_file(argv[1]);
  printf("--------\nNum of Nodes: %d\nNum of threads: %d\n--------\n",num_of_nodes, num_of_threads);
  
  assert(num_of_nodes != 0 && "File is empty!\n");

  struct node *array_ptr[num_of_nodes];
  pthread_t my_threads[num_of_threads];

  pthread_barrier_init (&barrier_phase_end, NULL, num_of_threads);

  struct list_of_nodes *ptr = head;
  ptr = head;
  for (int i = 0; i < num_of_nodes; i++) {
    array_ptr[i] = head->node_entry;
    ptr = head;
    head = head->next;
    free(ptr);
  }
  free(head);

  //forall example from lectures
  int from = 0, to = num_of_nodes;
  int step = to/num_of_threads;
  struct thread_arguments thread_arg[num_of_threads];
  thread_arg->array_ptr = array_ptr;

  for(int i = 0; i < num_of_threads; i++)
  {
    thread_arg[i].array_ptr = array_ptr;
    thread_arg[i].from = from;
    thread_arg[i].to = (i < num_of_threads - 1) ? (from + step) : to;
    from = thread_arg[i].to;
    pthread_create (&(my_threads[i]), NULL, thread_function, &thread_arg[i]);
  } 

  for(int i = 0; i < num_of_threads; i++)   
		pthread_join((my_threads[i]), NULL);

  pthread_barrier_destroy(&barrier_phase_end);

  double add_all_pageranks = 0;
  for(int i = 0; i < num_of_nodes; i++)
  {
    add_all_pageranks += array_ptr[i]->pagerank;
  } 

  assert((fabs(add_all_pageranks - num_of_nodes) < 0.000001) && "Error in algorithm! Wrong implementation..\n");

  create_write_file(array_ptr, num_of_nodes);
  free_up_space    (array_ptr, num_of_nodes);
  return 0;
}