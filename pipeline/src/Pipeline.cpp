#include <stdio.h>
#include <LabeledImage.h>
#include <vector>
#include <opencv2/highgui/highgui_c.h>

#include "GPreProcessor.h"
#include "MorphologyProcessor.h"

#define NUM_IMAGES 8
#define LABEL_HOST "proto.melamp.us"

using namespace std;
using namespace Bioimagery;

int main() {
    vector<LabeledImage*> targetImages;

    // Fetch it some labeled Images
    for(int i = 1; i < NUM_IMAGES; i++) {
        LabeledImage *newImage = new LabeledImage(i);
        newImage->load(LABEL_HOST);
        targetImages.push_back(newImage);
    }

    // This should create the ImageProcessor
    GPreProcessor preprocessor(targetImages, 0, 5, 5, 1.0, 1.0);
    MorphologyProcessor morphprocessor(targetImages, 0);

    // Run the processor
    preprocessor.processImages();
    LabeledImage* result = morphprocessor.processImages();

    // Score the output
    printf("TODO: implement scoring around Image Processors\n");

    // Display the processed image
    cvShowImage("Processed", result->image);
    cvWaitKey();

    // Clean up Images
    for(int i = 0; i < targetImages.size(); i++) {
        delete targetImages[i];
    }

}
