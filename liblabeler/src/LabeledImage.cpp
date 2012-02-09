#include "LabeledImage.h"
#include "util/CurlUtils.h"

#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"


using namespace cv;
using namespace rapidjson;

namespace Bioimagery {

    LabeledImage::LabeledImage(uint32_t t_id):
                              id(t_id),
                              image(NULL),
                              rois(NULL){

    }

    LabeledImage::~LabeledImage() {
        for(uint32_t i=0; i < rois.size(); i++) {
            delete rois[i];
        } 
        
        rois.clear();

        if(image != NULL) {
            cvReleaseImage(&image);
        }
    }

    void LabeledImage::load(string host) {
        loadMetadata(host);
        loadRois(host);
    }

    // Helpers
    void LabeledImage::loadMetadata(string host) {
        // URL: host/image/id/describe

        char url[host.length() + 23 + 10];
        sprintf(url, "http://%s/image/%u/describe", host.c_str(), id);
        const char* metadataJSON = curlGet(url).c_str();

        // Parse metadata
        Document document;
        if(document.Parse<0>(metadataJSON).HasParseError()) {
            // Failed to parse
            fprintf(stderr, "Error Parsing metadata JSON");
            return;
        }

        if(document.IsObject()
            && document.HasMember("filename")
            && document.HasMember("height")
            && document.HasMember("width")
            && document.HasMember("description")) {
            // We have all the necessary fields

            filename = document["filename"].GetString();
            height   = document["height"].GetUint();
            width    = document["width"].GetUint();

            if(!document["description"].IsNull()) {
                description = document["description"].GetString();
            } else {
                description = "";
            }

        } else {
            fprintf(stderr, "Image metadata is missing params");
        }

    }

    void LabeledImage::loadRois(string host) {
        // URL: host/image/id/rois

        char url[host.length() + 19 + 10];
        sprintf(url, "http://%s/image/%u/rois", host.c_str(), id);
        const char* roiJSON = curlGet(url).c_str();

        // Parse ROIs
        Document document;
        if(document.Parse<0>(roiJSON).HasParseError() || !document.IsArray()) {
            fprintf(stderr, "Error Parsing ROI JSON");
            return;
        }

        for(uint32_t i = 0; i < document.Size(); i++) {
            // Build an ROI
            Roi *roi = new Roi();
            roi->loadFromDocument(document[i]);
            rois.push_back(roi);
        }


    }

    void LabeledImage::loadImage(string host) {
        // URL: host/image/id
        if(image == NULL) {
            char url[host.length() + 14 + 10];
            sprintf(url, "http://%s/image/%u", host.c_str(), id);
            string curlBuffer = curlGet(url);

            // Make an imageheader
            CvMat* matbuf = cvCreateMat(1,curlBuffer.size(),CV_8UC1);

            memcpy(matbuf->data.ptr, curlBuffer.data(), curlBuffer.size());

            // Assign this to an image header
            image = cvDecodeImage(matbuf);

        }
    }

    void LabeledImage::unloadImage() {
        if(image != NULL) {
            cvReleaseImage(&image);
            image = NULL;
        }
    }

}