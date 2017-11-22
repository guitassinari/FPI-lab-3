#include <opencv2/opencv.hpp>
using namespace cv;

int kernelSize = 1;

void increaseKernelSize(int, void *){
  if(kernelSize % 2 == 0){
    kernelSize++;
  }
}

int main(int argc, char** argv)
{
  int camera = 0;
  VideoCapture cap;
  // open the default camera, use something different from 0 otherwise;
  // Check VideoCapture documentation.
  if(!cap.open(camera))
  return 0;
  namedWindow("Config", 1);
  namedWindow("Canny", 1);
  namedWindow("Sobel", 1);
  createTrackbar("TESTE", "Config", &kernelSize, 101, increaseKernelSize);
  for(;;)
  {
    Mat frame;
    Mat editedFrame;
    Mat cannyEdge;
    Mat gray;
    Mat grad, gradX, absGradX, gradY, absGradY;
    
    int ddepth = CV_16S;
    int scale = 1;
    int delta = 0;

    cap >> frame;
    if( frame.empty()){
      break;// end of video stream
    }

    cvtColor(frame, gray, CV_BGR2GRAY);

    /// Gradient X
    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel( gray, gradX, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( gradX, absGradX );

    /// Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( gray, gradY, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( gradY, absGradY );

    addWeighted( absGradX, 0.5, absGradY, 0.5, 0, grad );

    Canny(gray, cannyEdge, 50, 50, 3);
    GaussianBlur(frame, editedFrame, Size(kernelSize, kernelSize), 0, 0);
    imshow("Sobel", grad);
    imshow("Canny", cannyEdge);
    imshow("This is you, smile! :)", editedFrame);
    if(waitKey(1)==27){
      break;// stop capturing by pressing ESC
    }
  }
  cap.release();// release the VideoCapture object
  return 0;
}
