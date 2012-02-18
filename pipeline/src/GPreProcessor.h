#ifndef GPREPROCESSOR_H_
#define GPREPROCESSOR_H_

#include <LabeledImage.h>
#include "ImageProcessor.h"
#include <vector>

using namespace std;

namespace Bioimagery {

    class GPreProcessor : public ImageProcessor {

    public:
        GPreProcessor(vector<LabeledImage*> images, 
                      int targetIndex, 
                      int filter_width, 
                      int filter_height, 
                      double sigma_x,
                      double sigma_y);

        GPreProcessor(LabeledImage **images, 
                      int numImages, 
                      int targetIndex,
                      int filter_width, 
                      int filter_height, 
                      double sigma_x,
                      double sigma_y);

        virtual ~GPreProcessor();

        // Runs image processing and returns the target image
        virtual LabeledImage* processImages();
    
    private:
        int filter_width;
        int filter_height;
        double sigma_x;
        double sigma_y;

    };

}

#endif /* GPREPROCESSOR_H_ */

