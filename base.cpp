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
  createTrackbar("TESTE", "Config", &kernelSize, 101, increaseKernelSize);
  for(;;)
  {
    Mat frame;
    Mat editedFrame;
    Mat cannyEdge;
    Mat gray;



    cap >> frame;
    if( frame.empty()){
      break;// end of video stream
    }

    cvtColor(frame, gray, CV_BGR2GRAY);

    Canny(gray, cannyEdge, 50, 50, 3);
    GaussianBlur(frame, editedFrame, Size(kernelSize, kernelSize), 0, 0);
    imshow("Canny", cannyEdge);
    imshow("This is you, smile! :)", editedFrame);
    if(waitKey(1)==27){
      break;// stop capturing by pressing ESC
    }
  }
  cap.release();// release the VideoCapture object
  return 0;
}
