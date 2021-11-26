#include "structs.h"


void check_days(int Days, int Num_Of_People,int Num_Of_Threads,struct day_stats **days_statistics,struct node **array_ptr )
{
  int newCases,newDeaths,recovered;
 
  struct node *node_ptr = NULL;
  struct neighbours *neighbour_node_ptr = NULL;

  for(int i = 1; i < Days; ++i)
  {
    newCases      = 0;
    newDeaths     = 0;
    recovered     = 0;

    #pragma omp parallel firstprivate(node_ptr,neighbour_node_ptr)
    {
      assert(Num_Of_Threads == omp_get_num_threads());

      int tmp_newCases      = 0;
      int tmp_newDeaths     = 0;
      int tmp_recovered     = 0;
      
      #pragma omp for 
      for(int k = 0; k < Num_Of_People; ++k)
      {
        node_ptr = array_ptr[k];

        if(NODE_FLAG == INFECTED)
        {
          neighbour_node_ptr = NODE_NEIGHBOURS;
          while(neighbour_node_ptr != NULL)
          {
              if( (NEIGHBOUR_FLAG == NEATRAL) && got_infected())             
                NEIGHBOUR_FLAG = TO_BE_INFECTED;
            neighbour_node_ptr = NEXT_NEIGHBOUR;
          }
          
          ++NODE_INFECTED_DAYS;
        
          if(passed_away())
          { 
            NODE_FLAG = DEAD;
            NODE_INFECTED_DAYS = -1;
            ++tmp_newDeaths;
          }
          else if(NODE_INFECTED_DAYS == 10)
          {
            NODE_FLAG = IMMORTAL;
            NODE_INFECTED_DAYS = -1;
            ++tmp_recovered;
          }
        }
      }

      #pragma omp barrier

      #pragma omp for
      for(int k = 0; k < Num_Of_People; ++k)
      {
        node_ptr = array_ptr[k];
        if(NODE_FLAG == TO_BE_INFECTED)
        {
          NODE_FLAG = INFECTED;
          ++tmp_newCases;
        }
      }
    
      #pragma omp critical
      {
        newCases      += tmp_newCases;
        newDeaths     += tmp_newDeaths;
        recovered     += tmp_recovered;
      }
    }

    days_statistics[i]->NewCases = newCases;
    days_statistics[i]->Recovered = recovered;
    days_statistics[i]->Active = (days_statistics[i-1]->Active + newCases) - (recovered + newDeaths);
    days_statistics[i]->NewDeaths = newDeaths;
  }
}


int main(int argc, char *argv[]) 
{
  clock_t t;
  assert(argv[1] != NULL && argv[2] != NULL &&  argv[3] != NULL &&  argv[4] != NULL && "Wrong input format!");
  int DAYS = atoi(argv[1]);
  int Num_Of_Threads = atoi(argv[4]);
  double time_taken;

  srand ( time (NULL));
  omp_set_dynamic(0);
  omp_set_num_threads(Num_Of_Threads);

  struct day_stats *days_statistics[DAYS];
  init_output_days(days_statistics, DAYS);

  int num_of_sick_nodes = read_file(argv[2], 0);
  assert(num_of_sick_nodes != 0 && "First file is empty!\n");

  days_statistics[0]->NewCases = num_of_sick_nodes;
  days_statistics[0]->Active = num_of_sick_nodes;

  int num_of_nodes = num_of_sick_nodes;
  num_of_nodes += read_file(argv[3], -1);

  assert(num_of_nodes != 0  && "Second file is empty!\n");

  struct node *array_ptr[num_of_nodes];
  struct list_of_nodes *ptr = NULL;
  ptr = head;
  for (int i = 0; i < num_of_nodes; ++i) {
    array_ptr[i] = head->node_entry;
    ptr = head;
    head = head->next;
    free(ptr);
  }
  free(head);

  t = clock();
  check_days(DAYS, num_of_nodes, Num_Of_Threads, days_statistics, array_ptr);
  t = clock() - t; 
  
  create_write_file(days_statistics, DAYS);
  free_up_space    (array_ptr, days_statistics, num_of_nodes, DAYS);

  time_taken = ((double)t)/CLOCKS_PER_SEC;
  printf("%f\n", time_taken);

  return 0;
}