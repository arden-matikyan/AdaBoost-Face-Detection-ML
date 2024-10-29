#ifndef STRONGCLASSIFIER_H
#define STRONGCLASSIFIER_H

#include <vector>
#include "weakClassifier.h"
#include "featureUtil.h"


class StrongClassifier {
public:
    StrongClassifier(); 
    int predict(FeatureUtil::FeatureData& example);
    void setClassifiers(std::vector<WeakClassifier> classifiers);
    std::vector<WeakClassifier>& getClassifiers();

private:
    std::vector<WeakClassifier> weakClassifiers;
};

#endif 

