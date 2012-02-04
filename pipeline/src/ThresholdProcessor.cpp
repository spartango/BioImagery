#include "ThresholdProcessor.h"
#include <LabeledImage.h>
#include <opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

namespace Bioimagery {

    ThresholdProcessor::ThresholdProcessor(vector<LabeledImage*> images,
                                             int targetIndex,
                                             double threshold) : ImageProcessor(images, targetIndex),
                                                                 threshold(threshold) {

    }

    ThresholdProcessor::ThresholdProcessor(LabeledImage** images,
                                             int numImages,
                                             int targetIndex,
                                             double threshold): ImageProcessor(images, numImages, targetIndex),
                                                                threshold(threshold) {

    }

    LabeledImage* ThresholdProcessor::processImages() {
        // Make sure we load the target image
        images[targetIndex]->loadImage("proto.melamp.us");

        // Create a target
        IplImage* newImage = cvCreateImage(cvSize(images[targetIndex]->image->width, images[targetIndex]->image->height),
                     images[targetIndex]->image->depth,
                     1);

        // Get to the right colorspace
        cvCvtColor(images[targetIndex]->image, newImage, CV_RGB2GRAY);

        // Threshold the target image
        cvThreshold(newImage, newImage, threshold, 255.0, CV_THRESH_BINARY_INV);

        images[targetIndex]->image = newImage;

        return images[targetIndex];
    }
}
