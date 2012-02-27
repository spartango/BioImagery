#include "ImageSequence.h"
#include "util/CurlUtils.h"

#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
 
namespace Bioimagery {
    ImageSequence::ImageSequence(uint32_t id): id(id) {

    }

    ImageSequence::~ImageSequence() {
        // Destroy all the nice images we've allocated
        for(uint32_t i=0; i < images.size(); i++) {
            delete images[i];
        } 
        
        images.clear();
    }

    void ImageSequence::load(string host) {
        loadMetadata(host);
    }

    // Helpers

    void ImageSequence::loadMetadata(string host) {
        // Curl out the metadata for this Id
        // Invoke the parser
        // Grab the metadata fields

        // URL: host/imageseq/id/describe

        char url[host.length() + 26 + 10];
        sprintf(url, "http://%s/imageseq/%u/describe", host.c_str(), id);
        const char* metadataJSON = curlGet(url).c_str();

        // Parse metadata
        Document document;
        if(document.Parse<0>(metadataJSON).HasParseError()) {
            // Failed to parse
            fprintf(stderr, "Error Parsing metadata JSON");
            return;
        }

        if(document.IsObject()
            && document.HasMember("delta")
            && document.HasMember("count")
            && document.HasMember("images")
            && document.HasMember("description")) {
            // We have all the necessary fields

            length = document["count"].GetUint();
            delta  = document["delta"].GetInt() / 1000.0;

            if(!document["description"].IsNull()) {
                description = document["description"].GetString();
            } else {
                description = "";
            }

            // Pull out the image list
            if(document["images"].IsArray()) {
                for(uint32_t i=0; i<length; i++) {
                    // Take the ID and make an object
                    LabeledImage *newImage = 
                            new LabeledImage(document["images"][i].GetUint());
                    // Take the object and load its metadata
                    newImage->load(host);
                    images.push_back(newImage);
                }
            }

        } else {
            fprintf(stderr, "Image metadata is missing params");
        }

    }


}