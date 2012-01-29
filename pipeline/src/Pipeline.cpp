#include <stdio.h>
#include <LabeledImage.h>
#include <vector>

#include "ImageProcessor.h"

#define NUM_IMAGES 8

using namespace std;
using namespace Bioimagery;

int main() {
    vector<LabeledImage> targetImages;

    // Fetch it some labeled Images
    for(int i = 0; i < NUM_IMAGES; i++) {
        targetImages.push_back(LabeledImage(i));
    }

    // This should create the ImageProcessor

    // Run the processor

    // Score the output

    printf("TODO: implement pipeline around Image Processors\n");

}
