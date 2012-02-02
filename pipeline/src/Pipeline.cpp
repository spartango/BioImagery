#include <stdio.h>
#include <LabeledImage.h>
#include <vector>
#include <opencv2/highgui/highgui_c.h>

#include "GPreProcessor.h"

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
    GPreProcessor processor(targetImages, 0, 5, 5, 0, 0);

    // Run the processor
    LabeledImage* result = processor.processImages();

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
