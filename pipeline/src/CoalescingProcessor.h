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
        CoalescingProcessor(vector<LabeledImage*> images, int targetIndex, double threshold);
        CoalescingProcessor(LabeledImage **images, int numImages, int targetIndex, double threshold);

        virtual ~CoalescingProcessor();

        // Runs image processing and returns the target image
        LabeledImage* processImages();
    
    private: 
        double threshold;
        
    };

}

#endif /* COALESCINGPROCESSOR_H_ */

