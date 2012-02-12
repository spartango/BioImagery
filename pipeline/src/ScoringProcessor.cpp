#include "ScoringProcessor.h"
#include <LabeledImage.h>
#include <Roi.h>
#include <opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

#define MAX_RECT_THICKNESS 10

namespace Bioimagery {

    ScoringProcessor::ScoringProcessor(vector<LabeledImage*> images,
                                       int targetIndex,
                                       vector<Roi*> targets) : ImageProcessor(images, targetIndex),
                                                               rois(targets) {

    }

    ScoringProcessor::ScoringProcessor(LabeledImage** images,
                                       int numImages,
                                       int targetIndex,
                                       vector<Roi*> targets): ImageProcessor(images, numImages, targetIndex),
                                                              rois(targets) {
   
    }

    ScoringProcessor::~ScoringProcessor() {

    }

    LabeledImage* ScoringProcessor::processImages() {
        // Make sure we load the target image
        images[targetIndex]->loadImage("proto.melamp.us");

        return images[targetIndex];
    }

    void ScoringProcessor::scoreRois() {
        // Score will be calculated from area overlap 
        LabeledImage *targetImage = images[targetIndex];

        // For each target roi
        for(uint32_t i = 0; i < rois.size(); i++){
            Roi *targetRoi = rois[i];

            Roi     *bestMatch = NULL;
            uint64_t matchArea = 0;

            for(uint32_t l = 0; l < targetImage->rois.size(); l++) {
                Roi *labeledRoi = targetImage->rois[l];

                //  Check Intersection with each labeled roi
                Rect targetRect   = Rect(targetRoi->x, targetRoi->y, targetRoi->width, targetRoi->height);
                Rect labelRect    = Rect(labeledRoi->x, labeledRoi->y, labeledRoi->width, labeledRoi->height);
                Rect intersection = labelRect & targetRect; 

                int area = intersection.area();
                if(area > matchArea) {
                    bestMatch = labeledRoi;
                    matchArea = area;
                }
            }

        }
    }

    void ScoringProcessor::drawRois() {
        for(int i = 0; i < rois.size(); i++) {
            cvRectangle(images[targetIndex]->image, 
                        cvPoint(rois[i]->x, rois[i]->y), 
                        cvPoint(rois[i]->x + rois[i]->width, rois[i]->y + rois[i]->height), 
                        CV_RGB(rand() % 255, rand() % 255, rand() % 255),
                        (rois[i]->confidence / MAX_RECT_THICKNESS + 1));
    }
  }
}
