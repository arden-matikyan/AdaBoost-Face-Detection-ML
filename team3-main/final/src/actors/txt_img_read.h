# ifndef txt_img_read_h
# define txt_img_read_h

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Each firing of this actor reads an image from a file and outputs a pointer to a
a 2-d vector representation of the image. The assumed image file format is the
Simple Text-based Image Format (STIF) supported in Welter.
Output (a): 
    The token type of the output is: pointer to a 2-d vector of integers.
Parameter(s): 
    The file_name parameter gives the name of file to be read. 
    The nRows and nCols parameters give the assumed dimensions of the images that are to be read.
Actor modes and transitions: 
    The READ mode reads an image from a file and stores the image to a 2-D vector internally 
        (as part of the internal state of the actor). A pointer of to the 2-D vector is then
        produced on the output edge. 
    The INACTIVE mode does nothing.
Initial mode: 
    The actor starts out in the READ mode .
Dataflow table:
    Mode out_fifo
- - - - - - - - - - - - - - - - - - - - - - - - - - - -
READ 1
INACTIVE 0
Limitations: At most one unconsumed output token of this actor should
be allowed to exist at any time. After a given firing F, the actor
should not be fired again until the token produced by F is consumed .
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <cstring>

extern "C" {
#include "welt_c_util.h"
#include "welt_c_fifo.h"
}
#include "welt_cpp_actor.h"
#include "welt_cpp_graph.h"

#include "../util2/featureUtil.h"

#define IMG_READ_MODE_INACTIVE            (1)
#define IMG_READ_MODE_SRC_UPDATE          (2)

class txt_img_read: public welt_cpp_actor {
public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    Construct a new txt_img_read actor that is associated with the given
    file name and image size dimensions, and connect the new actor to
    the given output FIFO.
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    txt_img_read (welt_c_fifo_pointer out_fifo, char* first_file_in, int img_num_in, int num_rows, int num_cols);
    ~txt_img_read () override;
    bool enable () override;
    void invoke () override;
    void reset () override;

    /* Associate the actor with a graph. */
    void connect (welt_cpp_graph* graph) override;

    /* Set the value of the actor’s file name parameter to the given string. */
    void setFileName (char* fileName);

    /* Return the value of the actor ’s file name parameter . */
    char* getFileName() const;

private:
    /* Output FIFO */
    welt_c_fifo_pointer out;

    /* First file name to read */
    char* first_file;
    char* present_file_name;

    /* Holding our file name within a specific variable so we can manipulate the file path for future images */
    char file_name_val[80];

    /* Holding location for present file to read */
    char* temp;

    
    string prefix; 

    /* Dimensions of the image to be read. */
    int nRows;
    int nCols;

    /* Total of images that actor is must compute. */
    int img_num;
    int img_index;
    int processed_img;
    
    
    
    int img_code; 
    

    /* Information where all the image is stored. */
    tuple<int, vector<vector<int>>>* IIS;
};
#endif
