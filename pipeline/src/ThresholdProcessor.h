#ifndef THRESHOLDPROCESSOR_H_
#define THRESHOLDPROCESSOR_H_

#include <LabeledImage.h>
#include "ImageProcessor.h"
#include <vector>

using namespace std;

namespace Bioimagery {

    class ThresholdProcessor : public ImageProcessor {

    public:
        ThresholdProcessor(vector<LabeledImage*> images, int targetIndex, double threshold);
        ThresholdProcessor(LabeledImage** images, int numImages, int targetIndex, double threshold);

        virtual ~ThresholdProcessor();

        // Runs image processing and returns the target image
        virtual LabeledImage* processImages();

    private:
        double threshold;
    };

}

#endif /* THRESHOLDPROCESSOR_H_ */

