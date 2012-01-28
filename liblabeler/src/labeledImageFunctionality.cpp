#include "LabeledImage.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>

using namespace cv;
using namespace std;
using namespace Bioimagery;

int main(int, char*) {
  LabeledImage a = LabeledImage(1);
  a.load("proto.melamp.us");
  IplImage* img = a.image;
  cvShowImage("src",img);
}
