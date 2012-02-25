#ifndef CANNYEDGEPROCESSOR_H_
#define CANNYEDGEPROCESSOR_H_

#include <LabeledImage.h>
#include "ImageProcessor.h"
#include <vector>

using namespace std;

namespace Bioimagery {

    class CannyEdgeProcessor : public ImageProcessor {

    public:
        CannyEdgeProcessor(vector<LabeledImage*> images, 
                      int targetIndex, 
                      int aperture_size, 
                      double low_thresh,
                      double high_thresh);

        CannyEdgeProcessor(LabeledImage **images, 
                      int numImages, 
                      int targetIndex,
                      int aperture_size, 
                      double low_thresh,
                      double high_thresh);

        virtual ~CannyEdgeProcessor();

        // Runs image processing and returns the target image
        virtual LabeledImage* processImages();
    
    private:
        int aperture_size;
        double low_thresh;
        double high_thresh;

    };

}

#endif /* CANNYEDGEPROCESSOR_H_ */
