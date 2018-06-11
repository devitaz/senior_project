#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

/** Function Headers */
void obstacleDetect(Mat frame);

int main(int argc, char **argv)
{
	// 	Get video frame 
	/*
	Mat frame;
	
	while (1) {
		capture >> frame;
		if (frame.empty()) {
			printf(" --(!) No captured frame -- Break!");
			break;
		}
		obstacleDetect(frame);
		
		int c = waitKey(10);
		if ((char)c == 27) { break; } // escape
	}
	waitKey(0);
	*/
	
	//	 Import image
	frame = imread("images/blackrock.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	obstacleDetect(frame);
}
void obstacleDetect(Mat frame) {
	Mat blurred, gray, canny;

	//	Convert image to Grayscale
	cvtColor(frame, gray, CV_BGR2GRAY);

	//	Smoothing image
	blur(frame, blurred, Size(5, 5));	// Original: (40, 4)

	//	Morphological opening (remove small objects from the foreground)
	erode(blurred, blurred, getStructuringElement(MORPH_RECT, Size(5, 5)));
	dilate(blurred, blurred, getStructuringElement(MORPH_RECT, Size(5, 5)));
	dilate(blurred, blurred, getStructuringElement(MORPH_RECT, Size(5, 5)));

	//	Canny Edge detection algorithm
	Canny(blurred, canny, 50, 120, 3);

	//	Display Images with filters
	imshow("Canny", canny(Rect(0, 0, canny.rows, canny.rows)));
	imshow("Blurred", blurred(Rect(0, 0, canny.rows, canny.rows)));
	imshow("Grayscale", gray(Rect(0, 0, canny.rows, canny.rows)));
	imshow("Original", frame(Rect(0, 0, canny.rows, canny.rows)));
}	
		