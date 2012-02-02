#include "MorphologyProcessor.h"
#include <LabeledImage.h>
#include <opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

namespace Bioimagery {

    MorphologyProcessor::MorphologyProcessor(vector<LabeledImage*> images, int targetIndex) : ImageProcessor(images, targetIndex) {

    }

    MorphologyProcessor::MorphologyProcessor(LabeledImage** images, int numImages, int targetIndex): ImageProcessor(images, numImages, targetIndex) {

    }

    LabeledImage* MorphologyProcessor::processImages() {
        // Make sure we load the target image
        images[targetIndex]->loadImage("proto.melamp.us");
        
        // Close the target image
        cvMorphologyEx(images[targetIndex]->image, images[targetIndex]->image, NULL, NULL, CV_MOP_CLOSE, 1);
        
        return images[targetIndex];
    }
}