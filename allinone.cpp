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

//resizing
const int slider_max = 100;
int slider;
Mat img;

//lightning
Mat image;
int alpha = 1, beta = 0;
int alpha_MAX =1; 
int beta_MAX = 100; 

//unncanny edges
Mat src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
//blending
double al; 
double be;
const int blend_slider_max = 100;
int alpha_slider;
 int width1 , width2 , height1 , height2;

/** Function Headers */
void Erosion( int, void* );
void Dilation( int, void* );
void resizeing(int , void *);
void lightning(int, void*);
void edgedetection(int, void*);
void blend_trackbar( int , void* );


/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  source = imread("face.jpeg");
 src1 = imread("meta.jpeg");
 src2 = imread("face.jpeg");
 


 

  if( !source.data )
  { return -1; }

  /// Create windows
  namedWindow( "Erosion Demo", CV_WINDOW_AUTOSIZE );
  namedWindow( "Dilation ", CV_WINDOW_AUTOSIZE );
  namedWindow( "resizing", CV_WINDOW_AUTOSIZE );
 namedWindow("image", CV_WINDOW_AUTOSIZE);
namedWindow( "canny", CV_WINDOW_AUTOSIZE );
namedWindow("blending",CV_WINDOW_AUTOSIZE);
 

 /// Create Erosion Trackbar


  createTrackbar( "Kernel size:\n 2n +1", "Erosion Demo",
                  &erosion_size, max_kernel_size,
                  Erosion );

  /// Create Dilation Trackbar
 

  createTrackbar( "Kernel size:\n 2n +1", "Dilation ",
                  &dilation_size, max_kernel_size,
                  Dilation );
///  resizing Trackbar
     createTrackbar("Size", "resizing", &slider, slider_max, resizeing);


 

    // lightning trackbars
    createTrackbar("dark/lightning", "image", &beta, beta_MAX, lightning);
     createTrackbar("full Dark", "image", &alpha, alpha_MAX, lightning);
 
 
//  edge detectors
 
 createTrackbar( "Min Threshold:", "canny", &lowThreshold, max_lowThreshold, edgedetection ); 

//blend
 createTrackbar( "Blending", "blending", &alpha_slider, blend_slider_max, blend_trackbar );
 blend_trackbar( alpha_slider, 0 );
 
/// Create a matrix 
  dst.create( source.size(), source.type() );

  ///  image to grayscale
  cvtColor( source, src_gray, CV_BGR2GRAY );

  ///  start
  Erosion( 0, 0 );
  Dilation( 0, 0 );
resizeing(0,0);
lightning(0,0);
edgedetection(0, 0);
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
  
//resize func

void resizeing(int , void *)
{
    
    float scale = float(slider+50)/100;

     
    Size s(source.size().width*scale, source.size().height*scale);
    resize(source, img_converted, s);
    imshow("resizing", img_converted);
    imwrite("resized image.jpg" ,img_converted);
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

//edge func
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

void blend_trackbar( int , void* )
{
 al = (double) alpha_slider/blend_slider_max;
 be = (double)( 1.0 - al );
    addWeighted( src1, al, src2, be, 0.0, dst);
imshow( "blending", dst );
imwrite("blended.jpg" ,dst);
   
}

