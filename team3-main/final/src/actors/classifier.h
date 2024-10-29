#ifndef CLASSIFIER_H
#define CLASSIFIER_H

extern "C" {
// #include "welt_c_util.h"
#include "welt_c_fifo.h"
}

#include "welt_cpp_actor.h"
#include "welt_cpp_graph.h"


// TODO: should this be from /util2/ instead of /utility/ 

#include "../util2/featureUtil.h"
#include "../util2/strongClassifier.h"
#include "../util2/weakClassifier.h"

#include <chrono>
using namespace std::chrono;

using namespace std;

#define CONFIGURE 1
#define CLASSIFY  2 
#define READ      3
#define FALSE     4
#define TRUE      5

#define FACE    (Y)
#define NONFACE (N)

class classifier : public welt_cpp_actor{
public:
    classifier(StrongClassifier strong_classifier_in, 
    welt_c_fifo_pointer img_file_in, 
    welt_c_fifo_pointer img_file_out);

  
    ~classifier();

    bool enable() override;
    void invoke() override;

    float getTime();
    int getPositives();


    void reset() override;

    void connect(welt_cpp_graph *graph) override;

private:

    StrongClassifier classifier_in; 

    // Inputs information from images transformed into a 2-D vector of ints
    welt_c_fifo_pointer IIS_in;
    
    // Ouputs information from image onto next classifier/file_sink for reading
    welt_c_fifo_pointer IIS_out;
  

    tuple<int, std::vector<std::vector<int>>> *IIS;
    vector<vector<int>> (image);
    int key;
     
    float totaltime; 
    int totalpositives; 
    
    std::vector<tuple<FeatureUtil::FeatureType, int, int, int, int>> features;
    
};

#endif
