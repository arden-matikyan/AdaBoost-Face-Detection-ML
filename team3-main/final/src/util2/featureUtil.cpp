#include "featureUtil.h"
#include <unordered_set>

// Initializes the feature utility for all Haar-Features
FeatureUtil::FeatureUtil(int w, int h) {
  width = w;
  height = h;
}

// Code structure for calculating the integral image, using the sample's original image
std::vector<std::vector<int>> FeatureUtil::calculateIntegralImage(std::vector<uint8_t> imageData) {


        // Initializes a 2-D vector to store the integral data when calculating the integral image
    std::vector<std::vector<int>> integralData(height, std::vector<int>(width, 0));

        // Beginning of the integral image (top-left corner)
        // is exactly the same pixel value of the original image, thus we just copy and paste the pixel value
    integralData[0][0] = imageData[0];

        // This loop is used for calculating the top row of the integral image
    for (int x = 1; x < width; ++x) {

                // We add the pixel value to the left of the integrated image to the pixel value of the original image and
                // we do this until we finish off the top row of the integrated image, indicated by the "width" of the original image
        integralData[0][x] = integralData[0][x-1] + imageData[x];
    }

        // This loop is used for calculating the first column of the integral image
    for (int y = 1; y < height; ++y) {

                // We add the pixel value above the integrated image to the pixel value of the original image and
                // we do this until we finish off the first column of the integrated image, indicated by the "height" of the original image
                integralData[y][0] = integralData[y-1][0] + imageData[y * width];
    }

        // This loop is used for calculating the rest of the integral image, besides the first row and column
    for (int y = 1; y < height; ++y) {
        for (int x = 1; x < width; ++x) {

                        // For a new pixel location in the integrated image,
                        // we add the original image corresponding location's pixel value to
                        // the integrated image's pixel value to the left, above, and diagonally left
                        // of the new pixel location.
            integralData[y][x] = imageData[y * width + x] +
                                 integralData[y-1][x] +
                                 integralData[y][x-1] -
                                 integralData[y-1][x-1];
        }
    }

        // We submit our newly integrated image, into our feature(image) data
        // under the type of "integralData"
    return integralData;
}

// Function used to destroy our featureUtil class
FeatureUtil::~FeatureUtil(){}

// Function used to return the "width" variable of our FeatureUtil class
int FeatureUtil::getWidth(){
  return width;
}

// Function used to return the "height" variable of our FeatureUtil class
int FeatureUtil::getHeight(){
  return height;
}

// Function used to return the "FeatureSize" variable of our FeatureUtil class
int FeatureUtil::getFeatureSize() {
  return featureSize;
}

// Function used for summing up the pixels within a particular region of our integral image
// using the starting X and Y coordinates (startX and startY, respectively),
// in addition to how big the region is in the X and Y directions (width and height, respectively)
int FeatureUtil::sumRegion(std::vector<std::vector<int>> integralData,
                           int startX, int startY,
                           int width, int height) {

  // Start by figuring out our ending X and Y coordinate of our region,
  // by adding the width and height of our identified region and subtracting 1
  // as our array values start at 0
  int endX = startX + width - 1;
  int endY = startY + height - 1;

  // The total pixel value is already calculated through the integral image
  // which is at the location of our endY and endX coordinates, pushed through an int called "total"
  int total = integralData[endY][endX];

  // The value of the pixel above our final location(top-right location) is put through an if-else statement:
  // If startY is greater than 0, then our int "above" is the integral image's pixel value above our location
  // Otherwise, the value of the pixel is 0 as there's no pixel value above the top row (indicated by 0)
  int above = startY > 0 ? integralData[startY-1][endX] : 0;

  // The value of the pixel left of our final location(bottom-left location) is put through an if-else statement:
  // If startX is greater than 0, then our int "left" is the integral image's pixel value to the left of our location
  // Otherwise, the value of the pixel is 0 as there's no pixel to the left of the leftmost column (indicated by 0)
  int left = startX > 0 ? integralData[endY][startX-1] : 0;

  // The value of the pixel in the top left corner of our region is put through an if-else statement:
  // If startX AND startY is greater than 0, than our int "topLeftCorner" is the integral image's pixel value diagonally left of our starting location
  // Otherwise, the value of the pixel is 0 as there's no pixel diagonally left of the top left corner (indicated by 0)
  int topLeftCorner = (startX > 0 && startY > 0) ? integralData[startY - 1][startX - 1] : 0;


  // Sanity check to see if our values are the correct values used to calculate the sum of the region
  //printf("endX = %d, endY = %d, total = %d, above = %d, left = %d, topLeftCorner = %d\n",
         //endX, endY, total, above, left, topLeftCorner);

  // We return the value of region sum by subtracting the total value of pixels by the above(top-right) and left(bottom-left)
  // and adding the topLeftCorner, since it got subtracted twive from above and left variables

  int sum = total - above - left + topLeftCorner;
  if (0) {

    printf("endX = %d, endY = %d, total = %d, above = %d, left = %d, topLeftCorner = %d\n",
    endX, endY, total, above, left, topLeftCorner);

    printf("endX = %d, endY = %d, total = %d, above = %d, left = %d, topLeftCorner = %d\n",
    endX, endY, total, above, left, topLeftCorner);

  }
 
  return total - above - left + topLeftCorner;
};

