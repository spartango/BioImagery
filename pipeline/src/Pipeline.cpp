#include <stdio.h>
#include <LabeledImage.h>
#include <vector>
#include <opencv2/highgui/highgui_c.h>

#include "GPreProcessor.h"
#include "MorphologyProcessor.h"
#include "ThresholdProcessor.h"
#include "ContourProcessor.h"
#include "ScoringProcessor.h"
#include "CoalescingProcessor.h"
#include "CannyEdgeProcessor.h"
#include "PyramidSegProcessor.h"

#define NUM_IMAGES 8
#define TARGET 2
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

    CoalescingProcessor labelprocessor(targetImages, TARGET, 70, targetImages[TARGET]->rois);

    // Coalesce labeled rois
    labelprocessor.processImages();
    //targetImages[TARGET]->rois = labelprocessor.rois;

    // Processors
    GPreProcessor preprocessor(targetImages, TARGET, 5, 5, 1.0, 1.0);
    // CannyEdgeProcessor cannyedgeprocessor(targetImages, TARGET, 7, 40.0, 80.0);
    // MorphologyProcessor morphprocessor(targetImages, TARGET, 1);
    // ThresholdProcessor threshprocessor(targetImages, TARGET, 127.0);
    // PyramidSegProcessor segproc (targetImages, TARGET, 20, 5);

    ContourProcessor    contourprocessor(targetImages, TARGET, 6.0, 11);

    // Run the preprocessor
    preprocessor.processImages();

    // Run the feature extractor
    contourprocessor.processImages();

    // Run the canny edge detector
    // cannyedgeprocessor.processImages();

    // Run the segmenter
    // segproc.processImages();

    // Run the ROI builder
    CoalescingProcessor coalescingprocessor(targetImages, TARGET, 50, contourprocessor.rois);
    coalescingprocessor.processImages();

    // Score the output 
    ScoringProcessor scoringprocessor(targetImages, TARGET, coalescingprocessor.rois);   
    scoringprocessor.processImages();

    // Display the processed image
    cvShowImage("Processed", targetImages[TARGET]->image);
    cvWaitKey();

    // Clean up Images
    for(uint32_t i = 0; i < targetImages.size(); i++) {
        delete targetImages[i];
    }

}
