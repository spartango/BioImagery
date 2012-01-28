#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_

#include "LabeledImage.h"

#include <vector>

using namespace std;

namespace Bioimagery {

  class ImageProcessor {

  public:
    ImageProcessor(vector<LabeledImage> images, int targetIndex);
    ImageProcessor(LabeledImage *images, int numImages, int targetIndex);

    virtual ~ImageProcessor();

    // Runs image processing and returns the target image
    virtual LabeledImage processImages();

  protected:
    vector<LabeledImage> images;
    int targetIndex;

  };

}

#endif /* IMAGEPROCESSING_H_ */

