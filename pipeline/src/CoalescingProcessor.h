#ifndef COALESCINGPROCESSOR_H_
#define COALESCINGPROCESSOR_H_

#include <LabeledImage.h>
#include <Roi.h>

#include "ImageProcessor.h"
#include <vector>

using namespace std;

namespace Bioimagery {

    class CoalescingProcessor : ImageProcessor {

    public:
        CoalescingProcessor(vector<LabeledImage*> images, int targetIndex, double threshold, vector<Roi*> rois);
        CoalescingProcessor(LabeledImage **images, int numImages, int targetIndex, double threshold, vector<Roi*> rois);

        virtual ~CoalescingProcessor();

        // Runs image processing and returns the target image
        LabeledImage* processImages();

        vector<Roi*> rois;
    
    private: 
        double threshold;
        
    };

}

#endif /* COALESCINGPROCESSOR_H_ */

