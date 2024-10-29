#include <iostream>
#include "graph.h"

using namespace std;

graph::graph(char* input_file, char* input_image_files, char* out_file_name, int img_num) {
  
  // Input/output files
  config_file = input_file; 
  img_files = input_image_files;
  output_file = out_file_name;

  // Total number of images to process
  total_imgs = img_num;


  // creating the strong classifier objects for the classifier ACTORS

  
  
  // load in strong classifiers using the Cascade Classifier object 
  CascadeClassifier *cascade = new CascadeClassifier();
  strongClassifiers = cascade->loadStrongClassifiers(input_file); 
  
  
  /* 
    
  int i =1; 
  for (auto& strongClassifier: strongClassifiers) {
        printf("    strongClassifer %d, , DR = %.2f, FPR = %.2f\n", 
        i,strongClassifier.getDR(), strongClassifier.getFPR());
        
        std::vector<WeakClassifier> weakClassifiers;
        weakClassifiers = strongClassifier.getClassifiers();
        for (auto& weakClassifier : weakClassifiers) {
            weakClassifier.print();
        }
        printf("\n\n");
        
        i++;
    }

  */ 

  // Set number of iterations used for graph
  iterations = 1;

  // Number of actors and FIFOs in this graph
  actor_count = ACTOR_COUNT;
  fifo_count = FIFO_COUNT;

  // Initialize FIFOs
  int token_size;

  /************************************
  INITIALIZE FIFOS 
  ************************************/ 

  fifos.reserve(fifo_count);
 
  // token_size is tuple of pointer to image and image index 
  token_size = sizeof(tuple<int, vector<vector<int>>*>*);

  
  // readimg to classifier 1 to 2, 2 to 3, 3 to compare 
  fifos[FIFO_IMREAD_STRCLASS_1] = ((welt_c_fifo_pointer)welt_c_fifo_new(BUFFER_CAPACITY, token_size, FIFO_IMREAD_STRCLASS_1));
  fifos[FIFO_STRCLASS_1_STRCLASS_2] =  ((welt_c_fifo_pointer)welt_c_fifo_new(BUFFER_CAPACITY, token_size, FIFO_STRCLASS_1_STRCLASS_2));
  fifos[FIFO_STRCLASS_2_STRCLASS_3] =  ((welt_c_fifo_pointer)welt_c_fifo_new(BUFFER_CAPACITY, token_size, FIFO_STRCLASS_2_STRCLASS_3));
  fifos[FIFO_STRCLASS_3_FILESINK] =  ((welt_c_fifo_pointer)welt_c_fifo_new(BUFFER_CAPACITY, token_size, FIFO_STRCLASS_3_FILESINK));
  
  


  /***************************************************************************
    Create actors in the actors vector and put descriptions
    for each actor in the descriptions vector.
    ***************************************************************************/

  actors.reserve(ACTOR_COUNT);
  descriptors.reserve(ACTOR_COUNT);



  // Actor for Image Read Actor - sends IIS to FORK 
  actors[ACTOR_IMREAD] = (new txt_img_read(fifos[FIFO_IMREAD_STRCLASS_1], input_image_files, total_imgs, 24, 24));
  descriptors[ACTOR_IMREAD] = ((char*)"actor txt image read");


  /* classifier actors  STRCLASS 1/2/3
    classifier(
    welt_c_fifo_pointer config_files_in, 
    welt_c_fifo_pointer img_file_in,
    welt_c_fifo_pointer img_file_out);
  */ 
  
  // classifier actor 1
  
  classifier *class1 = new classifier(strongClassifiers[0],fifos[FIFO_IMREAD_STRCLASS_1], fifos[FIFO_STRCLASS_1_STRCLASS_2]);
  actors[ACTOR_STRCLASS_1] = (class1);
  descriptors[ACTOR_STRCLASS_1] = ((char*)"actor configuration");

  // classifier 2  
  classifier *class2 = new classifier(strongClassifiers[1],fifos[FIFO_STRCLASS_1_STRCLASS_2], fifos[FIFO_STRCLASS_2_STRCLASS_3]);
  actors[ACTOR_STRCLASS_2] = class2;
  descriptors[ACTOR_STRCLASS_2] = ((char*)"actor configuration");

  // classifier 3  
  classifier *class3 = new classifier(strongClassifiers[2],fifos[FIFO_STRCLASS_2_STRCLASS_3], fifos[FIFO_STRCLASS_3_FILESINK]); 
  actors[ACTOR_STRCLASS_3] = class3;
  descriptors[ACTOR_STRCLASS_3] = ((char*)"actor configuration"); 

  // output from classifier 3
  actors[ACTOR_FILESINK] = (new file_sink(fifos[FIFO_STRCLASS_3_FILESINK], output_file, img_num));
  descriptors[ACTOR_FILESINK] = ((char*)"actor file sink");

}

