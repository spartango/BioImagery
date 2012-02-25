#include "GPreProcessor.h"
#include <LabeledImage.h>
#include <opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

namespace Bioimagery {

    GPreProcessor::GPreProcessor(vector<LabeledImage*> images, 
                                 int targetIndex, 
                                 int filter_width, 
                                 int filter_height, 
                                 double sigma_x,
                                 double sigma_y) : ImageProcessor(images, targetIndex),
                                                   filter_width(filter_width), 
                                                   filter_height(filter_height), 
                                                   sigma_x(sigma_x), 
                                                   sigma_y(sigma_y){

    }

    GPreProcessor::GPreProcessor(LabeledImage** images, 
                                 int numImages,
                                 int targetIndex, 
                                 int filter_width, 
                                 int filter_height, 
                                 double sigma_x,
                                 double sigma_y) : ImageProcessor(images, numImages, targetIndex),
                                                   filter_width(filter_width), 
                                                   filter_height(filter_height), 
                                                   sigma_x(sigma_x), 
                                                   sigma_y(sigma_y){

    }

    GPreProcessor::~GPreProcessor() {
      
    }

    LabeledImage* GPreProcessor::processImages() {
        // Make sure we load the target image
        images[targetIndex]->loadImage("proto.melamp.us");
        
        // Gaussian Smooth the target image
        cvSmooth(images[targetIndex]->image, images[targetIndex]->image, CV_GAUSSIAN, filter_width, filter_height, sigma_x, sigma_y);
        
        return images[targetIndex];
    }
}