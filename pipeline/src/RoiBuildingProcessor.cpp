#include "RoiBuildingProcessor.h"
#include <LabeledImage.h>
#include <opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

namespace Bioimagery {

    LabeledImage* RoiBuildingProcessor::processImages() {
        // Make sure we load the target image
        images[targetIndex]->loadImage("proto.melamp.us");
        
        // TODO scan image

        return images[targetIndex];
    }
}