void graph::scheduler(){
  int i;
  int iter;


  cout << "top of scheduler" << endl; 


  for(iter = 0; iter < getIters(); iter++){
  

     // invoke all strong classifiers once, will be in CONFIG MODE
     if(actors[ACTOR_STRCLASS_1]->enable()){
        actors[ACTOR_STRCLASS_1]->invoke();
        //cout<<"Invoked actor: ACTOR_STRCLASS_1 in Configure\n"; 
     }
     if(actors[ACTOR_STRCLASS_2]->enable()){
        actors[ACTOR_STRCLASS_2]->invoke();
        //cout<<"Invoked actor: ACTOR_STRCLASS_2 in Configure\n"; 
     }
     if(actors[ACTOR_STRCLASS_3]->enable()){
        actors[ACTOR_STRCLASS_3]->invoke();
        //cout<<"Invoked actor: ACTOR_STRCLASS_3 in Configure\n";
     }
    
    
      for(int i = 0; i < total_imgs; i++){
                
                if(actors[ACTOR_IMREAD]->enable()){
                  actors[ACTOR_IMREAD]->invoke();
                  //cout<<"Invoked actor: IM_READ \n"; 
                }
    
               // if there is IIS in FIFO then enable is true and we can invoke 
               if(actors[ACTOR_STRCLASS_1]->enable()){
                    //cout<<"Invoked actor: ACTOR_STRCLASS_1 in read\n";
                    actors[ACTOR_STRCLASS_1]->invoke();
                    
                    actors[ACTOR_STRCLASS_1]->invoke();
                    //cout<<"Invoked actor: ACTOR_STRCLASS_1 in classify\n";
                    actors[ACTOR_STRCLASS_1]->invoke();
                    //cout<<"Invoked actor: ACTOR_STRCLASS_1 in either TRUE or FALSE\n";
               
               }     
    
               
               if(actors[ACTOR_STRCLASS_2]->enable()){
                    //cout<<"Invoked actor: ACTOR_STRCLASS_2 in read\n";
                    actors[ACTOR_STRCLASS_2]->invoke();
                    actors[ACTOR_STRCLASS_2]->invoke();
                    //cout<<"Invoked actor: ACTOR_STRCLASS_2 in classify\n";
                    actors[ACTOR_STRCLASS_2]->invoke();
                    //cout<<"Invoked actor: ACTOR_STRCLASS_2 in either TRUE or FALSE\n";
                 
    
               }     
             
               if(actors[ACTOR_STRCLASS_3]->enable()){
                    //cout<<"Invoked actor: ACTOR_STRCLASS_3 in read\n";
                    actors[ACTOR_STRCLASS_3]->invoke(); 
                    actors[ACTOR_STRCLASS_3]->invoke();
                    //cout<<"Invoked actor: ACTOR_STRCLASS_3 in classify\n";
                    actors[ACTOR_STRCLASS_3]->invoke();
                    //cout<<"Invoked actor: ACTOR_STRCLASS_3 in either TRUE or FALSE\n";
    
               }     
            
              // in the read mode 
              if(actors[ACTOR_FILESINK]->enable()){
                  //cout<<"Invoked actor: ACTOR_FILESINK \n"; 
                  actors[ACTOR_FILESINK]->invoke();
                  
              }   
              
    
      } // end of for loop for number of images 

    
    // #define FILE_SINK_MODE_SINK (2)
    actors[ACTOR_FILESINK]->setMode(2);
    actors[ACTOR_FILESINK]->invoke();             
       
    
  } // end of iters 
  
    
  
  
}

void graph::setIters(int num_iter){
  iterations = num_iter;
}

int graph::getIters(){
  return iterations;
}

void graph::setImgTotal(int num_img){
  total_imgs = num_img;
}

int graph::getImgTotal(){
  return total_imgs;
}

graph::~graph() {}
