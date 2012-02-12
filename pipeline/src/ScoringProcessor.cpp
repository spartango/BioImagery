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
                                       vector<Roi*> rois) : ImageProcessor(images, targetIndex),
                                                               rois(rois) {

    }

    ScoringProcessor::ScoringProcessor(LabeledImage** images,
                                       int numImages,
                                       int targetIndex,
                                       vector<Roi*> rois): ImageProcessor(images, numImages, targetIndex),
                                                              rois(rois) {
   
    }

    ScoringProcessor::~ScoringProcessor() {

    }

    LabeledImage* ScoringProcessor::processImages() {
        // Make sure we load the target image
        images[targetIndex]->loadImage("proto.melamp.us");
        
        printf("Scoring rois: %u\n", rois.size());
        scoreRois();

        printf("Drawing rois\n");
        drawRois();
        
        return images[targetIndex];
    }

    void ScoringProcessor::scoreRois() {
        // For each target roi
        for(uint32_t i = 0; i < rois.size(); i++){
            scoreRoi(rois[i]);
        }
    }

    void ScoringProcessor::scoreRoi(Roi *targetRoi) {
        // Score will be calculated from area overlap 
        LabeledImage *targetImage = images[targetIndex];

        Roi *bestMatch = NULL;
        int  matchArea = 0;

        for(uint32_t l = 0; l < targetImage->rois.size(); l++) {
            Roi *labeledRoi = targetImage->rois[l];

            Rect intersection = targetRoi->intersection(labeledRoi);
            int area = intersection.area();

            if(area > matchArea) {
                bestMatch = labeledRoi;
                matchArea = area;
            }
        }

        if(bestMatch != NULL) {
            // Assign confidence score
            int labelArea  = (bestMatch->height * bestMatch->width);
            int targetArea = (targetRoi->height * targetRoi->width);

            // % of label occupied by targetROI, compensated for oversized areas
            targetRoi->confidence = 100  
                                    * ((labelArea / targetArea) > 1 ? 1 : (labelArea / targetArea)) 
                                    * (matchArea / labelArea);
        } else {
            targetRoi->confidence = 0;
        }
        printf("Roi (%d, %d) -> Confidence: %d\n", targetRoi->x, targetRoi->y, targetRoi->confidence);

    }

    void ScoringProcessor::drawRois() {
        for(uint32_t i = 0; i < rois.size(); i++) {
            cvRectangle(images[targetIndex]->image, 
                        cvPoint(rois[i]->x, rois[i]->y), 
                        cvPoint(rois[i]->x + rois[i]->width, rois[i]->y + rois[i]->height), 
                        CV_RGB(rand() % 255, rand() % 255, rand() % 255),
                        (rois[i]->confidence / MAX_RECT_THICKNESS + 1));
    }
  }
}
