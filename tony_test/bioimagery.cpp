/*
 * Currently following this link to work on simple techniques:
 *
 * http://www.discover.uottawa.ca/~qchen/my_presentations/A%20Basic%20Introduction%20to%20OpenCV%20for%20Image%20Processing.pdf
 */
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
int main()
{
  IplImage* newImg = NULL;
  IplImage* grayImg = NULL;
  IplImage* contourImg = NULL;
  //parameters for the contour detection
  CvMemStorage * storage = cvCreateMemStorage(0);
  CvSeq * contour = 0;
  int mode = CV_RETR_EXTERNAL;
  mode = CV_RETR_CCOMP; //detect both outside and inside contour
  cvNamedWindow("src", 1);
  cvNamedWindow("contour",1);
  //load original image
  newImg = cvLoadImage("AlignedHiResStack_2_6_2011_00.tif",1);
  //create a single channel 1 byte image (i.e. gray-level image)
  grayImg = cvCreateImage( cvSize(newImg->width, newImg->height), IPL_DEPTH_8U, 1 );
  //convert original color image (3 channel rgb color image) to gray-level image
  cvCvtColor( newImg, grayImg, CV_BGR2GRAY );
  cvShowImage( "src", newImg );
  //make a copy of the original image to draw the detected contour
  contourImg = cvCreateImage(cvGetSize(newImg), IPL_DEPTH_8U, 3);
  contourImg=cvCloneImage( newImg );
  //find the contour
  cvFindContours(grayImg, storage, &contour, sizeof(CvContour), mode, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
  //draw the contour
  cvDrawContours(contourImg, contour, CV_RGB(0, 255, 0), CV_RGB(255, 0, 0), 2, 2, 8);
  cvShowImage( "contour", contourImg );
  cvWaitKey(0);
  cvDestroyWindow( "src" );  cvDestroyWindow( "contour" );
  cvReleaseImage( &newImg );   cvReleaseImage( &grayImg );  cvReleaseImage( &contourImg );
  cvReleaseMemStorage(&storage);
  return 0;
}
