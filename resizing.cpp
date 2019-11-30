#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
Mat source, erosion_dst, dilation_dst, img_converted,src1, src2,src3;
 


//resizing
const int slider_max = 100;
int slider;
Mat img;


/** Function Headers */

void resizeing(int , void *);


/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  source = imread("face.jpeg");
 

 

  if( !source.data )
  { return -1; }

  /// Create windows
  
  namedWindow( "resizing", CV_WINDOW_AUTOSIZE );


 
///  resizing Trackbar
     createTrackbar("Size", "resizing", &slider, slider_max, resizeing);


 

   
 

resizeing(0,0);

  waitKey(0);
  return 0;
}


  
//resize func

void resizeing(int , void *)
{
    
    float scale = float(slider+50)/100;

     
    Size s(source.size().width*scale, source.size().height*scale);
    resize(source, img_converted, s);
    imshow("resizing", img_converted);
    imwrite("resized image.jpg" ,img_converted);
}


