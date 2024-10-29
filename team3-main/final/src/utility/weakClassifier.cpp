#include "weakClassifier.h"

WeakClassifier::WeakClassifier(){}

int WeakClassifier::predict(FeatureUtil::FeatureData example) {
  if (polarity == 1) {
    return example.featureEvaluations[featureIndex] >= threshold ? 1 : 0;
  } else {
    return example.featureEvaluations[featureIndex] < threshold ? 1 : 0;
  }
}
/*
int WeakClassifier::predict(FeatureUtil::FeatureData example) {
  int classification;
  
  if (polarity == 1) {
    // Classify feature values >= threshold as positive, < threshold as negative
    classification = example.featureEvaluations[featureIndex] >= threshold ? 1 : 0;
  } else {
    // Classify feature values < threshold as positive, >= threshold as negative
    classification = example.featureEvaluations[featureIndex] < threshold ? 1 : 0;
  }

  // Adjust the classification according to the expected label
  // If label is -1, we invert the classification
  return (label == -1) ? classification : -classification;
}
*/
void WeakClassifier::print() {
    printf("   --> weak classifier error = %f\n", getError());
    printf("   --> weak classifier feature index = %d\n", getFeatureIndex());
    printf("   --> weak classifier threshold = %d\n", getThreshold());
    printf("   --> weak classifier polarity = %d\n", getPolarity());
    printf("   --> weak classifier error count = %d\n", getErrorCount());
    printf("   --> weak classifier label = %d\n\n", getLabel());
}


void WeakClassifier::serialize(std::ostream& os) const{
    os.write(reinterpret_cast<const char*>(&error), sizeof(error));
    os.write(reinterpret_cast<const char*>(&featureIndex), sizeof(featureIndex));
    os.write(reinterpret_cast<const char*>(&threshold), sizeof(threshold));
    os.write(reinterpret_cast<const char*>(&polarity), sizeof(polarity));
    os.write(reinterpret_cast<const char*>(&errorCount), sizeof(errorCount));
    os.write(reinterpret_cast<const char*>(&label), sizeof(label));
}

void WeakClassifier::deserialize(std::istream& is) {
    is.read(reinterpret_cast<char*>(&error), sizeof(error));
    is.read(reinterpret_cast<char*>(&featureIndex), sizeof(featureIndex));
    is.read(reinterpret_cast<char*>(&threshold), sizeof(threshold));
    is.read(reinterpret_cast<char*>(&polarity), sizeof(polarity));
    is.read(reinterpret_cast<char*>(&errorCount), sizeof(errorCount));
    is.read(reinterpret_cast<char*>(&label), sizeof(label));
}

void WeakClassifier::setFeatureIndex(int featIndex) {
  featureIndex = featIndex;
}

void WeakClassifier::setError(float e) {
  error = e;
}

void WeakClassifier::setThreshold(int thresh) {
  threshold = thresh;
}

void WeakClassifier::setPolarity(int pol) {
  polarity = pol;
}

void WeakClassifier::setErrorCount(int eCount) {
  errorCount = eCount;
}

void WeakClassifier::setLabel(int lab) {
  label = lab;
}

void WeakClassifier::setAlpha(float a) {
  alpha = a;
}


void WeakClassifier::setBeta(float b) {
  beta = b;
}

int WeakClassifier::getFeatureIndex() {
  return featureIndex;
}

float WeakClassifier::getError() {
  return error;
}

int WeakClassifier::getThreshold() {
  return threshold;
}

int WeakClassifier::getPolarity() {
  return polarity;
}

int WeakClassifier::getErrorCount() {
  return errorCount;
}

int WeakClassifier::getLabel() {
  return label;
}

float WeakClassifier::getAlpha() {
  return alpha;
}

float WeakClassifier::getBeta() {
  return beta;
}

