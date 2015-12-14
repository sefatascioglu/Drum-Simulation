/*#include "opencv2/imgproc/imgproc.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "highgui.h"
 #include <iostream>
 #include <string>
 #include <stdio.h>
 #include <stdlib.h>
 #include "cv.h"
 #include "highgui.h"
 using namespace cv;*/
using namespace std;
#include <iostream>
#include <cv.h>
#include <highgui.h>
using namespace cv;

enum BAGET_COLOR{

	BLUE, RED
};

int playBattery();

CvSeq* findColor(IplImage* frame, BAGET_COLOR color);

void drawCircles(CvSeq* circles);

CvMemStorage* storage;

int main(int argc, char* argv[]) {

	playBattery();

	return 0;
}

void drawCircles(CvSeq* circles, Mat* final, BAGET_COLOR color){
	Scalar clr(0,0,0);
	if(color == BLUE){
		clr= Scalar(0, 0, 255);
	}
	else{
		clr= Scalar(255, 0, 0);
	}

	//draw circle!!
	for (int i = 0; i < circles->total; i++) {
		float* p = (float*) cvGetSeqElem(circles, i);

		if((p[0] > 0 && p[0] < 640)&&!(p[1] > 350 && p[1] < 480))
			circle(*final, Point(640-p[0], p[1]), p[2], clr, -1,8,0);

		/*printf("Ball! x=%f y=%f r=%f\n\r", p[0], p[1], p[2]);

		if((p[0] > 51 && p[0] < 180)&&(p[1] > 300 && p[1] < 375)){

			cout<<"abi ben 1. zilim"<<endl;
		}

		if((p[0] > 450 && p[0] < 631)&&(p[1] > 108 && p[1] < 276+108))
			cout<<"abi ben 2.zilim"<<endl;

		if((p[0] > 205 && p[0] < 300)&&(p[1] > 131+108 && p[1] < 223+108))
			cout<<"abi ben 1.davulum"<<endl;

		if((p[0] > 325 && p[0] < 430)&&(p[1] > 120+108 && p[1] < 210+108))
			cout<<"abi ben 2. davulum"<<endl;*/
	}
}

CvSeq* findColor(IplImage* frame, BAGET_COLOR color){
	CvSize size = cvSize(640, 480);
	int iLowH, iHighH, iLowS, iHighS, iLowV, iHighV;

	if (color == BLUE) {
		iLowH = 110;
		iHighH = 130;

		iLowS = 130;
		iHighS = 255;

		iLowV = 50;
		iHighV = 255;
	} else {
		iLowH = 120;
		iHighH = 179;

		iLowS = 111;
		iHighS = 255;

		iLowV = 109;
		iHighV = 255;
	}

	CvScalar hsv_min = cvScalar(iLowH, iLowS, iLowV, 0);
	CvScalar hsv_max = cvScalar(iHighH, iHighS, iHighV, 0);

	IplImage * hsv_frame = cvCreateImage(size, IPL_DEPTH_8U, 3);
	IplImage* thresholded = cvCreateImage(size, IPL_DEPTH_8U, 1);

	//cout << count << "--------------" << flag1 << endl;
	// Covert color space to HSV as it is much easier to filter colors in the HSV color-space.
	cvCvtColor(frame, hsv_frame, CV_BGR2HSV);
	// Filter out colors which are out of range.
	cvInRangeS(hsv_frame, hsv_min, hsv_max, thresholded);
	//cvInRangeS(hsv_frame, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), thresholded);
	// Memory for hough circles
	storage = cvCreateMemStorage(0);
	// hough detector works better with some smoothing of the image
	cvSmooth(thresholded, thresholded, CV_GAUSSIAN, 9, 9);
	CvSeq* circles = cvHoughCircles(thresholded, storage, CV_HOUGH_GRADIENT, 2,
			thresholded->height / 4, 100, 50, 10, 400);

	cvShowImage("After Color Filtering", thresholded);
	cvClearMemStorage(storage);

	return circles;
}


int playBattery()
{
	// Default capture size - 640x480
	// Open capture device. 0 is /dev/video0, 1 is /dev/video1, etc.
	CvCapture* capture = cvCaptureFromCAM(0);
	if (!capture) {
		fprintf(stderr, "ERROR: capture is NULL \n");
		getchar();
		return -1;
	}

	Mat bateriResim;
	bateriResim = imread("/home/sefatascioglu/Resimler/drumPic2.jpg");


	// Create a window in which the captured images will be presented
	cvNamedWindow("Camera", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("HSV", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("EdgeDetection", CV_WINDOW_AUTOSIZE);


	while (1) {
		// Get one frame
		IplImage* frame = cvQueryFrame(capture);

		if (!frame) {
			fprintf(stderr, "ERROR: frame is null...\n");
			getchar();
			break;
		}


		Mat final;

		// merge frame with bateri image
		Mat image = (Mat) frame;
		addWeighted(image, 0.1, bateriResim, 0.9, 0.0, final);

		//for things u know
		putText(final, "GROUP-8 DRUM MASTER", cvPoint(200,100),
		    FONT_HERSHEY_COMPLEX_SMALL, 0.9, cvScalar(150,200,250), 1.2, CV_AA);

		CvSeq* blues= findColor(frame, BLUE);
		drawCircles(blues, &final, BLUE);
		cvReleaseMemStorage(&storage);

		CvSeq* reds= findColor(frame, RED);
		drawCircles(reds, &final, RED);
		cvReleaseMemStorage(&storage);


		imshow("Final", final);

		cvShowImage("Camera", frame); // Original stream with detected ball overlay
		//cvShowImage("HSV", hsv_frame); // Original stream in the HSV color space
		//cvShowImage("After Color Filtering", thresholded); // The stream after color filtering
		// Do not release the frame!
		//If ESC key pressed, Key=0x10001B under OpenCV 0.9.7(linux version),
		//remove higher bits using AND operator
		if ((cvWaitKey(10) & 255) == 27)
			break;

	}
	// Release the capture device housekeeping
	cvReleaseCapture(&capture);
	cvDestroyWindow("mywindow");

return 0;
}

