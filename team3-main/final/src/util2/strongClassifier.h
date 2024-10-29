#ifndef STRONGCLASSIFIER_H
#define STRONGCLASSIFIER_H

#include <vector>
#include "weakClassifier.h"
#include "featureUtil.h"


class StrongClassifier {
public:
    StrongClassifier(); 
    int predict(std::vector<std::vector<int>>& integralData, 
                std::vector<tuple<FeatureUtil::FeatureType, int, int, int, int>>& featureConfig);
    void setClassifiers(std::vector<WeakClassifier> classifiers);
    std::vector<WeakClassifier>& getClassifiers();
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
    void setDR(float dr);
    void setFPR(float fpr);
    float getDR();
    float getFPR();

private:
    std::vector<WeakClassifier> weakClassifiers;
    float dr;
    float fpr;
};

#endif 

