#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_

#include "LabeledImage.h"

using namespace LabeledImage

namespace Bioimagery {

  class ImageProcessor {

  public:
    ImageProcessor(LabeledImage* allImages, int targetIndex) {

    }
    virtual ~LabeledImage();

    LabeledImage* labeledImages;

    int t_index;

    // Runs image processing and returns the target image
    LabeledImage processImages() {}
  }
}
