#include "LabeledImage.h"
#include "opencv2/core/core_c.h"
#include <curl/curl.h>

using namespace cv;
using namespace rapidjson;

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

    // CURL buffer
    static string curlBuffer;  
      
    // Callback function for CURL 
    static size_t curlWriter(char *data, size_t size, size_t nmemb,  
                      string *buffer)  
    {  
        // Append the data to the buffer    
        buffer->append(data, size * nmemb);  
        
        return size * nmemb;  
    }  

    static const char* curlGet(char* url) {
        CURL *curl;
        CURLcode res;

        curl = curl_easy_init();
        
        // Clear the curl buffer
        curlBuffer.clear();
        
        if(curl) {  
            curl_easy_setopt(curl, CURLOPT_URL, url);  
            curl_easy_setopt(curl, CURLOPT_HEADER, 0);  
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);  
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriter);  
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);             

            res = curl_easy_perform(curl);
            if(res) {
                // Return the data
            } else {
                // Something went wrong getting the data
                fprintf(stderr, "Error GETing URL: %s -> %i \n", url, res);
            }
            
            curl_easy_cleanup(curl);
        }
        
        return curlBuffer.c_str();

    }

    // Helpers
    void LabeledImage::loadMetadata(string host) {
        // URL: host/image/id/describe

        char url[host.length() + 23 + 10];
        sprintf(url, "http://%s/image/%u/describe", host.c_str(), id);
        const char* metadataJSON = curlGet(url);
        
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

            filename    = document["filename"].GetString();
            height      = document["height"].GetUint();
            width       = document["width"].GetUint();
            description = document["description"].GetString();
        
        } else {
            fprintf(stderr, "Image metadata is missing params");
        }

    }

    void LabeledImage::loadRois(string host) {
        // URL: host/image/id/rois
        
        char url[host.length() + 19 + 10];
        sprintf(url, "http://%s/image/%u/rois", host.c_str(), id);
        const char* roiJSON = curlGet(url);

        // Parse ROIs
        Document document;
        if(document.Parse<0>(roiJSON).HasParseError()) {
            fprintf(stderr, "Error Parsing ROI JSON");
            return;
        } 
        
        // Build a bunch of ROIs
        if(document.IsArray()) {
            for(SizeType i = 0; i < document.Size(); i++) {
                // Build an ROI 
                
            }
        }
        
    }

    void LabeledImage::loadImage(string host) {
        // URL: host/image/id

        char url[host.length() + 14 + 10];
        sprintf(url, "http://%s/image/%u", host.c_str(), id);
        const char* imageBuffer = curlGet(url);

        // Make an imageheader

        // Assign this to an image header
    }

}