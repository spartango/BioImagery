#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_

#include "LabeledImage.h"

namespace Bioimagery {

  class ImageProcessor {

  public:
    ImageProcessor(LabeledImage* allImages, int targetIndex);

    virtual ~ImageProcessor();

    LabeledImage* labeledImages;

    int target_index;

    // Runs image processing and returns the target image
    LabeledImage processImages();

  private:

  };

}

#endif /* IMAGEPROCESSING_H_ */

