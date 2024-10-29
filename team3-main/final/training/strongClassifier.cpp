#include "strongClassifier.h"

StrongClassifier::StrongClassifier() {}

int StrongClassifier::predict(FeatureUtil::FeatureData& example) {
    float alphaSum = 0;
    float weightedSum = 0;

    for (auto& classifier : weakClassifiers) {
        alphaSum += classifier.getAlpha();
        weightedSum += classifier.getAlpha() * classifier.predict(example);
    }
    if (weightedSum >= 0.5 * alphaSum) {
        return 1; 
    } else {
        return 0;
    }
}

void StrongClassifier::setClassifiers(std::vector<WeakClassifier> classifiers){
    weakClassifiers = classifiers;
}

std::vector<WeakClassifier>& StrongClassifier::getClassifiers() {
    return weakClassifiers;
}