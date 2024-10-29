#include "adaBoost.h"

adaBoostManager::adaBoostManager(){}

void adaBoostManager::initImageData(char* featureDataPath, 
                                    char* positiveDir, 
                                    char* negativeDir, 
                                    int baseWidth, 
                                    int baseHeight) {
  allImageData.clear();
  ProcImages imgs;

  FeatureUtil features(baseWidth, baseHeight);
  imgs.imageDataProc(positiveDir, negativeDir, baseWidth, baseHeight);
  features.readFeatureData(featureDataPath, allImageData);
  //allImageData = features.generateFeatureConfigs(imgs.getExamples(), imgs.getLabels());
  splitData(trainingD, testingD);
  featureSize = allImageData[0].featureEvaluations.size();
}


std::vector<WeakClassifier> adaBoostManager::adaBoost(std::vector<FeatureUtil::FeatureData>& imageData, 
                                                      int boostRounds, 
                                                      int featureIncrement) {
    initializeWeights(imageData);
    normalizeWeights(imageData);
    std::vector<WeakClassifier> classifiers;
    for (int rounds = 0; rounds < boostRounds; rounds++) {
      printf("   -> boosting round %d of %d\n", rounds + 1, boostRounds);
      float error = 0;
      WeakClassifier bestClassifier = selectBestClassifier(imageData, featureIncrement);
      error = bestClassifier.getError();
      float beta = (error / 1.0 - error);
      float alpha = log(1.0 / beta);
      bestClassifier.setBeta(beta);
      bestClassifier.setAlpha(alpha);
      updateWeights(imageData, bestClassifier);
      classifiers.push_back(bestClassifier);
    }
    usedFeatures.clear();
    return classifiers;
}

WeakClassifier adaBoostManager::selectBestClassifier(std::vector<FeatureUtil::FeatureData>& imageData, 
                                                     int featureIncrement) {
    int imageDataSize = imageData.size();
    float weight, error, posError, negError, threshold;
    int polarity = 0;
    float posWeightTotal = 0;
    float negWeightTotal = 0;
    int posCount = 0;
    int negCount = 0;

    float cyclePosWeightTotal = 0;
    float cycleNegWeightTotal = 0;
    int cyclePosCount = 0;
    int cycleNegCount = 0;
    vector<float> errors;
    vector<int> predictLabels;
    vector<int> errorCounts;
    WeakClassifier bestClassifier;

    for (auto& example : imageData) {
      if (example.label == 1) {
        posWeightTotal += example.weight;
        posCount ++;
      } else {
        negWeightTotal += example.weight;
        negCount ++;
      }
      //printf("%d, %f, %f\n", example.label,posWeightTotal, negWeightTotal);
    }
 
    // Loop through each feature to evaluate as a potential classifier
    for (int featureIndex = 0; featureIndex < featureSize; featureIndex++) {
      if (featureIndex % featureIncrement == 0) {
        int cycle = 0;
        // skips feature if already a classifier
        if (usedFeatures.find(featureIndex) != usedFeatures.end()) {
          continue;
        }

        // Sorte image data by feature
        sortByFeature(imageData, featureIndex);

        error = 0;
        predictLabels.clear();
        errors.clear();
        cyclePosWeightTotal = 0;
        cycleNegWeightTotal = 0;

        // Iterate over all images and calculate errors for classifier at each cycle
        for (auto& example : imageData) {
          weight = example.weight;
          if(example.label == FACE) {
            cyclePosWeightTotal += weight;

          } else {
            cycleNegWeightTotal += weight;
          }
           
          // posError is the total error when the current data is considered the boundry and everything to the left is a face.
          posError = cyclePosWeightTotal + (negWeightTotal - cycleNegWeightTotal);
          // negErro is the total error when the current data is considered the boundry and everything to the left is not a face.
          negError = cycleNegWeightTotal + (posWeightTotal - cyclePosWeightTotal);

          // If posError > negError then everything to the left of threshold is negative and
          if (posError > negError) {
            errors.push_back(negError);
            // Data points to the right of Threshold is a face;
            predictLabels.push_back(FACE);
            polarity = -1;
          } else {
            errors.push_back(posError);
            // Data points to the right of the threshold is Not a Face.
            predictLabels.push_back(NOT_FACE);
            polarity = 1;
          }
       
          // Find the minium error for the current feature and its index
          std::vector<float>::iterator result = std::min_element(errors.begin(), errors.end());
          int index = std::distance(errors.begin(), result);
          error = *result;
          //printf("error %f\n", error);
          //printf("poserror %f negerror %f\n", posError, negError);
          if (error < bestClassifier.getError()) {
            bestClassifier.setError(error);
            bestClassifier.setFeatureIndex(featureIndex);
            bestClassifier.setThreshold(imageData[index].featureEvaluations[featureIndex]);
            bestClassifier.setPolarity(polarity);
            bestClassifier.setLabel(predictLabels[index]);
          }
          cycle ++;
        }
      }
    }
    
    usedFeatures.insert(bestClassifier.getFeatureIndex());
    bestClassifier.print();
    return bestClassifier;
}

