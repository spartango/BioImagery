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

  LabeledImage* ContourProcessor::processImages() {
    images[targetIndex]->loadImage("proto.melamp.us");

    // Make sure we load the target image
    Mat img = images[targetIndex]->image;

    // Create a target
    IplImage* newImage = cvCreateImage(cvSize(images[targetIndex]->image->width, images[targetIndex]->image->height),
                                       images[targetIndex]->image->depth,
                                       1);

    // Get to the right colorspace
    cvCvtColor(images[targetIndex]->image, newImage, CV_RGB2GRAY);

    // Threshold the target image
    cvThreshold(newImage, newImage, threshold, 255.0, CV_THRESH_BINARY_INV);

    //    Mat dst = Mat::zeros(img.size(), CV_8UC3);
    CvMemStorage* g_storage = cvCreateMemStorage(0);;
    CvSeq * contours = 0;
    int a = cvFindContours( newImage, g_storage, &contours, sizeof(CvContour), CV_RETR_CCOMP);

    // iterate through all the top-level contours,
    // draw each connected component with its own random color
    // int size = contours.size();
    // for (int idx = 0; idx < size; idx++) {
    for (CvSeq* c = contours; c != NULL; c = c->h_next) {
      for (CvSeq* d = c; d != NULL; d = d->v_next) {
        CvScalar red = CV_RGB(rand()&255,rand()&255,rand()&255);
        CvScalar blue = CV_RGB(rand()&255,rand()&255,rand()&255);
        cvDrawContours(
                       images[targetIndex]->image,
                       d,
                       red,// Red
                       blue,// Blue
                       1,// Vary max_level and compare results
                       CV_FILLED,
                       8 );
      }
    }
    // IplImage new_img = dst;

    // images[targetIndex]->image = &new_img;

    return images[targetIndex];
  }
}
