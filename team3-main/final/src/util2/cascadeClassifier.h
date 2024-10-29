#ifndef CASCADECLASSIFIER_H
#define CASCADECLASSIFIER_H

#include <vector>
#include "featureUtil.h"
#include "weakClassifier.h"
#include "strongClassifier.h"

class CascadeClassifier {
public:
    CascadeClassifier(); 

    std::vector<StrongClassifier> loadStrongClassifiers(const char* filename);
    void saveStrongClassifiers(const char* filename);

private:
    std::vector<StrongClassifier> strongClassifiers;
};

#endif 
