#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
Mat source, erosion_dst, dilation_dst, img_converted,src1, src2,src3;
 
//erosion/dilation
int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 1;
int const max_kernel_size = 100;


/** Function Headers */
void Erosion( int, void* );

/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  source = imread("face.jpeg");
 


 

  if( !source.data )
  { return -1; }

  /// Create windows
  namedWindow( "Erosion Demo", CV_WINDOW_AUTOSIZE );
  
 

 /// Create Erosion Trackbar
 

  createTrackbar( "Kernel size:\n 2n +1", "Erosion Demo",
                  &erosion_size, max_kernel_size,
                  Erosion );

  
 
/// Create a matrix 
 
  ///  start
  Erosion( 0, 0 );
  
  waitKey(0);
  return 0;
}

//Erosion 
void Erosion( int, void* )
{
  int erosion_type;
  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( erosion_type,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) );

  /// operation and show
  erode( source, erosion_dst, element );
  imshow( "Erosion Demo", erosion_dst );
 imwrite("erosion.jpg" ,erosion_dst);
}


