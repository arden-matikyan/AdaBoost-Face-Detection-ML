#include "procImages.h"
#include <opencv2/opencv.hpp>
// Initializes images class for the testing/sample images
ProcImages::ProcImages() {}

// Destroyer function for testing/sample images
ProcImages::~ProcImages() {}

// Loads a particular image from a specific set
std::vector<uint8_t> ProcImages::loadImage(const std::string& filepath, int width, int height){

    // Use OpenCV to read the image
    cv::Mat img = cv::imread(filepath, cv::IMREAD_GRAYSCALE); // Reads image in grayscale
    if (!img.data) {
        std::cerr << "Failed to load image at " << filepath << std::endl;
        return std::vector<uint8_t>();
    }

    // Resize image if necessary
    if (img.cols != width || img.rows != height) {
        cv::resize(img, img, cv::Size(width, height));
    }

    // Convert Mat to std::vector<uint8_t>
    std::vector<uint8_t> image;
    if (img.isContinuous()) {
        image.assign(img.datastart, img.dataend);
    } else {
        for (int i = 0; i < img.rows; ++i) {
            image.insert(image.end(), img.ptr<uint8_t>(i), img.ptr<uint8_t>(i) + img.cols);
        }
    }

    return image;
}

// Loads images from the positive directory (faces) and negative directory (non-faces)
void ProcImages::imageDataProc(char* positiveDir,
                               char* negativeDir,
                               int width, int height) {
  
  int i = 0;
  // Load positive images (faces)
  for (const auto& entry : std::filesystem::directory_iterator(positiveDir)) {
    std::vector<uint8_t> image = loadImage(entry.path().string(), width, height);
    if (!image.empty() && i < 2200) {
      examples.push_back(image);
      labels.push_back(1);
    }
   i ++;
  }
  
  i = 0;
  // Load negative images (non-faces)
  for (const auto& entry : std::filesystem::directory_iterator(negativeDir)) {
    std::vector<uint8_t> image = loadImage(entry.path().string(), width, height);
    if (!image.empty() && i < 2200) {
      examples.push_back(image);
      labels.push_back(-1);
    }
    i ++;
  }
}

// Return example images for reading purposes
std::vector<std::vector<uint8_t>>& ProcImages::getExamples() {
        return examples;
}

// Returns the label for the example images
std::vector<int>& ProcImages::getLabels() {
  return labels;
}

