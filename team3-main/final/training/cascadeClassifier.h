#ifndef CASCADECLASSIFIER_H
#define CASCADECLASSIFIER_H

#include <vector>
#include "adaBoost.h"
#include "featureUtil.h"
#include "weakClassifier.h"
#include "strongClassifier.h"

class CascadeClassifier {
public:
    CascadeClassifier(char* featureDataPath, 
                      char* positiveDir, 
                      char* negativeDir, 
                      int baseWidht, 
                      int baseHeight); 

    void trainCascade(int stages, int boostRounds, int featureInc, float desiredFPR, float desiredDR);
    int classify(FeatureUtil::FeatureData data, int stage);
    std::pair<float, float> calculateMetrics(std::vector<FeatureUtil::FeatureData> testData, int stage);

private:
    adaBoostManager adaBoost;
    std::vector<StrongClassifier> strongClassifiers;
};

#endif 
