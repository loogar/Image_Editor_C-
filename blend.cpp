#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
Mat source, dst, erosion_dst, dilation_dst, img_converted,src1, src2,src3;
 

//blending
double al; 
double be;
const int blend_slider_max = 100;
int alpha_slider;
 int width1 , width2 , height1 , height2;

/** Function Headers */

void blend_trackbar( int , void* );


/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  
 src1 = imread("meta.jpeg");
 src2 = imread("face.jpeg");
 


 

  if( !src1.data )
  { return -1; }

  /// Create windows
 
namedWindow("blending",CV_WINDOW_AUTOSIZE);
 

 
//blend
 createTrackbar( "Blending", "blending", &alpha_slider, blend_slider_max, blend_trackbar );
 blend_trackbar( alpha_slider, 0 );
 

  waitKey(0);
  return 0;
}



void blend_trackbar( int , void* )
{
 al = (double) alpha_slider/blend_slider_max;
 be = (double)( 1.0 - al );
    addWeighted( src1, al, src2, be, 0.0, dst);
imshow( "blending", dst );
imwrite("blended.jpg" ,dst);
   
}

