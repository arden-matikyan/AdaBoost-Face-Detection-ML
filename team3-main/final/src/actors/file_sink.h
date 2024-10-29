#ifndef PROJECTNAME_FILE_SINK_H
#define PROJECTNAME_FILE_SINK_H

#include <fstream>
#include <string>
extern "C" {
#include "welt_c_util.h"
#include "welt_c_fifo.h"
}

#include "welt_cpp_actor.h"
#include "welt_cpp_graph.h"

using namespace std;

/* Actor modes */
#define FILE_SINK_MODE_PROCESS (1)
#define FILE_SINK_MODE_SINK (2)
#define FILE_SINK_MODE_ERROR (3)
#define FILE_SINK_MODE_COMPLETE (4)

class file_sink : public welt_cpp_actor{
public:
    /*************************************************************************
    Construct a file sink actor with the specified input FIFO connection
    and the specified output file name.
    *************************************************************************/
    file_sink(welt_c_fifo_pointer in, char* file_name, int total_images_number);

    /*Destructor*/
    ~file_sink() override;

    bool enable() override;

    void invoke() override;

    /* Reset the actor so that the output file is re-opened for writing,
       discarding any previously written contents in the file.
    */
    void reset() override;

    void connect(welt_cpp_graph *graph) override;


private:
    char* file_name;
    ofstream outStream;
    tuple<int, vector<vector<int>>>* image_information;
    welt_c_fifo_pointer in;

    int total_images; 
    int false_positive_counter; 
    int true_postive_counter; 
    
    tuple<int, std::vector<std::vector<int>>> *IIS;
    int key; 
    

};

#endif //PROJECTNAME_FILE_SINK_H
