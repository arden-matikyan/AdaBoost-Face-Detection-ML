
#ifndef procImages_h
#define procImages_h

#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
using namespace std;

// Identify the class used to intialize the images received for our particular set (training vs testing)
class ProcImages {
 public:

  // Builds the class for us to use
  ProcImages();

  // Destroyer for our class
  ~ProcImages();

  // Loads our positive images(images with a face) and our negative images(images without face)
  // in order for us to use
  void imageDataProc(char* positiveDir,
                     char* negativedir,
                     int width, int height);

  // Returns all of the example faces used
  std::vector<std::vector<uint8_t>>& getExamples();

  // Returns the label for the particular image
  std::vector<int>& getLabels();

 private:

  // Function used to load a particular image from our particular set above
  std::vector<uint8_t> loadImage(const std::string& filepath, int width, int height);

  // Stores all of our sample images
  std::vector<std::vector<uint8_t>> examples;

  // Stores the corresponding labels to the sample images
  std::vector<int> labels;
};
#endif
