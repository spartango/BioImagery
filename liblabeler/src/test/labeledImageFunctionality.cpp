#include "../LabeledImage.h"
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
  printf("Got Image Metadata: %d x %d \n", a.height, a.width);

  a.loadImage("proto.melamp.us");
  printf("Got Image: %dB \n", a.image->imageSize);

  a.unloadImage();
  printf("Unloaded image: %p \n", a.image);

  a.loadImage("proto.melamp.us");
  printf("Got Image: %dB \n", a.image->imageSize);

  cvShowImage("src",a.image);
  cvWaitKey();

}