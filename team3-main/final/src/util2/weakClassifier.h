#ifndef WEAKCLASSIFIER_H
#define WEAKCLASSIFIER_H
#include <tuple>
#include <vector>
#include <limits>
#include "featureUtil.h"


class WeakClassifier {
public:
  struct Example {
    std::vector<uint8_t> imageData;
    std::vector<float> features;
  };

  WeakClassifier();
  int predict(std::vector<std::vector<int>>& integralData, 
              std::vector<tuple<FeatureUtil::FeatureType, int, int, int, int>>& featureConfig);
  void setFeatureIndex(int featIndex);
  void print();
  void setError(float e);
  void setThreshold(int thresh);
  void setPolarity(int pol);
  void setErrorCount(int eCount);
  void setLabel(int lab);
  void setAlpha(float alpha);
  void setBeta(float beta);
  void serialize(std::ostream& os) const;
  void deserialize(std::istream& is);
  int getFeatureIndex();
  float getError();
  int getThreshold();
  int getPolarity();
  int getErrorCount();
  int getLabel();
  float getAlpha();
  float getBeta();

private:
  int featureIndex = 0;
  float error = std::numeric_limits<float>::max();
  float threshold = 0;
  float alpha = 0;
  float beta = 0;
  int polarity = 0;
  int errorCount = 0;
  int label = 0;
};


#endif
