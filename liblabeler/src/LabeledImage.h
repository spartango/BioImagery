#ifndef LABELEDIMAGE_H_
#define LABELEDIMAGE_H_

#include <rapidjson/document.h>
#include "opencv2/core/core.hpp"

#include <string>

#include "Roi.h"

using namespace cv;
using namespace rapidjson;
using namespace std;

namespace Bioimagery { 
	
	class LabeledImage {

	public:
		LabeledImage(uint32_t t_id);
		virtual ~LabeledImage();
	
		/* data */
		uint32_t id;

		string filename;
		
		uint32_t height;
		uint32_t width;

		string description;

		IplImage *image;

		Roi *rois;

		// Populates this image from the host's db
		void load(string host);

	private:
		// Gets image metadata
		void loadMetadata();

		// Gets the Rois
		void loadRois();

		// Gets the image itself
		void loadImage();

		// deserialization  
		void metadataFromDocument(Document *doc);

		void imageFromBuffer(char *buffer);
	};

} /* namespace Bioimagery */


#endif /* LABELEDIMAGE_H_ */