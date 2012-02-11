#include "ScoringProcessor.h"
#include <LabeledImage.h>
#include <opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

namespace Bioimagery {

    ScoringProcessor::ScoringProcessor(vector<LabeledImage*> images,
                                             int targetIndex,
                                             vector<Roi*> targets) : ImageProcessor(images, targetIndex),
                                                                     rois(targets) {

    }

    ScoringProcessor::ScoringProcessor(LabeledImage** images,
                                             int numImages,
                                             int targetIndex,
                                             vector<Roi*> targets): ImageProcessor(images, numImages, targetIndex),
                                                                    rois(targets) {

    }

    LabeledImage* ScoringProcessor::processImages() {
        // Make sure we load the target image
        images[targetIndex]->loadImage("proto.melamp.us");

        return images[targetIndex];
    }
}
