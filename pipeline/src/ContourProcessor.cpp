#include "ContourProcessor.h"

#include <LabeledImage.h>
#include <Roi.h>

#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgproc/imgproc_c.h>
#include <iostream>

using namespace std;
using namespace cv;

namespace Bioimagery {

  ContourProcessor::ContourProcessor(vector<LabeledImage*> images,
                                     int targetIndex,
                                     double threshold, 
                                     int rasterIncrement) : ImageProcessor(images, targetIndex),
                                                            threshold(threshold),
                                                            rasterIncrement(rasterIncrement) {

  }

  ContourProcessor::ContourProcessor(LabeledImage** images,
                                     int numImages,
                                     int targetIndex,
                                     double threshold,
                                     int rasterIncrement) : ImageProcessor(images, numImages, targetIndex),
                                                            threshold(threshold),
                                                            rasterIncrement(rasterIncrement) {

  }

  ContourProcessor::~ContourProcessor() {
    for(uint32_t i=0; i<rois.size(); i++) {
      delete rois[i];
    }
    rois.clear();
  }

  LabeledImage* ContourProcessor::processImages() {
    images[targetIndex]->loadImage("proto.melamp.us");
    
    // Create a binary map 
    IplImage* map = cvCreateImage(cvGetSize(images[targetIndex]->image), IPL_DEPTH_8U, 1);
    printf("Map created %d x %d -> %ub\n", map->width, map->height, map->imageSize);
    // Mark unsolved positions
    memset(map->imageData, UNOCCUPIED, map->imageSize);

    // Make a working copy of the image
    IplImage* workingCopy = cvCreateImage(cvGetSize(images[targetIndex]->image), 
                                          images[targetIndex]->image->depth, 
                                          images[targetIndex]->image->nChannels);

    // Raster across the map
    for(int y = 0; y < map->height; y+=rasterIncrement) {

      uchar *ptr = (uchar*) (map->imageData + y*map->widthStep);

      for(int x = 0; x < map->width; x+=rasterIncrement) {
        //printf("%d|", ptr[x]);

        if(ptr[x] == UNOCCUPIED) {
          // if position unsolved

          // Select a color:
          CvScalar color = CV_RGB((rand() % 255), (rand() % 255), (rand() % 255));
          
          // Will be Feature boxes
          CvConnectedComp component;

          // Try a flood fill    
          cvCopy(images[targetIndex]->image, workingCopy);

          cvFloodFill(workingCopy, 
                      cvPoint(x, y), color, 
                      cvScalarAll(threshold), 
                      cvScalarAll(threshold), 
                      &component);

          // Store the ROI box
          if(component.rect.width > 1 
            && component.rect.height > 1 
            && component.rect.width != map->width 
            && component.rect.height != map->height) {

            //Copy the component to a map 
            cvRectangle(map, 
                        cvPoint(component.rect.x, component.rect.y), 
                        cvPoint(component.rect.x + component.rect.width, component.rect.y + component.rect.height), 
                        cvScalar(OCCUPIED), CV_FILLED);

            Roi* newRoi = new Roi(0, component.rect.x, component.rect.y, component.rect.height, component.rect.width, 100);
            rois.push_back(newRoi);
            //printf("ROI created: (%d, %d) => %d, %d of %d x %d\n", x, y, newRoi->x, newRoi->y, newRoi->width, newRoi->height);
          }
        } 
      }
    }

    printf("Floodfilling complete: %lu\n", rois.size());

    //cvShowImage("Map", map);
    cvReleaseImage(&map);
    cvReleaseImage(&workingCopy);

    return images[targetIndex];
  }


}