void adaBoostManager::sortByFeature(std::vector<FeatureUtil::FeatureData>& imageData, 
                                    int featureIndex) {
  std::sort(imageData.begin(), imageData.end(),
            [featureIndex](FeatureUtil::FeatureData& a, FeatureUtil::FeatureData& b) {
              if (featureIndex < a.featureEvaluations.size() &&
                  featureIndex < b.featureEvaluations.size()) {
                return a.featureEvaluations[featureIndex] < b.featureEvaluations[featureIndex];
              }
              return false;
            });
}

void adaBoostManager::initializeWeights(std::vector<FeatureUtil::FeatureData>& imageData) {
  int negCount = std::count_if(imageData.begin(), imageData.end(), [](auto& data) {
    return data.label == -1;
  });
  int posCount = imageData.size() - negCount;

  for (auto& example : imageData) {
    example.weight = example.label == -1 ? 1.0 / (2 * negCount) : 1.0 / (2 * posCount);
  }
}

void adaBoostManager::normalizeWeights(std::vector<FeatureUtil::FeatureData>& imageData) {
  float sum = std::accumulate(imageData.begin(), imageData.end(), 0.0f,
                              [](float acc, FeatureUtil::FeatureData example) {
                                return acc + example.weight;
                              });
    for (auto& example : imageData) {
        example.weight /= sum;
    }
}

void adaBoostManager::updateWeights(std::vector<FeatureUtil::FeatureData>& imageData, 
                                    WeakClassifier classifier) {
  float error = classifier.getError();
  float beta = error / (1 - error);
  for(auto& example : imageData) {
    int correct = classifier.predict(example);
    float exponent = 1 - correct;
    example.weight *= std::pow(static_cast<double>(beta), static_cast<double>(exponent));
  }
}

std::vector<FeatureUtil::FeatureData>& adaBoostManager::getAllImageData() {
  return allImageData;
}

std::vector<FeatureUtil::FeatureData>& adaBoostManager::getTestingData() {
  return testingD;
}

std::vector<FeatureUtil::FeatureData>& adaBoostManager::getTrainingData() {
  return trainingD;
}

void adaBoostManager::splitData(std::vector<FeatureUtil::FeatureData>& trainingData,
                                 std::vector<FeatureUtil::FeatureData>& testingData) {

    std::vector<FeatureUtil::FeatureData> firstHalf;
    std::vector<FeatureUtil::FeatureData> secondHalf;

    // Calculate the total size and the midpoint
    std::size_t totalSize = allImageData.size();
    std::size_t midPoint = totalSize / 2;

    // Clear the new vectors to ensure there's no residual data
    firstHalf.clear();
    secondHalf.clear();

    // Assign the first half of allImageData to firstHalf
    firstHalf.assign(allImageData.begin(), allImageData.begin() + midPoint);

    // Assign the second half of allImageData to secondHalf
    secondHalf.assign(allImageData.begin() + midPoint, allImageData.end());

    // Calculate the midpoint of each half
    std::size_t firstHalfMidPoint = firstHalf.size() / 2;
    std::size_t secondHalfMidPoint = secondHalf.size() / 2;
      // Insert the first half of firstHalf into trainingData
    trainingData.insert(trainingData.end(), firstHalf.begin(), firstHalf.begin() + firstHalfMidPoint);

    // Insert the first half of secondHalf into trainingData
    trainingData.insert(trainingData.end(), secondHalf.begin(), secondHalf.begin() + secondHalfMidPoint);

    // Assign the rest to testingData
    testingData.clear();
    testingData.insert(testingData.end(), firstHalf.begin() + firstHalfMidPoint, firstHalf.end());
    testingData.insert(testingData.end(), secondHalf.begin() + secondHalfMidPoint, secondHalf.end());

}
