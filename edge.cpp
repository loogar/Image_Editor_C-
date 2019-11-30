#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
Mat source, erosion_dst, dilation_dst, img_converted,src1, src2,src3;
 


//unncanny edges
Mat src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;

/** Function Headers */

void edgedetection(int, void*);


/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  source = imread("face.jpeg");
 


 

  if( !source.data )
  { return -1; }

  /// Create windows
  
namedWindow( "canny", CV_WINDOW_AUTOSIZE );


 
    
 
//  edge detectors
 
 createTrackbar( "Min Threshold:", "canny", &lowThreshold, max_lowThreshold, edgedetection ); 


 
/// Create a matrix 
  dst.create( source.size(), source.type() );

  ///  image to grayscale
  cvtColor( source, src_gray, CV_BGR2GRAY );

  ///  start
 
edgedetection(0, 0);
  waitKey(0);
  return 0;
}


void edgedetection(int, void*)
{
   /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );

  /// Using Canny's output as a mask to display  result
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

 
  dst = Scalar::all(20);

  source.copyTo( dst, detected_edges);

imshow( "canny", dst );
imwrite("canny.jpg" ,dst);
 }



