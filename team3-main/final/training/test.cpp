
#include "cascadeClassifier.h"


int main(int argc, char* argv[]) {
    char* positiveDir = "/home/rkoepke/final/good";
    char* negativeDir = "/home/rkoepke/final/bad";
    int width = 24, height = width, stages = 5, boostRounds = 5, featureIncrements = 1000;
      if (argc > 1) {
        if (argc >= 2) {
            stages = std::atoi(argv[1]); 
        }
        if (argc >= 3) {
            boostRounds = std::atoi(argv[2]);
        }
        if (argc >= 4) {
            featureIncrements = std::atoi(argv[3]); 
        }
    }
    float desiredFPR = 0.1, desiredDR = 0.95;
    CascadeClassifier cascadeClassifier("feature_outputs.bin", positiveDir, negativeDir, width, height);
    cascadeClassifier.trainCascade(stages, boostRounds, featureIncrements, desiredFPR, desiredDR);
    return 0;
}
