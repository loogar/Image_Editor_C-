#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
Mat source, erosion_dst, dilation_dst, img_converted,src1, src2,src3;
 

//lightning
Mat image;
int alpha = 1, beta = 0;
int alpha_MAX =1; 
int beta_MAX = 100; 



/** Function Headers */

void lightning(int, void*);


/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  source = imread("face.jpeg");
 
//source = imread("meta.jpeg");
 

 

  if( !source.data )
  { return -1; }

  /// Create windows
  
 namedWindow("image", CV_WINDOW_AUTOSIZE);


 

 

    // lightning trackbars
    createTrackbar("dark/lightning", "image", &beta, beta_MAX, lightning);
     createTrackbar("full Dark", "image", &alpha, alpha_MAX, lightning);
 


  ///  start
  
lightning(0,0);

  waitKey(0);
  return 0;
}


//light func
void lightning(int, void*)
{
    Mat new_image;
  //Adjust the Gain light and dark parameters 
    source.convertTo(new_image, -1, alpha, beta);
 
    imshow("image", new_image); 
imwrite("light effectes image.jpg" , new_image);
}


