#include <LabeledImage.h>
#include <ImageSequence.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>

using namespace cv;
using namespace std;
using namespace Bioimagery;

void testSingleImage() {
  LabeledImage a(1);
  a.load("localhost:8080");
  printf("Got Image Metadata: %d x %d \n", a.height, a.width);

  a.loadImage("localhost:8080");
  printf("Got Image: %dB \n", a.image->imageSize);

  a.unloadImage();
  printf("Unloaded image: %p \n", a.image);

  a.loadImage("localhost:8080");
  printf("Got Image: %dB \n", a.image->imageSize);

  //cvShowImage("src",a.image);
  //cvWaitKey(); 
}

void testSequence() {
  ImageSequence seq(1); 
  seq.load("localhost:8080");
  printf("Got sequence metadata: %d images, delta: %f -> %s", seq.length, seq.delta, seq.description.c_str());

  LabeledImage *seqImage = seq.images[0];
  seqImage->loadImage("localhost:8080");

  printf("Got Sequence Image Metadata: %d x %d \n", seqImage->height, seqImage->width);
  cvShowImage("src", seqImage->image);
  cvWaitKey(); 
}

int main(int, char*) {
  testSingleImage();
  testSequence();
}

