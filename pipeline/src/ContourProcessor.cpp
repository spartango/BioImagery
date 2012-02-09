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

    // Create a binary map 
    IplImage* map = cvCreateImage(cvSize(images[targetIndex]->width, images[targetIndex]->width), IPL_DEPTH_8U, 1);

    // Mark unsolved positions
    memset(map->imageData, UNOCCUPIED, map->imageSize);

    // Raster across the map
    for(int y = 0; y < map->height; y++) {

      uchar *ptr = (uchar*) (map->imageData + y*map->widthStep);

      for(int x = 0; x < map->width; x++) {
        if(ptr[x] == UNOCCUPIED) {
          // if position unsolved

          // Select a color: TODO
          CvScalar color;// = nextColor();

          cvFloodFill(images[targetIndex]->image, cvPoint(x, y), color, cvScalarAll(threshold), cvScalarAll(threshold), components);

            // Copy the component to a map
            // TODO
        }
      }
    }


    // Store the ROI boxes
    // TODO

    return images[targetIndex];
  }
}
