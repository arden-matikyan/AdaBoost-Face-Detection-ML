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
    void setDR(float dr);
    void setFPR(float fpr);
    float getDR();
    float getFPR();
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);

private:
    std::vector<WeakClassifier> weakClassifiers;
    float dr;
    float fpr;
};

#endif 

