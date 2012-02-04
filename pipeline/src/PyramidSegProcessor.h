#ifndef PYRAMIDSEGPROCESSOR_H_
#define PYRAMIDSEGPROCESSOR_H_

#include <LabeledImage.h>
#include "ImageProcessor.h"
#include <vector>

using namespace std;

namespace Bioimagery {

  class PyramidSegProcessor : public ImageProcessor {

  public:
    PyramidSegProcessor(vector<LabeledImage*> images, int targetIndex, double threshold1, double threshold2);
    PyramidSegProcessor(LabeledImage** images, int numImages, int targetIndex, double threshold1, double threshold2);

    // Runs image processing and returns the target image
    virtual LabeledImage* processImages();

  private:
    double threshold1, threshold2;
  };

}

#endif /* PYRAMIDSEGPROCESSOR_H_ */

