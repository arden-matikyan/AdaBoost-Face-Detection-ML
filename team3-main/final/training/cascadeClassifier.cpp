#include "cascadeClassifier.h"

CascadeClassifier::CascadeClassifier(char* featureDataPath, 
                                     char* positiveDir, 
                                     char* negativeDir, 
                                     int width, 
                                     int height) {

    adaBoost.initImageData(featureDataPath, positiveDir, negativeDir, width, height);
}

void CascadeClassifier::trainCascade(int stages, int adaboostRounds, int featureInc, float desiredFPR, float desiredDR) {
    int boostingRounds = adaboostRounds, featureIncrement = featureInc;
    std::vector<FeatureUtil::FeatureData> trainingData = adaBoost.getTrainingData();
    std::vector<FeatureUtil::FeatureData>& testData = adaBoost.getTestingData();
    int truePos = 0.5 * trainingData.size();
    int trueNeg = 0.5 * trainingData.size();
    std::pair<float, float> metrics;
    for (int stage = 0; stage < stages; ++stage) {
        printf("Training stage %d of %d\n", stage + 1, stages);
        printf("truePos = %d, trueNeg = %d\n", truePos, trueNeg);
        StrongClassifier strongClassifier;
        
        // Strong classifier vector is here.
        strongClassifier.setClassifiers(adaBoost.adaBoost(trainingData, boostingRounds, featureIncrement));
        strongClassifiers.push_back(strongClassifier);

        // Calculate the current DR and FPR.
        printf("Calculating DR and FPR\n");
        metrics = calculateMetrics(testData, stage);
        float currentFPR = metrics.second;
        float currentDR = metrics.first;

        // If DR and FPR are good then stop.
        printf("[Current FPR: %.2f, Desired FPR: %.2f, Current DR: %.2f, Desired DR: %.2f]\n\n\n", currentFPR, desiredFPR, currentDR, desiredDR);
        if (currentFPR <= desiredFPR && currentDR >= desiredDR) {
            printf("Desired criteria met, stopping cascade training.\n");
            break; 
        }
        
        // Clear current traning data and set up new training data for next stage
        printf("Setting up new training data\n");
        truePos = trueNeg = 0;
        std::vector<FeatureUtil::FeatureData> temp = adaBoost.getTrainingData();
        trainingData.clear();
        for (auto& data : temp) {
            if (classify(data, stage) == 1) {  
                if (data.label == 1) {
                    truePos ++;
                } else {
                    trueNeg ++;
                }
                trainingData.push_back(data); 
            }
        }
        temp.clear();
        boostingRounds += ((stage + 1)*2);
    }
}

int CascadeClassifier::classify(FeatureUtil::FeatureData data, int stage) {
    //printf("size of weak classfiiers %ld\n", strongClassifiers[stage].getClassifiers().size());
    if (strongClassifiers[stage].predict(data) == 0) { 
        return 0;  
    }
    return 1; 
}

std::pair<float, float> CascadeClassifier::calculateMetrics(std::vector<FeatureUtil::FeatureData> testData, int stage) {
    int truePositives = 0;
    int falseNegatives = 0;
    int falsePositives = 0;
    int trueNegatives = 0;
    for (auto& data : testData) { 
        int prediction = classify(data, stage);
        if (data.label == 1) { 
            if (prediction == 1) {
                truePositives++;
            } else {
                falseNegatives++;
            }
        } else { 
            if (prediction == 1) {
                falsePositives++;
            } else {
                trueNegatives++;
            }
        }
    }
    printf("true positives = %d, true negatives = %d, false positives = %d, false negatives = %d\n", truePositives, trueNegatives, falsePositives, falseNegatives);
    printf("Total test data size = %lu\n", testData.size());
 
    float detectionRate = (truePositives + falseNegatives) == 0 ? 0 : static_cast<float>(truePositives) / (truePositives + falseNegatives);
    float falsePositiveRate = (falsePositives + trueNegatives) == 0 ? 0 : static_cast<float>(falsePositives) / (falsePositives + trueNegatives);
    return std::make_pair(detectionRate, falsePositiveRate);
}

/*
std::pair<float, float> CascadeClassifier::calculateMetrics(std::vector<FeatureUtil::FeatureData> testData, int stage) {
    int truePositives = 0;
    int falseNegatives = 0;
    int falsePositives = 0;
    int trueNegatives = 0;

    for (auto& data : testData) {
        int prediction = 1; 
        // pass the data through each of the stages if it passes at a face then its good to go if no then discard it.
        for (int s = 0; s <= stage; s++) { 
            if (classify(data, s) == 0) {
                prediction = 0; 
                break;
            }
        }
        // Test the prediction with the true value of the image.
        if (data.label == 1) {
            if (prediction == 1) {
                truePositives++;
            } else {
                falseNegatives++;
            }
        } else {
            if (prediction == 1) {
                falsePositives++;
            } else {
                trueNegatives++;
            }
        }
    }

    printf("true positives = %d, true negatives = %d, false positives = %d, false negatives = %d\n", truePositives, trueNegatives, falsePositives, falseNegatives);
    float detectionRate = (truePositives + falseNegatives) == 0 ? 0 : static_cast<float>(truePositives) / (truePositives + falseNegatives);
    
    float falsePositiveRate = (falsePositives + trueNegatives) == 0 ? 0 : static_cast<float>(falsePositives) / (falsePositives + trueNegatives);

    return std::make_pair(detectionRate, falsePositiveRate);
}
*/