// Used to evaluate the feature depending on the five different kinds of Haar-Features
// and their respective dimensions
float FeatureUtil::evaluateFeature(std::vector<std::vector<int>>& integralData,
                                   FeatureType type,
                                   int x, int y,
                                   int width, int height) {
  // Initialize the regions in which we sum the light and dark regions
  // in addition to finding out where the midpoint is or if our Haar-Feature
  // is split into thirds.
  int sumRegion1 = 0;
  int sumRegion2 = 0;
  int midPoint = 0;
  int thirdWidth = 0;
  int thirdHeight = 0;
  // Because there are 5 different types of Haar-Feartures
  // we go through the 5 different cases in order to account for that.
  switch (type) {

  // For the Horizontal Two Rectangle class,
  // we identify the midpoint as half of the original width,
  // and the sum of the regions to be to the left of the midpoint(light pixels) and to the right of the midpoint(dark pixels)
  case HorizontalTwoRectangle: {
    midPoint = width / 2;
    sumRegion1 = sumRegion(integralData, x, y, midPoint, height);
    sumRegion2 = sumRegion(integralData, x + midPoint, y, width - midPoint, height);
    break;
  }

  // For the Vertical Two Rectangle class,
  // the procedure is nearly identical to the Horizontal Two Rectangle class,
  // except that the sum of the regions will be above the midpoint(light pixels) and below the midpoint(dark pixels)
  case VerticalTwoRectangle: {
    midPoint = height / 2;
    sumRegion1 = sumRegion(integralData, x, y, width, midPoint);
    sumRegion2 = sumRegion(integralData, x, y + midPoint, width, height - midPoint);
    break;
  }

  // Similar to the Horizontal Two Rectangle class,
  // instead of calculating a specific midpoint, the Haar-Feature is split into thirds
  // so we must split our region totals into thirds as well using thirdWidth and
  // have two of our regions be light pixels compared to the single dark pixel section.
  case HorizontalThreeRectangle: {
    thirdWidth = width / 3;

        // Generally, we sum the leftmost and the rightmost part of the section together (light pixels)
        // and the middle section of the section together (dark pixels)
    sumRegion1 = sumRegion(integralData, x, y, thirdWidth, height)
      + sumRegion(integralData, x + 2 * thirdWidth, y, width - 2 * thirdWidth, height);
    sumRegion2 = sumRegion(integralData, x + thirdWidth, y, thirdWidth, height);
    break;
  }

  // Similar to the Horizontal Three Rectangle, where we calculate the total section
  // into thirds indicated by thirdHeight.
  case VerticalThreeRectangle: {
    thirdHeight = height / 3;

        // In this case, we sum the top and bottom parts of the section together (light pixels)
        // and the middle section of the section together (dark pixels)
    sumRegion1 = sumRegion(integralData, x, y, width, thirdHeight)
      + sumRegion(integralData, x, y + 2 * thirdHeight, width, height - 2 * thirdHeight);
    sumRegion2 = sumRegion(integralData, x, y + thirdHeight, width, thirdHeight);
    break;
  }

  // For the FourRectangle case, our sections are separated into a grid-like formation
  // so we indicate these sections through new ints called halfWidth and halfHeight
  case FourRectangle: {
    int halfWidth = width / 2;
    int halfHeight = height / 2;

        // The sum of the light pixel region are the indicated by the light pixelated corners of the grid
        // used by adding the halfWidths and halfHeights to the original X and Y coordinates
    sumRegion1 = sumRegion(integralData, x, y, halfWidth, halfHeight)
      + sumRegion(integralData, x + halfWidth, y + halfHeight, width - halfWidth, height - halfHeight);

        // Similar to the addition of light pixel region, the dark pixel region takes the opposite corners of the grid
        // and adds them together.
    sumRegion2 = sumRegion(integralData, x + halfWidth, y, width - halfWidth, halfHeight)
      + sumRegion(integralData, x, y + halfHeight, halfWidth, height - halfHeight);
    break;
  }
  default:
    std::cerr << "Unsupported feature type." << std::endl;
    return 0;
  }

  // Sanity check to see if our code runs correctly
  if (0){//sumRegion2 == 0 && sumRegion1 == 0) {
       printf("integral data: \n");
    for (const auto& row : integralData) {
      for (int val : row) {
        std::cout << val << " ";
      }
      std::cout << std::endl;
    }
    printf("feature eval: sumRegion 2 = %d, sumRegion1 = %d, contrast = %d\n", sumRegion2, sumRegion1, sumRegion2 - sumRegion1);

  }

  // We return our subtraction of light pixel region by the dark pixel region,
  // so we can use the data to figure out if the sub-window we have in the integral image is usable

  return sumRegion2 - sumRegion1;

}

