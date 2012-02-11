#include "MorphologyProcessor.h"
#include <LabeledImage.h>
#include <opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

namespace Bioimagery {

    MorphologyProcessor::MorphologyProcessor(vector<LabeledImage*> images, 
                                             int targetIndex, 
                                             int iterations) : ImageProcessor(images, targetIndex), 
                                                               iterations(iterations) {

    }

    MorphologyProcessor::MorphologyProcessor(LabeledImage** images, 
                                             int numImages, 
                                             int targetIndex, 
                                             int iterations): ImageProcessor(images, numImages, targetIndex), 
                                                              iterations(iterations) {

    }

    MorphologyProcessor::~MorphologyProcessor() {

    }

    LabeledImage* MorphologyProcessor::processImages() {
        // Make sure we load the target image
        images[targetIndex]->loadImage("proto.melamp.us");
        
        // Close the target image
        cvMorphologyEx(images[targetIndex]->image, images[targetIndex]->image, NULL, NULL, CV_MOP_CLOSE, iterations);
        cvSmooth(images[targetIndex]->image, images[targetIndex]->image, CV_GAUSSIAN);

        return images[targetIndex];
    }
}