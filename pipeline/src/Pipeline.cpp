#include <stdio.h>
#include <LabeledImage.h>
#include <vector>

#include "ImageProcessor.h"

#define NUM_IMAGES 8
#define LABEL_HOST "proto.melamp.us"

using namespace std;
using namespace Bioimagery;

int main() {
    vector<LabeledImage*> targetImages;

    // Fetch it some labeled Images
    for(int i = 0; i < NUM_IMAGES; i++) {
        LabeledImage *newImage = new LabeledImage(i);
        newImage->load(LABEL_HOST);
        targetImages.push_back(newImage);
    }

    // This should create the ImageProcessor
    ImageProcessor processor(targetImages, 0);

    // Run the processor
    processor.processImages();

    // Score the output
    printf("TODO: implement scoring around Image Processors\n");

    // Clean up Images
    for(int i = 0; i < targetImages.size(); i++) {
        delete targetImages[i];
    }


}
