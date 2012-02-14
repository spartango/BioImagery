#include "CoalescingProcessor.h"
#include <LabeledImage.h>
#include <opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

namespace Bioimagery {

    CoalescingProcessor::CoalescingProcessor(vector<LabeledImage*> images,
                                             int targetIndex,
                                             double threshold,
                                             vector<Roi*> rois) : ImageProcessor(images, targetIndex),
                                                                  rois(rois),
                                                                  threshold(threshold) {

    }

    CoalescingProcessor::CoalescingProcessor(LabeledImage** images,
                                             int numImages,
                                             int targetIndex,
                                             double threshold,
                                             vector<Roi*> rois): ImageProcessor(images, numImages, targetIndex),
                                                                 rois(rois),
                                                                 threshold(threshold) {

    }

    CoalescingProcessor::~CoalescingProcessor() {

    }

    LabeledImage* CoalescingProcessor::processImages() {        
        // Scan through ROIs, for each
        for(uint32_t i = 0; i < rois.size(); i++) {
            Roi *coalesceRoi = rois[i];
            // Try to coalesce with downstream 
            for(uint32_t j = i + 1; j < rois.size(); j++) {
                Roi *targetRoi = rois[j];

                // Check intersection
                int coalesceArea = coalesceRoi->height * coalesceRoi->width;
                int targetArea   = targetRoi->height * targetRoi->width;
                int matchArea    = (coalesceRoi->intersection(targetRoi)).area(); 

                double score     =  100  
                                     * ((coalesceArea / targetArea) >= 1 ? 1.0 
                                                                         : ((double) coalesceArea) / targetArea)
                                     * ((double) matchArea) / coalesceArea;
                if(score >= threshold) {
                    // These are coalescable
                    // Coalesced ROI has
                    // Max bounding box (union)
                    Rect unionRect = Rect(coalesceRoi->x, coalesceRoi->y, coalesceRoi->width, coalesceRoi->height)
                                     | Rect(targetRoi->x, targetRoi->y, targetRoi->width, targetRoi->height);

                    // TODO confidence scoring

                    // Make a new ROI with the coalesced params
                    delete coalesceRoi;
                    coalesceRoi = new Roi(0, unionRect.x, unionRect.y, unionRect.height, unionRect.width, round(score));
                    rois[i] = coalesceRoi;

                    printf("Coalesced into (%d, %d), %d x %d -> %f\n", coalesceRoi->x, 
                                                                       coalesceRoi->y, 
                                                                       coalesceRoi->width, 
                                                                       coalesceRoi->height, 
                                                                       score);

                    // remove the targetRoi
                    rois.erase(rois.begin() + j);
                    j--;
                } else {
                    printf("Separate -> %f\n", score);
                }

            }
        }

        return images[targetIndex];
    }
}
