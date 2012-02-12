#ifndef SCORINGPROCESSOR_H_
#define SCORINGPROCESSOR_H_

#include <LabeledImage.h>
#include <Roi.h>

#include "ImageProcessor.h"
#include <vector>

using namespace std;

namespace Bioimagery {

    class ScoringProcessor : ImageProcessor {

    public:
        ScoringProcessor(vector<LabeledImage*> images, int targetIndex, vector<Roi*> targets);
        ScoringProcessor(LabeledImage **images, int numImages, int targetIndex, vector<Roi*> targets);

        virtual ~ScoringProcessor();

        // Runs image processing and returns the target image
        virtual LabeledImage* processImages();

        void scoreRois();
        void drawRois();

    private:

        void scoreRoi(Roi *targetRoi);

        vector<Roi*> rois;

    };

}

#endif /* SCORINGPROCESSOR_H_ */

