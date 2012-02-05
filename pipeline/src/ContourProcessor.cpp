#include "ContourProcessor.h"
#include <LabeledImage.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgproc/imgproc_c.h>
#include <iostream>

using namespace std;
using namespace cv;

namespace Bioimagery {

  ContourProcessor::ContourProcessor(vector<LabeledImage*> images,
                                     int targetIndex,
                                     double threshold) : ImageProcessor(images, targetIndex),
                                                         threshold(threshold) {

  }

  ContourProcessor::ContourProcessor(LabeledImage** images,
                                     int numImages,
                                     int targetIndex,
                                     double threshold): ImageProcessor(images, numImages, targetIndex),
                                                        threshold(threshold) {

  }

  ContourProcessor::~ContourProcessor() {
    for(int i=0; i<rois.size(); i++) {
      delete rois[i];
    }
    rois.clear();
  }

  LabeledImage* ContourProcessor::processImages() {
    images[targetIndex]->loadImage("proto.melamp.us");
    
    // Will be Feature boxes
    CvConnectedComp *components = 0;
    
    // Raster across the image
    // TODO

    // Select a color: TODO
    CvScalar color = CV_RGB(0,0,0);

    cvFloodFill(images[targetIndex]->image, cvPoint(0, 0), color, cvScalarAll(threshold), cvScalarAll(threshold), components);

    // Copy the component to a map
    // TODO

    // Store the ROI boxes
    // TODO

    return images[targetIndex];
  }
}
