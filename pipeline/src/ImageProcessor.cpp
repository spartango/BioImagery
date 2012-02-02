#include "ImageProcessor.h"
#include <LabeledImage.h>

using namespace std;

namespace Bioimagery {
    ImageProcessor::ImageProcessor(vector<LabeledImage*> images,
                                   int targetIndex):
                                   images(images),
                                   targetIndex(targetIndex) {
    }

    ImageProcessor::ImageProcessor(LabeledImage **targetImages,
                                   int numImages,
                                   int targetIndex):
                                   targetIndex(targetIndex) {
        // For each Image add to a new vector;
        for(int i = 0; i<numImages; i++) {
            images.push_back(targetImages[i]);
        }
    }

    ImageProcessor::~ImageProcessor() {
    }

    LabeledImage* ImageProcessor::processImages() {
        // Make sure the target image is loaded
        images[targetIndex]->loadImage("proto.melamp.us");
        // By default returns the Identity-- unprocessed image
        return images[targetIndex];
    }
}