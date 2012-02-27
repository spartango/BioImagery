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

        float delta;

        vector<LabeledImage*> images;

        void load(string host);

    private:
        // Gets sequence metadata
        void loadMetadata(string host);

        // Gets the images
        void loadLabeledImages(string host);

    };
}

#endif /* IMAGESEQUENCE_H_ */
