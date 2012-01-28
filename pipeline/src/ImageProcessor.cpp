#include "ImageProcessor.h"
#include <LabeledImage.h>

using namespace std;

namespace Bioimagery {
	ImageProcessor::ImageProcessor(vector<LabeledImage> images,
                                   int targetIndex):
                                   images(images),
                                   targetIndex(targetIndex) {

    }
}