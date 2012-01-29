#ifndef ROI_H_
#define ROI_H_

#include <rapidjson/document.h>
#include <string>
#include <vector>

using namespace rapidjson;
using namespace std;

namespace Bioimagery {

    class Roi {

    public:
        Roi();
        Roi(uint32_t id,
            int32_t x,
            int32_t y,
            uint32_t height,
            uint32_t width,
            uint32_t confidence);

        virtual ~Roi();

        /* data */
        uint32_t id;

        int32_t x;
        int32_t y;

        uint32_t height;
        uint32_t width;

        uint32_t confidence;

        // Tag ids
        vector<uint32_t> tags;

        void loadTags(string host);

        /* deserialization */
        void loadFromDocument(Value& obj);

        /* serialization */
        string toJSON();
    };

} /* namespace Bioimagery */


#endif /* ROI_H_ */
