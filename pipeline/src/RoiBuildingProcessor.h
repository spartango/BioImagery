#ifndef ROIBUILDINGPROCESSOR_H_
#define ROIBUILDINGPROCESSOR_H_

#include <LabeledImage.h>
#include "ImageProcessor.h"
#include <vector>

using namespace std;

namespace Bioimagery {

    class RoiBuildingProcessor : public ImageProcessor {

    public:
        RoiBuildingProcessor(vector<LabeledImage*> images, int targetIndex);
        RoiBuildingProcessor(LabeledImage** images, int numImages, int targetIndex);

        vector<Roi*> rois;

        // Runs image processing and returns the target image
        virtual LabeledImage* processImages();
    };

}

#endif /* ROIBUILDINGPROCESSOR_H_ */