// Function builds all of the viable Haar-Features of our pixelated images
std::vector<tuple<FeatureUtil::FeatureType, int, int, int, int>> FeatureUtil::generateFeatureConfigs(int base_res) {

  // Initialize an area to store all of our Haar-Features called "featureConfigs"
  std::vector<tuple<FeatureType, int, int, int, int>> featureConfigs;

  // We start by setting some ground variables that most of our Haar-Features must cover such as
  // the minimum width and height, in addition to how big the Haar-Feature can get
  int base_resolution = base_res;
  int minWidth = 1;
  int minHeight = 1;
  int stepWidth = 1;
  int stepHeight = 1;
std::unordered_set<std::string> featureSet;

  // We go through each of the 5 different types of Haar-Features,
  // as each one of them follows a specific step/trend that we must follow in order to create that specific Haar-Feature
  for (int type = 0; type < 5; type++) {

        // Using a switch function, we go through the basic fundamentals of each Haar-Feature
    switch (type) {

        // For the HorizontalTwoRectangle class, the Haar-Feature must be at least
        // an even number in width and an odd number in height, thus our stepWidth = 2 and stepHeight = 1, respectively
    case HorizontalTwoRectangle:
      minWidth = 2;
      minHeight = 1;
      stepWidth = 2;
      stepHeight = 1;
      break;

        // For the VerticalTwoRectangle class, it is nearly identical to the HorizontalTwoRectangle class,
        // except that the width must be an odd number and the height must be an even number and our step sizes switch, respectively
    case VerticalTwoRectangle:
      minWidth = 1;
      minHeight = 2;
      stepWidth = 1;
      stepHeight = 2;
      break;

        // For the HorizontalThreeRectangle class, the Haar-Feature must be at least
        // a multiple of 3 in width, and any number can satisfy the height qualifications
        // thus our stepWidth = 3, and our stepHeight = 1
    case HorizontalThreeRectangle:
      minWidth = 3;
      minHeight = 1;
      stepWidth = 3;
      stepHeight = 1;
      break;

        // For the VerticalThreeRectangle class, it is nearly identical to the HorizontalThreeRectangle class,
        // just the height and width are swapped around; height must be a multiple of 3 versus the width can be any number
        // stepWidth = 1, stepHeight = 3
    case VerticalThreeRectangle:
      minWidth = 1;
      minHeight = 3;
      stepWidth = 1;
      stepHeight = 3;
      break;

        // For the FourRectangle class, the Haar-Feature must be at least
        // an even number for both width and height qualifications of our Haar-Feature
        // meaning that the stepHeight and stepWidth = 2
    case FourRectangle:
      minWidth = 2;
      minHeight = 2;
      stepWidth = 2;
      stepHeight = 2;
      break;

    default:
      minWidth = 1;
      minHeight = 1;
    }

        // this for loop goes through all of the different possible Haar-Features that can be created from the base resolution
        // this code is extremely long as it generates roughly 160,000 different kinds of features for each image
    for (int height = minHeight; height <= base_resolution; height += stepHeight) {
      for (int width = minWidth; width <= base_resolution; width += stepWidth) {
        for (int y = 0; y <= base_resolution - height; y++) {
          for (int x = 0; x <= base_resolution - width; x++) {

                // We place the specific feature into our storage variable
            featureConfigs.emplace_back(std::make_tuple(static_cast<FeatureUtil::FeatureType>(type),
                                                          x, y, width, height));

          }
        }
      }
    }
  }

  // Input the total number of Haar-Features into the feature size variable and return all of our Haar-Features for usage

  featureSize = featureConfigs.size();
  return featureConfigs;
}

