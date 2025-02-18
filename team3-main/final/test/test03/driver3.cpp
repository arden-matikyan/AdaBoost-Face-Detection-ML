#include <stdio.h>
#include <iostream>
#include <ctime>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
extern "C" {
#include "welt_c_fifo.h"
#include "welt_c_util.h"
}

#include "welt_cpp_actor.h"
#include "welt_cpp_graph.h"
#include "classifier.h"

#include "graph.h"

#include <iostream>
#include <experimental/filesystem>

using namespace std;


//namespace FS=std::experimental::filesystem; 
int main(int argc, char **argv) {



    char *config_file = NULL;
    char *img_file = NULL;
    char *out_file = NULL;
   	char *num = NULL;  
 	int number = 0 ; 
 
	  int i = 0; 
   

	  int arg_count = 5; 
     
     
    const int graph_iters = 1;

        /* Check program usage. */
    if (argc != arg_count) {
        cerr << "driver.exe error: arg count" << endl;
        exit(1);
    }
  
  
 	  i = 1;
 	 
	config_file = argv[i++];
    img_file = argv[i++];
    out_file = argv[i++];

    number =atoi(argv[i++]);



//	cout << "num: "<< number<<endl; 

  	// cout << config_file << " " << img_file << " " << out_file << " " << number <<endl;  

		
  //   cout<<"outfile: " <<out_file<<endl;  
     
  
     auto* driver_graph = new graph(config_file, img_file, out_file, number);

    // Set the iteration count for graph execution. 
    driver_graph->setIters(graph_iters);

    // Execute the graph.
    driver_graph->scheduler();

    // Terminate graph

    
    
    return 0;



  
  return 0;
}
