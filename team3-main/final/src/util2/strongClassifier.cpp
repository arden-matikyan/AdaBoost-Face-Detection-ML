#include "strongClassifier.h"

StrongClassifier::StrongClassifier() {}

int StrongClassifier::predict(std::vector<std::vector<int>>& integralData, 
                              std::vector<tuple<FeatureUtil::FeatureType, int, int, int, int>>& featureConfig) {
      /*                        
     cout<<"In Strong classifier: Integral DATA: "<<endl;
    
            std::cout << "2D Vector:" << std::endl;
            for (const auto& row : integralData) {
            for (int element : row) {
                std::cout << element << " ";
              }
            std::cout << std::endl;
            }
                                  
       */                       
                                             
    float alphaSum = 0;
    float weightedSum = 0;
    for (auto& classifier : weakClassifiers) {
    
        alphaSum += classifier.getAlpha();
        // cout << " alpha: " << classifier.getAlpha() << " predict: " << classifier.predict(integralData, featureConfig) << endl; 
        weightedSum += classifier.getAlpha() * classifier.predict(integralData, featureConfig);
    }
    if (weightedSum >= 0.5 * alphaSum) {
        // cout<<"Weighted Sum : " << weightedSum << " >= " << 0.5 * alphaSum << " 0.5 * alphaSum " << endl; 
        return 1; 
    } else {
        return 0;
    }
}

void StrongClassifier::serialize(std::ostream& os) const{
    size_t numWeakClassifiers = weakClassifiers.size();
    os.write(reinterpret_cast<const char*>(&numWeakClassifiers), sizeof(numWeakClassifiers));
    for (const auto& classifier : weakClassifiers) {
        classifier.serialize(os);
    }
    os.write(reinterpret_cast<const char*>(&dr), sizeof(dr));
    os.write(reinterpret_cast<const char*>(&fpr), sizeof(fpr));
}

void StrongClassifier::deserialize(std::istream& is) {
    size_t numWeakClassifiers;
    is.read(reinterpret_cast<char*>(&numWeakClassifiers), sizeof(numWeakClassifiers));
    weakClassifiers.resize(numWeakClassifiers);
    for (auto& classifier : weakClassifiers) {
        classifier.deserialize(is);
    }
    is.read(reinterpret_cast<char*>(&dr), sizeof(dr));
    is.read(reinterpret_cast<char*>(&fpr), sizeof(fpr));
}

void StrongClassifier::setClassifiers(std::vector<WeakClassifier> classifiers){
    weakClassifiers = classifiers;
}

std::vector<WeakClassifier>& StrongClassifier::getClassifiers() {
    return weakClassifiers;
}