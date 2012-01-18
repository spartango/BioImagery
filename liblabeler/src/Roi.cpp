#include "Roi.h"

namespace Bioimagery {

    Roi::Roi():tags(NULL) {
        
    }

    Roi::~Roi() {
        if(tags != NULL) {
            delete tags;
        }
    }

    void Roi::loadTags(string host) {
        
    }

    void Roi::loadFromDocument(Document *doc) {
        
    }
}