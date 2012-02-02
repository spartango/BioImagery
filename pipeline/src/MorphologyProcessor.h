#ifndef MORPHOLOGYPROCESSOR_H_
#define MORPHOLOGYPROCESSOR_H_

#include <LabeledImage.h>
#include "ImageProcessor.h"
#include <vector>

using namespace std;

namespace Bioimagery {

    class MorphologyProcessor : public ImageProcessor {

    public:
        MorphologyProcessor(vector<LabeledImage*> images, int targetIndex);
        MorphologyProcessor(LabeledImage** images, int numImages, int targetIndex);

        // Runs image processing and returns the target image
        virtual LabeledImage* processImages();
    
    };

}

#endif /* MORPHOLOGYPROCESSOR_H_ */