// This function evaluates the "contrast" of the many different Haar-Features
// depending on the sample image inputted into this function
std::vector<float> FeatureUtil::generateFeatureEvaluations(std::vector<std::vector<int>>& integralData,
                                std::vector<tuple<FeatureUtil::FeatureType, int, int, int, int>> featureConfigs) {
  int counter = 0;
  // Initialize a storage variable for our function
  std::vector<float> featureEvaluations;

  // For all the different Haar-Features that are possible within our sample image
  for(const auto& featureConfig: featureConfigs) {
    if (counter % 1000 == 0) {
      // We initialize the values needed to calculate our features depending on our sample image
      FeatureUtil::FeatureType type;
      int x, y, width, height;
        // Matches the featureConfigurations input by the user, to the specific qualifications that we need to calculate our Haar-Feature
      std::tie(type, x, y, width, height) = featureConfig;
        // Calculate the "contrast" of our feature in comparison to our sample image
      float evaluation = evaluateFeature(integralData,
                                             type,
                                             x, y,
                                             width,
                                             height);

      // Stores the evaluations of each different Haar-Feature into the featureEvaluations vector

      featureEvaluations.emplace_back(evaluation);
    }

  }

  // Return our featureEvaluations to be inputted into our image data
  return featureEvaluations;
}



