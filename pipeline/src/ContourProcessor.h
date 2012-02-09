#ifndef CONTOURPROCESSOR_H_
#define CONTOURPROCESSOR_H_

#include <LabeledImage.h>
#include "ImageProcessor.h"
#include <vector>

using namespace std;

namespace Bioimagery {

    class ContourProcessor : public ImageProcessor {

    public:
        ContourProcessor(vector<LabeledImage*> images, int targetIndex, double threshold);
        ContourProcessor(LabeledImage** images, int numImages, int targetIndex, double threshold);
        virtual ~ContourProcessor();
        
        vector<Roi*> rois;

        // Runs image processing and returns the target image
        virtual LabeledImage* processImages();

        static const uint8_t OCCUPIED   = 0;
        static const uint8_t UNOCCUPIED = 255;
    private:
        double threshold;
    };

}

#endif /* CONTOURPROCESSOR_H_ */

