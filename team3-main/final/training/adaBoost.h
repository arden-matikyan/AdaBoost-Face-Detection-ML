#ifndef ADABOOST_H
#define ADABOOST_H
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>
#include <vector>
#include <set>
#include "featureUtil.h"
#include "procImages.h"
#include "weakClassifier.h"
#include "strongClassifier.h"

#define FACE 1
#define NOT_FACE -1

class adaBoostManager {
public:

  adaBoostManager();
  void initializeWeights(std::vector<FeatureUtil::FeatureData>& imageData);
  void initImageData(char* featureDataPath, char* positiveDir, char* negativeDir, int baseWidht, int baseHeight);
  std::vector<WeakClassifier> adaBoost(std::vector<FeatureUtil::FeatureData>& imageData, int rounds, int featureIncrement);
  WeakClassifier selectBestClassifier(std::vector<FeatureUtil::FeatureData>& imageData, int featureIncrement);
  void normalizeWeights(std::vector<FeatureUtil::FeatureData>& imageData);
  void sortByFeature(std::vector<FeatureUtil::FeatureData>& imageData, int j);
  void updateWeights(std::vector<FeatureUtil::FeatureData>& imagedata, WeakClassifier classifier);
  void splitData(std::vector<FeatureUtil::FeatureData>& trainingData,
                 std::vector<FeatureUtil::FeatureData>& testingData);
  std::vector<FeatureUtil::FeatureData>& getAllImageData();
  std::vector<FeatureUtil::FeatureData>& getTestingData();
  std::vector<FeatureUtil::FeatureData>& getTrainingData();

private:
  int featureSize;
  std::vector<FeatureUtil::FeatureData> allImageData;
  std::vector<FeatureUtil::FeatureData> trainingD;
  std::vector<FeatureUtil::FeatureData> testingD;
  std::set<int> usedFeatures;
};

#endif
