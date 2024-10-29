#ifndef graph_h
#define graph_h

#include <vector>
extern "C" {
#include "welt_c_basic.h"
#include "welt_c_fifo.h"  
#include "welt_c_util.h"
}

#include "welt_cpp_actor.h"
#include "welt_cpp_graph.h"


#include "txt_img_read.h"
#include "classifier.h"
#include "file_sink.h"

#include "../util2/cascadeClassifier.h"



#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <tuple>

#define BUFFER_CAPACITY 1024

/************* ACTORS ************/
#define ACTOR_STRCLASS_1  1
#define ACTOR_STRCLASS_2  2
#define ACTOR_STRCLASS_3  3

#define ACTOR_IMREAD 4
#define ACTOR_FILESINK 5  

/************* FIFOS ************/

#define FIFO_IMREAD_STRCLASS_1       1 
#define FIFO_STRCLASS_1_STRCLASS_2   2
#define FIFO_STRCLASS_2_STRCLASS_3   3 
#define FIFO_STRCLASS_3_FILESINK     4


#define ACTOR_COUNT 5
#define FIFO_COUNT  4

// Structure that holds all information for processed images.
struct img_data{

    // index: refers to the "index" indicating when the image was processed through the classifier
    int index;

    // data: holds the image pixelated into a 2-D vector for easier accessibility
    vector<vector<int>>* data;
};

class graph : public welt_cpp_graph{
public:
  graph(char* input_file, char* input_image_files, char* out_file_name, int img_num);

  ~graph();
  
  void scheduler() override;

  void setIters(int num_iter);

  int getIters();

  void setImgTotal(int num_img);

  int getImgTotal();
  
private:
  char *img_files;
  char *config_file;
  char *output_file;
  
  
  vector<StrongClassifier> strongClassifiers;

  
  int iterations;
  int total_imgs;
};

void graph_scheduler();

void graph_terminate();


#endif

