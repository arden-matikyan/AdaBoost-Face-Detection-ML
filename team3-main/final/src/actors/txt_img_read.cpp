#include "txt_img_read.h"

using namespace std;

txt_img_read::txt_img_read(welt_c_fifo_pointer out_fifo, char* first_file_in, int img_num_in, int num_rows, int num_cols){
    
    // Changes the mode into the reading mode for the actor.
    mode = IMG_READ_MODE_SRC_UPDATE;
    
    first_file = first_file_in;
    
    // Stores our first file into the temporary value for the actor to read into the data.
    strcpy(file_name_val, first_file);
    present_file_name = &file_name_val[0];

    img_num = img_num_in;
    
    prefix = "dataset/face ("; 
   
    img_code = 0; 
    processed_img = 0;
    img_index = 0;

    nRows = num_rows;
    nCols = num_cols;
    out = out_fifo;
}

bool txt_img_read::enable(){
    bool result = false;
    switch (mode) {
        case IMG_READ_MODE_SRC_UPDATE:
            result = (welt_c_fifo_population(out) <
                      welt_c_fifo_capacity(out));
            break;
        case IMG_READ_MODE_INACTIVE:
            result = false;
            break;
        default:
            result = false;
            break;
    }
    return result;
}

void txt_img_read::invoke(){

   
    // Does a particular part of the code once the actor is in a particular mode.
    switch(mode){
        case IMG_READ_MODE_SRC_UPDATE:{
        
            
           img_code++;
           
           string filename = prefix + std::to_string(img_code) + ").txt"; 
           
           cout<<"image read SRC_UPDATE reading from "<< filename <<endl; 
            
            // AFTER THE 50th IMAGE WE SWITCH TO NO FACE SAMPLES 
           if (prefix == "dataset/face (" && img_code == 1000){
             // CHANGE PREFIX 
             prefix = "dataset/bad (";
             //RESET CODE 
             img_code = 0; 
           } 
           
             
            // int prefix1 = fn.find_last_of("/");
            // int prefix2 = fn.find_last_of("_");
             //string dir = fn.substr(0,dirIndex+1); 
             
             //cout <<" DIR: " << dir << endl;
             
             //next_file_name = in_prefix + next_string + in_suffix;
             //strcpy(present_file_name, next_file_name.c_str());

           
           

            // ****************** Process file ****************************************

            // collect image as 2D vector from the file 
            vector<vector<int> > pixels(nRows, vector<int> (nCols, 0));
            FILE *filePtr = NULL;
            filePtr = fopen(filename.c_str(), "r");
            if (filePtr == NULL) {
                perror("fopen: ");
                exit(EXIT_FAILURE);
            }
            for (int iRow = 0; iRow < nRows; iRow++)
            {
                for (int iCol = 0; iCol < nCols;iCol++)
                {
                    int data = 0;
                    if (!fscanf(filePtr, "%d,", &data)){
                        perror("fscanf: ");
                    }
                    pixels[iRow][iCol] = data;
                }
            }
            fclose(filePtr);

            // convert the pixels from file to integral image 
            vector<vector<int>> integral(nRows, vector<int> (nCols, 0));
            integral[0][0] = pixels[0][0];
            for(int x = 1; x < 24; ++x){
                integral[0][x] = integral[0][x-1] + pixels[0][x];
            }
            for(int y = 1; y < 24; ++y){
                integral[y][0] = integral[y-1][0] + pixels[0][y];
            }
            for(int y = 1; y < 24; ++y){
                for(int x = 1; x < 24; ++x){
                    integral[y][x] = pixels[y][x] + integral[y-1][x] + integral[y][x-1] - integral[y-1][x-1];
                }
            }

           
                
            /*
            std::cout << "2D Vector:" << std::endl;
            for (const auto& row : integral) {
            for (int element : row) {
                std::cout << element << " ";
              }
            std::cout << std::endl;
            }
            */
            
           
            // create IIS and pointer 
            IIS = new std::tuple<int, std::vector<std::vector<int>>>(img_index, integral);
            auto imgptr = get<1>(*IIS);
            
            welt_c_fifo_write(out, &IIS);
            // increase image key value 
            img_index++;
            
            // ****************************************************************************************************
           
             
            // Increases the processed image by 1
            processed_img++;

            // Keeps the same mode in order to continue processing.
            mode = IMG_READ_MODE_SRC_UPDATE;
            break; 
        }
        case IMG_READ_MODE_INACTIVE:{
            mode = IMG_READ_MODE_INACTIVE;
            break;   
        }
        default:{
            mode = IMG_READ_MODE_INACTIVE;
            break;
        }
    }
}

txt_img_read::~txt_img_read(){}

void txt_img_read::reset(){
    mode = IMG_READ_MODE_SRC_UPDATE;
}

void txt_img_read::connect(welt_cpp_graph *graph){
    int port_index;
    int direction;

    direction = GRAPH_IN_CONN_DIRECTION;
    port_index = 0;
    graph->add_connection(this, port_index, direction);
}
