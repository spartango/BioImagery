#include "LabeledImage.h"
#include "opencv2/core/core_c.h"

using namespace cv;

namespace Bioimagery {

	LabeledImage::LabeledImage(uint32_t t_id):id(t_id), image(NULL), rois(NULL){
		
	}

	LabeledImage::~LabeledImage() {
		if(rois != NULL) {
			delete rois;
		}
		if(image != NULL) { 
			cvReleaseImage(&image);
		}
	}

	void LabeledImage::load(string host) {
		
	}

	// Helpers
	void LabeledImage::loadMetadata() {
		
	}

	void LabeledImage::loadRois() {
		
	}

	void LabeledImage::loadImage() {
		
	}

}