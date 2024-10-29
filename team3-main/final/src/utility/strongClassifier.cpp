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

void StrongClassifier::setDR(float DR){
    dr = DR;
}

void StrongClassifier::setFPR(float FPR){
    fpr = FPR;
}

float StrongClassifier::getDR(){
    return dr;
}

float StrongClassifier::getFPR(){
    return fpr;
}