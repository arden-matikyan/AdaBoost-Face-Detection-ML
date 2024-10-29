#include <iostream>
#include <typeinfo>
#include "classifier.h"

// constructor

 
classifier::classifier(StrongClassifier strong_classifier_in, 
            welt_c_fifo_pointer img_file_in,
		        welt_c_fifo_pointer img_file_out) {
    
    classifier_in = strong_classifier_in;
    IIS_in = img_file_in;
    IIS_out = img_file_out;
   
   totaltime = 0; 
   totalpositives = 0; 
   
     mode = CONFIGURE; 
}
    

bool classifier::enable() {
  bool result = false;
  switch (mode) {
   
  case CONFIGURE: {
  
    result = true;
    break;
  }
  
  case READ: {
  
    //TODO: CONFIRM CORRECT
    result = (welt_c_fifo_population(IIS_in) >= 1
                    && (welt_c_fifo_population(IIS_out)
                    < welt_c_fifo_capacity(IIS_out)));
      
    // cout << "Result: "<<  result << endl; 
  
    if (result == false){
      cout<<"Empty FIFO\n"; 
      return false;
    } 
    
    break;
  }
  case CLASSIFY: {
  
    result = true;
    break;
  }
  case FALSE: {
    
    // false doesn't do anything 
    result = true; 
    break;
  }
  case TRUE: {
  
    result = true;
    break;
  }
  default: {
  
    result = false;
    break;
  }
    return result;
  }
}

void classifier::invoke() {
  
  switch (mode) {
    case CONFIGURE: {
    
    
      FeatureUtil *ft = new FeatureUtil(24,24); 
      features = ft->generateFeatureConfigs(24);
    
      mode = READ;  
      break;
    }
    case READ: {
      
      // read in the IIS 
      welt_c_fifo_read(IIS_in, &IIS);
       
      mode = CLASSIFY;
      break;
    }
    case CLASSIFY: {
        
        
        // gather image    
        std::vector<std::vector<int>> img = get<1>(*IIS);
        
        auto start = high_resolution_clock::now();
        // call predict with image and features 
        int predict = classifier_in.predict(img, features);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        // cout << "duration: "  << duration.count() << endl;
         
         
        // Depending on what the classifiers classify the image as, the actor will change modes respectively.
        // predict function made of strong classifiers
        if(predict == 1){
          mode = TRUE;
          totaltime += duration.count();
          // cout<<"total time update: " << totaltime << endl;
          totalpositives++;
          // cout<<"total positive count update: " << totalpositives << endl;
          cout<<"Average time per positive classification: " << totaltime/totalpositives << endl;
          
        } else {
          mode = FALSE;
          // cout<<"predict false"<<endl;
        }
        
      break;
    }
    case FALSE: {
      
      cout << "Classified False"<<endl;
       
      mode = READ;
      break;
    }
    case TRUE: {
  
      cout << "Classified True"<<endl;
  
      std::tuple<int, std::vector<std::vector<int>>> *IIS_toSend;
      IIS_toSend = IIS; 

  
      welt_c_fifo_write(IIS_out, &IIS_toSend);
      mode = READ;  
      
      break;
    }
    default: {
  
      break;
    }
  }
}

void classifier::reset() {

}

void classifier::connect(welt_cpp_graph *graph) {
    int port_index;
    int direction;

    direction = GRAPH_IN_CONN_DIRECTION;
    port_index = 0;
    graph->add_connection(this, port_index, direction);

    direction = GRAPH_OUT_CONN_DIRECTION;
    port_index = 1;
    graph->add_connection(this, port_index, direction);

    direction = GRAPH_OUT_CONN_DIRECTION;
    port_index = 1;
    graph->add_connection(this, port_index, direction);
}

float classifier::getTime(){
  return totaltime;
  }
  
int classifier::getPositives(){
  return totalpositives; 
}

classifier::~classifier() {}
