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

void Dilation( int, void* );


/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  source = imread("face.jpeg");
 
 

  if( !source.data )
  { return -1; }

  /// Create windows
 
  namedWindow( "Dilation ", CV_WINDOW_AUTOSIZE );
  

 

  /// Create Dilation Trackbar
  

  createTrackbar( "Kernel size:\n 2n +1", "Dilation ",
                  &dilation_size, max_kernel_size,
                  Dilation );

  ///  start
 
  Dilation( 0, 0 );

  waitKey(0);
  return 0;
}




// Dilation 
void Dilation( int, void* )
{
  int dilation_type;
  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( dilation_type,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );
  /// operation and show
  dilate( source, dilation_dst, element );
  imshow( "Dilation ", dilation_dst );
 imwrite("Dilation.jpg" ,dilation_dst);
}
  


