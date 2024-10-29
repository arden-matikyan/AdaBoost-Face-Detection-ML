#include "cascadeClassifier.h"

CascadeClassifier::CascadeClassifier() {}

std::vector<StrongClassifier> CascadeClassifier::loadStrongClassifiers(const char* filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        printf("error loading file\n");
        return {}; 
    }

    size_t numClassifiers;
    std::vector<StrongClassifier> strongClassifiers;

    if (inFile.read(reinterpret_cast<char*>(&numClassifiers), sizeof(numClassifiers))) {
        strongClassifiers.resize(numClassifiers);

        for (auto& classifier : strongClassifiers) {
            classifier.deserialize(inFile);
        }

        if (!inFile.good()) {
            printf("error reading from file\n");
            return {}; 
        }
    } else {
        printf("error reading number of files\n");
        return {}; 
    }

    inFile.close();
    printf("Strong classifiers loaded success\n");
    return strongClassifiers;  
}

void CascadeClassifier::saveStrongClassifiers(const char* filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        printf("error saving");
        return;
    }

    size_t numClassifiers = strongClassifiers.size();
    outFile.write(reinterpret_cast<const char*>(&numClassifiers), sizeof(numClassifiers));

    for (const auto& classifier : strongClassifiers) {
        classifier.serialize(outFile);
    }

    outFile.close();
    if (!outFile.good()) {
        printf("error saving\n");
        return;
    }

    printf("saved correctly\n");
}
