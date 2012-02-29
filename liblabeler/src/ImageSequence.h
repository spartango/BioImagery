#ifndef IMAGESEQUENCE_H_
#define IMAGESEQUENCE_H_

#include <rapidjson/document.h>
#include "opencv2/core/core.hpp"

#include <string>

using namespace cv;
using namespace rapidjson;
using namespace std;

#include "LabeledImage.h"

namespace Bioimagery {
    class ImageSequence {

    public:
        ImageSequence(uint32_t id);
        ~ImageSequence();
    
        /* data */
        uint32_t id;

        string description;

        // This is the change in time or space between the images
        double   delta;
        uint32_t length;

        vector<LabeledImage*> images;

        void load(string host);

    private:
        // Gets sequence metadata
        void loadMetadata(string host);

        
    };
}

#endif /* IMAGESEQUENCE_H_ */
