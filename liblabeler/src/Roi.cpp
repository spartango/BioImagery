#include "Roi.h"

namespace Bioimagery {

	Roi::Roi() {
		tags = NULL;
	}

	Roi::~Roi() {
		if(tags) {
			free(tags);
		}
	}

}