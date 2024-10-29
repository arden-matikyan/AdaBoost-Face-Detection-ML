#ifndef featureUtil_h
#define featureUtil_h
#include <stdexcept>
#include <cstdint>
#include <tuple>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

/* This file goes through all five different of the Haar-Feature calculations, which includes:
                -intergal image
                -calculations between light vs dark pixels for each different Haar-Feature
                -intermediate calculations between comparing the integral images and the different Haar-Features
   In addition, it initializes every feature that can be used for the sample images,
   by describing the feature size, the width, the height, and the index for each feature.
*/

using namespace std;

// Initialize class used for describing different Haar-Features called FeatureUtil
class FeatureUtil {
 public:

  // Initialze a proper structure used to store information used by said Haar-Features
  struct FeatureData {

        // Stores original image data (pixelated) as a vector of unsigned integers
    std::vector<uint8_t> originalData;

        // Stores an integral image calculation (pixelated) as a 2-D vector of integers
    std::vector<std::vector<int>> integralData;

        // Stores the "contrast" of pixelated values (dark pixels vs. light pixels) for boosting algorithm
    std::vector<float> featureEvaluations;

        // Labels each feature a specific number for easier accessibility
    int label;
    float weight;
  };

  /* Within the Haar-Features, there's a maximum of 5 different Haar-Features:
                Horizontal Two Rectangle: A rectangle with a VERTICAL line separating a light and dark section
                        - (2x1, 2x2, 2x3, 2x4, 4x1, 4x2, 4x3, 4x4, ...)
                Vertical Two Rectangnle: A rectangle with a HORIZONTAL line separating a light and dark section
                        - (1x2, 2x2, 3x2, 4x2, 1x4, 2x4, 3x4, 4x4, ...)
                Horizontal Three Rectangle: A rectangle with two VERTICAL lines separating a light, dark, and light section (or vice versa) respectively
                        - (1x3, 2x3, 3x3, 4x3, ...)
                Vertical Three Rectangle: A rectangle with two HORIZONTAL lines separating a light, dark, and light section (or vice versa) respectively
                        - (3x1, 3x2, 3x3, 3x4, ...)
                Four Rectangle: A rectangle with grid-like divisions, with white and black sections diagonal from each other
                        - (2x2, 2x4, 4x2, 4x4, ...)
         Because there can only be a maximum of 5 different utilizations of Haar-Features, we use the enum function in order to
         initialize those unique Haar-Features, as shown below.
 */
  enum FeatureType {
                    HorizontalTwoRectangle,
                    VerticalTwoRectangle,
                    HorizontalThreeRectangle,
                    VerticalThreeRectangle,
                    FourRectangle
  };

  // Initializes the features width and height for the data type called "FeatureUtil"
  FeatureUtil(int width, int height);

  // Destroyer for the "FeatureUtil" data type
  ~FeatureUtil();

  // Calculates the integral image, and places it within the speified feature data
  std::vector<std::vector<int>> calculateIntegralImage(std::vector<uint8_t> imageData);

  // Used for calculating the integral image,
  // sums up the pixels within a specified region using the starting X and Y coordinates (startX & startY, respectively)
  // along with how big the specified region is in the X and Y directions (width & height, respectively)
  int sumRegion(std::vector<std::vector<int>> integralData, int startX, int startY, int width, int height);

  // Used in conjunction with the integral image,
  // evaluates the Haar-Feature, specified by the 5 different "FeatureTypes", explained above,
  // along with where the feature starting x and y coordinate (x & y, respectively)
  // in addition to how big the Haar-Feature is (width & height, respectively)
  float evaluateFeature(std::vector<std::vector<int>>& integralData,
                        FeatureType type, int x, int y, int width, int height);

  // Initializes all of the different feature configurations along with the variable dimensions and the feature types
  std::vector<tuple<FeatureType, int, int, int, int>> generateFeatureConfigs(int base_res);

  // Goes through all of the samples through the "examples" vector and "labels" vector
  // and inputs them into each samples data type
  std::vector<FeatureData> generateFeatures(std::vector<std::vector<uint8_t>> examples, std::vector<int> labels);

  // Computes the "contrast" value of the light vs dark pixels and puts them into the training data for further use
  std::vector<float> generateFeatureEvaluations(std::vector<std::vector<int>>& integralData, std::vector<tuple<FeatureUtil::FeatureType, int, int, int, int>> featureConfigs);

  // Gets the specified dimension, width and height of the sample images, and the size of a specific feature, respectively
  void writeFeatureData(const std::string& filename, const std::vector<FeatureData>& data);
  void writeFeatureData2(const std::string& baseFilename, const std::vector<FeatureData>& data);

  void readFeatureData(const std::string& filename, std::vector<FeatureData>& data);
  int getWidth();
  int getHeight();
  int getFeatureSize();
 private:

  // featureSize: Describes how big (type of feature?) the feature is
  int featureSize;

  // width: x dimension of the feature
  int width;

  // height: y dimension of the feature
  int height;

  // data: stores all of the pixels within a 2-D vector of ints
  std::vector<std::vector<int>> data;
};

#endif
