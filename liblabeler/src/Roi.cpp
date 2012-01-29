#include "Roi.h"
#include "util/CurlUtils.h"

namespace Bioimagery {

    Roi::Roi():
               id(0),
               x(0),
               y(0),
               height(0),
               width(0),
               confidence(0) {

    }

    Roi::Roi(uint32_t id,
             int32_t x,
             int32_t y,
             uint32_t height,
             uint32_t width,
             uint32_t confidence):
             id(id),
             x(x),
             y(y),
             height(height),
             width(width),
             confidence(confidence) {

    }

    Roi::~Roi() {

    }

    void Roi::loadTags(string host) {
        char url[host.length() + 17 + 10];
        sprintf(url, "http://%s/roi/%u/tags", host.c_str(), id);
        const char* tagJSON = curlGet(url).c_str();

        // Parse metadata
        Document document;
        if(document.Parse<0>(tagJSON).HasParseError() || !document.IsArray()) {
            // Failed to parse
            fprintf(stderr, "Error Parsing metadata JSON");
            return;
        }

        for(SizeType i = 0; i < document.Size(); i++) {
            tags.push_back(document[i].GetUint());
        }
    }

    void Roi::loadFromDocument(Value& document) {
        if(document.IsObject()
            && document.HasMember("id")
            && document.HasMember("height")
            && document.HasMember("width")
            && document.HasMember("x")
            && document.HasMember("y")
            && document.HasMember("confidence")) {

            id     = document["id"].GetInt();
            x      = document["x"].GetInt();
            y      = document["y"].GetInt();
            height = document["height"].GetUint();
            width  = document["width"].GetUint();

            if(!document["confidence"].IsNull()) {
                confidence = document["confidence"].GetUint();
            } else {
                confidence = 50;
            }

        }
    }
}