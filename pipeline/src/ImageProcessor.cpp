#include "ImageProcessor.h"
#include <LabeledImage.h>

using namespace std;

namespace Bioimagery {
	ImageProcessor::ImageProcessor(vector<LabeledImage> images,
                                   int targetIndex):
                                   images(images),
                                   targetIndex(targetIndex) {

    }

    ImageProcessor::ImageProcessor(LabeledImage *images,
                                   int numImages,
                                   int targetIndex):
                                   targetIndex(targetIndex) {
        // For each Image add to a new vector;
        // TODO
    }

    ImageProcessor::~ImageProcessor() {
        // Clean up the images and image vector
        // TODO
    }

    LabeledImage ImageProcessor::processImages() {
        // By default returns the Identity-- unprocessed image
        return images[targetIndex];
    }
}