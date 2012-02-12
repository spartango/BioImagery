#include "CoalescingProcessor.h"
#include <LabeledImage.h>
#include <opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

namespace Bioimagery {

    CoalescingProcessor::CoalescingProcessor(vector<LabeledImage*> images,
                                             int targetIndex,
                                             double threshold) : ImageProcessor(images, targetIndex),
                                                                 threshold(threshold) {

    }

    CoalescingProcessor::CoalescingProcessor(LabeledImage** images,
                                             int numImages,
                                             int targetIndex,
                                             double threshold): ImageProcessor(images, numImages, targetIndex),
                                                                threshold(threshold) {

    }

    CoalescingProcessor::~CoalescingProcessor() {

    }

    LabeledImage* CoalescingProcessor::processImages() {
        // Make sure we load the target image
        images[targetIndex]->loadImage("proto.melamp.us");

        // Scan through ROIs, for each
        // Find maximum overlap > threshold
        // Coalesce the ROIs into a single

        return images[targetIndex];
    }
}
