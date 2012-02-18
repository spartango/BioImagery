#include "CannyEdgeProcessor.h"
#include <LabeledImage.h>
#include <opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

namespace Bioimagery {

    CannyEdgeProcessor::CannyEdgeProcessor(vector<LabeledImage*> images, 
                                 int targetIndex, 
                                 int aperture_size, 
                                 double low_thresh,
                                 double high_thresh) : ImageProcessor(images, targetIndex),
                                                       aperture_size(aperture_size), 
                                                       low_thresh(low_thresh), 
                                                       high_thresh(high_thresh){
    }

    CannyEdgeProcessor::CannyEdgeProcessor(LabeledImage** images, 
                                 int numImages,
                                 int targetIndex, 
                                 int aperture_size, 
                                 double low_thresh,
                                 double high_thresh) : ImageProcessor(images, numImages, targetIndex),
                                                       aperture_size(aperture_size), 
                                                       low_thresh(low_thresh), 
                                                       high_thresh(high_thresh){
    }

    CannyEdgeProcessor::~CannyEdgeProcessor() {
      
    }

    LabeledImage* CannyEdgeProcessor::processImages() {
        // Make sure we load the target image
        images[targetIndex]->loadImage("proto.melamp.us");
      	// Apply Canny Edge detection (cannot be in-place)
      	IplImage *orig = images[targetIndex]->image;
      	IplImage *copy = cvCreateImage( cvSize(orig->width,orig->height),
                                                  IPL_DEPTH_8U, 1 );
      	cvCvtColor(orig, copy, CV_RGB2GRAY);
      	
        // cvCopy(orig, copy, 0);
        cvCanny(copy, copy, low_thresh, high_thresh, aperture_size);
              
      	images[targetIndex]->image = copy;
      	cvReleaseImage(&orig);

        return images[targetIndex];
    }
}