void FeatureUtil::writeFeatureData(const std::string& filename, const std::vector<FeatureData>& data) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Cannot open file for writing.");
    }

    for (const auto& fd : data) {
        // Write label and weight
        outFile.write(reinterpret_cast<const char*>(&fd.label), sizeof(fd.label));
        outFile.write(reinterpret_cast<const char*>(&fd.weight), sizeof(fd.weight));

        // Write originalData
        size_t size = fd.originalData.size();
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        outFile.write(reinterpret_cast<const char*>(fd.originalData.data()), size * sizeof(uint8_t));

        // Write featureEvaluations
        size = fd.featureEvaluations.size();
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        outFile.write(reinterpret_cast<const char*>(fd.featureEvaluations.data()), size * sizeof(float));

        // Write integralData
        size = fd.integralData.size();
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& row : fd.integralData) {
            size_t rowSize = row.size();
            outFile.write(reinterpret_cast<const char*>(&rowSize), sizeof(rowSize));
            outFile.write(reinterpret_cast<const char*>(row.data()), rowSize * sizeof(int));
        }
    }
    outFile.close();
}

 void FeatureUtil::writeFeatureData2(const std::string& baseFilename, const std::vector<FeatureData>& data) {
        // 3 GB limit, calculated as 3 * 1024 * 1024 * 1024
        const size_t maxTotalSize = static_cast<size_t>(3) * 1024 * 1024 * 1024; 
        const size_t maxChunkSize = 400 * 1024 * 1024; // 400 MB chunk limit

        size_t currentFileSize = 0;
        size_t totalWrittenSize = 0;
        size_t fileIndex = 0;

        // Generate the initial filename
        std::string currentFilename = baseFilename + "_" + std::to_string(fileIndex) + ".bin";
        std::ofstream outFile;

        // Open the first file
        outFile.open(currentFilename, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Cannot open file for writing.");
        }

        for (const auto& fd : data) {
            // Calculate the size of the data to be written
            size_t dataSize = sizeof(fd.label) + sizeof(fd.weight);
            dataSize += sizeof(size_t) + fd.originalData.size() * sizeof(uint8_t);
            dataSize += sizeof(size_t) + fd.featureEvaluations.size() * sizeof(float);

            dataSize += sizeof(size_t); // Size for integral data
            for (const auto& row : fd.integralData) {
                dataSize += sizeof(size_t) + row.size() * sizeof(int);
            }

            // If adding this data exceeds chunk size or total limit
            if (currentFileSize + dataSize > maxChunkSize || totalWrittenSize + dataSize > maxTotalSize) {
                // If exceeding total limit, stop writing
                if (totalWrittenSize + dataSize > maxTotalSize) {
                    break;
                }

                // Otherwise, create a new chunk
                outFile.close();
                currentFileSize = 0;
                fileIndex++;
                currentFilename = baseFilename + "_" + std::to_string(fileIndex) + ".bin";
                outFile.open(currentFilename, std::ios::binary);
                if (!outFile) {
                    throw std::runtime_error("Cannot open new chunk file for writing.");
                }
            }

            // Write data
            outFile.write(reinterpret_cast<const char*>(&fd.label), sizeof(fd.label));
            outFile.write(reinterpret_cast<const char*>(&fd.weight), sizeof(fd.weight));

            // Write originalData
            size_t size = fd.originalData.size();
            outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            outFile.write(reinterpret_cast<const char*>(fd.originalData.data()), size * sizeof(uint8_t));

            // Write featureEvaluations
            size = fd.featureEvaluations.size();
            outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            outFile.write(reinterpret_cast<const char*>(fd.featureEvaluations.data()), size * sizeof(float));

            // Write integralData
            size = fd.integralData.size();
            outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            for (const auto& row : fd.integralData) {
                size_t rowSize = row.size();
                outFile.write(reinterpret_cast<const char*>(&rowSize), sizeof(rowSize));
                outFile.write(reinterpret_cast<const char*>(row.data()), rowSize * sizeof(int));
            }

            // Update file size and total size written
            currentFileSize += dataSize;
            totalWrittenSize += dataSize;
        }

        // Close the final file
        outFile.close();
    }

  void FeatureUtil::readFeatureData(const std::string& filename, std::vector<FeatureData>& data) {
      std::ifstream inFile(filename, std::ios::binary);
      if (!inFile) {
          throw std::runtime_error("Cannot open file for reading.");
      }

      while (!inFile.eof()) {
          FeatureData fd;

          // Read label and weight
          inFile.read(reinterpret_cast<char*>(&fd.label), sizeof(fd.label));
          inFile.read(reinterpret_cast<char*>(&fd.weight), sizeof(fd.weight));
          if (inFile.fail()) {
              break;
          }

          // Read originalData
          size_t size;
          inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
          fd.originalData.resize(size);
          inFile.read(reinterpret_cast<char*>(fd.originalData.data()), size * sizeof(uint8_t));

          // Read featureEvaluations
          inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
          fd.featureEvaluations.resize(size);
          inFile.read(reinterpret_cast<char*>(fd.featureEvaluations.data()), size * sizeof(float));

          // Read integralData
          inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
          fd.integralData.resize(size);
          for (auto& row : fd.integralData) {
              size_t rowSize;
              inFile.read(reinterpret_cast<char*>(&rowSize), sizeof(rowSize));
              row.resize(rowSize);
              inFile.read(reinterpret_cast<char*>(row.data()), rowSize * sizeof(int));
          }

          data.push_back(fd);
      }

      inFile.close();
}
