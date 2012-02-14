#include "CoalescingProcessor.h"
#include <LabeledImage.h>
#include <opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

namespace Bioimagery {

    CoalescingProcessor::CoalescingProcessor(vector<LabeledImage*> images,
                                             int targetIndex,
                                             double threshold) : ImageProcessor(images, targetIndex),
                                                                 threshold(threshold) {

    }

    CoalescingProcessor::CoalescingProcessor(LabeledImage** images,
                                             int numImages,
                                             int targetIndex,
                                             double threshold): ImageProcessor(images, numImages, targetIndex),
                                                                threshold(threshold) {

    }

    CoalescingProcessor::~CoalescingProcessor() {

    }

    LabeledImage* CoalescingProcessor::processImages() {
        LabeledImage *targetImage = images[targetIndex];

        // Make sure we load the target image
        targetImage->loadImage("proto.melamp.us");

        // Scan through ROIs, for each
        for(uint32_t i = 0; i < targetImage->rois.size(); i++) {
            Roi *coalesceRoi = targetImage->rois[i];
            // Try to coalesce with downstream 
            for(uint32_t j = i + 1; j < targetImage->rois.size(); j++) {
                Roi *targetRoi = targetImage->rois[j];

                // Check intersection
                int coalesceArea = coalesceRoi->height * coalesceRoi->width;
                int targetArea   = targetRoi->height * targetRoi->width;
                int matchArea    = (coalesceRoi->intersection(targetRoi)).area(); 

                double score     =  100 * ((coalesceArea / targetArea) >= 1 ? 1.0 
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
                    targetImage->rois[i] = coalesceRoi;

                    printf("Coalesced into (%d, %d), %d x %d -> %f", coalesceRoi->x, 
                                                                     coalesceRoi->y, 
                                                                     coalesceRoi->width, 
                                                                     coalesceRoi->height, 
                                                                     score);

                    // remove the targetRoi
                    targetImage->rois.erase(targetImage->rois.begin() + j);
                    j--;
                }

            }
        }

        return images[targetIndex];
    }
}
