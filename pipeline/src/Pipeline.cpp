#include <stdio.h>
#include <LabeledImage.h>
#include <vector>
#include <opencv2/highgui/highgui_c.h>

#include "GPreProcessor.h"
#include "MorphologyProcessor.h"
#include "ThresholdProcessor.h"
#include "ContourProcessor.h"
#include "RoiBuildingProcessor.h"

#define NUM_IMAGES 8
#define TARGET 1
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

    // Coalesce labels
    printf("TODO: Coalesce labels\n");

    // This should create the ImageProcessor
    GPreProcessor    preprocessor(targetImages, TARGET, 3, 3, 1.0, 1.0);
    ContourProcessor contourprocessor(targetImages, TARGET, 8, 20);
    
    // Run the preprocessor
    preprocessor.processImages();

    // Run the feature extractor
    contourprocessor.processImages();

    // Run the ROI builder

    // Score the output
    printf("TODO: implement scoring around Image Processors\n");

    // Display the processed image
    cvShowImage("Processed", targetImages[TARGET]->image);
    cvWaitKey();

    // Clean up Images
    for(uint32_t i = 0; i < targetImages.size(); i++) {
        delete targetImages[i];
    }

}
