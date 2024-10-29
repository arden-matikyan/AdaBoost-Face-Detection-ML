#include "cascadeClassifier.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

int main(int argc, char* argv[]) {

    std::vector<StrongClassifier> strongClassifiers;
    char* positiveDir = "/home/rkoepke/final/good";
    char* negativeDir = "/home/rkoepke/final/bad";
    int width = 24, height = width, stages = 2, boostRounds = 1, featureIncrements = 1000;
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

    std::ostringstream filename;
    filename << "SC_stages_" << stages << "_boostRnds_" << boostRounds << "_featureIncr_" << featureIncrements << ".bin";
    float desiredFPR = 0.1, desiredDR = 0.95;
    CascadeClassifier cascadeClassifier("feature_outputs.bin", positiveDir, negativeDir, width, height);
    //cascadeClassifier.trainCascade(stages, boostRounds, featureIncrements, desiredFPR, desiredDR);
    //cascadeClassifier.saveStrongClassifiers(filename.str().c_str());

    strongClassifiers = cascadeClassifier.loadStrongClassifiers("SC_stages_3_boostRnds_10_featureIncr_1000.bin");
    int i = 1;
    printf("stages = %d, Boost Rounds = %d, Feature Increments = %d\n", stages, 10, 1000);
    for (auto& strongClassifier: strongClassifiers) {
        printf("    strongClassifer %d, , DR = %.2f, FPR = %.2f\n", 
        i,strongClassifier.getDR(), strongClassifier.getFPR());
        /*
        std::vector<WeakClassifier> weakClassifiers;
        weakClassifiers = strongClassifier.getClassifiers();
        for (auto& weakClassifier : weakClassifiers) {
            weakClassifier.print();
        }
        i ++;
        printf("\n\n");
        */
        i++;
    }

    strongClassifiers = cascadeClassifier.loadStrongClassifiers("SC_stages_3_boostRnds_10_featureIncr_500.bin");
    i = 1;
    printf("\nstages = %d, Boost Rounds = %d, Feature Increments = %d\n", stages, 10, 500);
    for (auto& strongClassifier: strongClassifiers) {
        printf("    strongClassifer %d, , DR = %.2f, FPR = %.2f\n", 
        i,strongClassifier.getDR(), strongClassifier.getFPR());
        i++;
    }

    strongClassifiers = cascadeClassifier.loadStrongClassifiers("SC_stages_3_boostRnds_1_featureIncr_1000.bin");
    i = 1;
    printf("\nstages = %d, Boost Rounds = %d, Feature Increments = %d\n", stages, 1, 1000);
    for (auto& strongClassifier: strongClassifiers) {
        printf("    strongClassifer %d, , DR = %.2f, FPR = %.2f\n", 
        i,strongClassifier.getDR(), strongClassifier.getFPR());
        i++;
    }

    strongClassifiers = cascadeClassifier.loadStrongClassifiers("SC_stages_3_boostRnds_1_featureIncr_500.bin");
    i = 1;
    printf("\nstages = %d, Boost Rounds = %d, Feature Increments = %d\n", stages, 1, 500);
    for (auto& strongClassifier: strongClassifiers) {
        printf("    strongClassifer %d, , DR = %.2f, FPR = %.2f\n", 
        i,strongClassifier.getDR(), strongClassifier.getFPR());
        i++;
    }

    return 0;
}
