#include "PyramidSegProcessor.h"
#include <LabeledImage.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgproc/imgproc_c.h>
#include <iostream>

using namespace std;
using namespace cv;

namespace Bioimagery {

  PyramidSegProcessor::PyramidSegProcessor(vector<LabeledImage*> images,
                                           int targetIndex,
                                           double threshold1,
                                           double threshold2) : ImageProcessor(images, targetIndex),
                                                                threshold1(threshold1),
                                                                threshold2(threshold2)  {

  }

  PyramidSegProcessor::PyramidSegProcessor(LabeledImage** images,
                                           int numImages,
                                           int targetIndex,
                                           double threshold1,
                                           double threshold2): ImageProcessor(images, numImages, targetIndex),
                                                               threshold1(threshold1),
                                                               threshold2(threshold2)  {

  }

  LabeledImage* PyramidSegProcessor::processImages() {
    images[targetIndex]->loadImage("proto.melamp.us");

    IplImage * img1 = cvCloneImage( images[targetIndex]->image );

    int block_size = 1000, level = 4;

    CvMemStorage *storage = cvCreateMemStorage( block_size );

    CvSeq *comp;

    cvPyrSegmentation(images[targetIndex]->image, img1, storage, &comp, level, threshold1 + 1, threshold2 + 1);

    images[targetIndex]->image = img1;

    return images[targetIndex];
  }
}
