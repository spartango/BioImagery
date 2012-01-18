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
		loadMetadata(host);
		loadRois(host);
		loadImage(host);	
	}

	// Helpers
	void LabeledImage::loadMetadata(string host) {
		
	}

	void LabeledImage::loadRois(string host) {
		
	}

	void LabeledImage::loadImage(string host) {
		
	}

}