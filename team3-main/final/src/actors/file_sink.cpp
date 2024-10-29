#include <iostream>
#include <typeinfo>
#include <tuple>
#include "file_sink.h"

using namespace std;

file_sink::file_sink (welt_c_fifo_pointer in_fifo, char* output_file_name, int total_images_number) {

    in = (welt_c_fifo_pointer)in_fifo;
    file_name = output_file_name;
    total_images = total_images_number; 
    
    
    this->reset(); 
    
    false_positive_counter = 0; 
    true_postive_counter = 0; 
    mode = FILE_SINK_MODE_PROCESS;


}

bool file_sink::enable() {
    bool result = false;
    switch (mode) {
    
        // TODO: This also 
        case FILE_SINK_MODE_PROCESS:
            result = (welt_c_fifo_population(in) > 0);
            break;
        case FILE_SINK_MODE_SINK:
            result = true; 
            break;
        case FILE_SINK_MODE_ERROR:
            /* Modes that don't produce or consume data are always enabled. */
            result = true;
            break;
        default:
            result = false;
            break;
    }
    return result;
}

// Check invoke function to ensure that it works with newly created struct:
void file_sink::invoke() {
    switch (mode) {


        case FILE_SINK_MODE_PROCESS: {

            welt_c_fifo_read(in, &IIS);
      
            key = get<0>(*IIS);
            std::vector<std::vector<int>> img = get<1>(*IIS);
            
            /* 
            std::cout << "2D Vector:" << std::endl;
            for (const auto& row : img) {
            for (int element : row) {
                std::cout << element << " ";
              }
            std::cout << std::endl;
            }
            */ 
            
            cout << "Image #" <<key<<" has reached FILE_SINK \n" <<endl; 
            
            
            // ie. max_positive_index = 200 means that the first 200 images read in are faces and everything after that is not a face
            int max_positive_index = 999;  
            if (key <= max_positive_index){
                true_postive_counter++;
            }else{
                false_positive_counter++;
            }
            
           

            //Continues in the same mode
            mode = FILE_SINK_MODE_PROCESS;
            break;
        }
        case FILE_SINK_MODE_SINK: {
        
        
            cout<<"file_sink in MODE_SINK\n"<<endl;
        
           //Outputs data into the output file.
            outStream << "Total Images: "<< total_images << "\nTrue Positives: "<< true_postive_counter << "\nFalse Positives: "<< false_positive_counter << endl; 
            
          
            mode = FILE_SINK_MODE_SINK; 
            break; 
        }
        
        case FILE_SINK_MODE_ERROR: {
            /* Remain in the same mode, and do nothing. */
            break;
        }
        default:
            mode = FILE_SINK_MODE_ERROR;
            break;
    }
}


void file_sink::reset() {
    /* Close the file it is open, and then open/re-open the file so that
    subsequent invocations of the PROCESS MODE write from the beginning of
    the file.
    */
    if (outStream.is_open()) {
        outStream.close();
    }
    outStream.open(file_name);
    if (outStream.fail()) {
        cerr << "Could not open file \"" << file_name << "\"" << endl;
        mode = FILE_SINK_MODE_ERROR;
    } else {
        mode = FILE_SINK_MODE_PROCESS;
    }
}

file_sink::~file_sink() {
    outStream.close();
}

void file_sink::connect(welt_cpp_graph *graph) {
    int port_index;
    int direction;

    direction = GRAPH_OUT_CONN_DIRECTION;
    port_index = 0;
    graph->add_connection( this, port_index, direction);

}
