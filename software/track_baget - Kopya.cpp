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
/*using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <irrKlang.h>
//using namespace irrklang;
#include <opencv/cvaux.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
//#include <cv.h>
//#include <highgui.h>
using namespace cv;

int main(int argc, char* argv[]) {

    CvSize size = cvSize(640, 480);

	CvCapture* capture = cvCaptureFromCAM(0);
	if (!capture) {
		fprintf(stderr, "ERROR: capture is NULL \n");
		getchar();
		return -1;
    }

	cvNamedWindow("Camera", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("HSV", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("EdgeDetection", CV_WINDOW_AUTOSIZE);

	int iLowH = 110;
	int iHighH = 130;

	int iLowS = 130;
	int iHighS = 255;

	int iLowV = 50;
	int iHighV = 255;

	CvScalar hsv_min = cvScalar(iLowH, iLowS, iLowV, 0);
	CvScalar hsv_max = cvScalar(iHighH, iHighS, iHighV, 0);

	volatile bool flag1 = true;
	int count = 1;
	IplImage * hsv_frame = cvCreateImage(size, IPL_DEPTH_8U, 3);
	IplImage* thresholded = cvCreateImage(size, IPL_DEPTH_8U, 1);
	while (1) {
		// Get one frame
		IplImage* frame = cvQueryFrame(capture);
		if (!frame) {
			fprintf(stderr, "ERROR: frame is null...\n");
			getchar();
			break;
		}

		if (flag1) {

			iLowH = 110;
			iHighH = 130;

			iLowS = 130;
			iHighS = 255;

			iLowV = 50;
            iHighV = 255;

		} else {
			iLowH = 150;
			iHighH = 358;

			iLowS = 84;
			iHighS = 256;

			iLowV = 130;
			iHighV = 255;
		}
		hsv_min = cvScalar(iLowH, iLowS, iLowV, 0);
		hsv_max = cvScalar(iHighH, iHighS, iHighV, 0);

		if (count % 2 == 0)
			flag1 = false;
		else
			flag1 = true;
        ++count;

        cvCvtColor(frame, hsv_frame, CV_BGR2HSV);

        cvInRangeS(hsv_frame, hsv_min, hsv_max, thresholded);

		CvMemStorage* storage = cvCreateMemStorage(0);
		// hough detector works better with some smoothing of the image
		cvSmooth(thresholded, thresholded, CV_GAUSSIAN, 9, 9);
		CvSeq* circles =
				cvHoughCircles(thresholded, storage, CV_HOUGH_GRADIENT, 2,
						thresholded->height / 4, 100, 50, 10, 400);

		for (int i = 0; i < circles->total; i++) {
			float* p = (float*) cvGetSeqElem(circles, i);
			printf("Ball! x=%f y=%f r=%f\n\r", p[0], p[1], p[2]);

			if((p[0] > 51 && p[0] < 180)&&(p[1] > 300 && p[1] < 375)){

				cout<<"abi ben 1. zilim"<<endl;
			}

			if((p[0] > 450 && p[0] < 631)&&(p[1] > 108 && p[1] < 276+108))
				cout<<"abi ben 2.zilim"<<endl;

			if((p[0] > 205 && p[0] < 300)&&(p[1] > 131+108 && p[1] < 223+108))
				cout<<"abi ben 1.davulum"<<endl;

			if((p[0] > 325 && p[0] < 430)&&(p[1] > 120+108 && p[1] < 210+108))
                cout<<"abi ben 2. davulum"<<endl;

			Mat image = (Mat) frame;

			///TODO
			Mat src1,dst;
            src1 = imread("/home/sefatascioglu/Resimler/drumPic2.jpg");

			addWeighted(image, 0.1, src1, 0.9, 0.0, dst);
			if((p[0] > 0 && p[0] < 640)&&!(p[1] > 350 && p[1] < 480))
                circle(dst, Point(p[0], p[1]), p[2], Scalar(0, 255, 255), -1,8,0);

			putText(dst, "GROUP-8 DRUM MASTER", cvPoint(200,100),
			    FONT_HERSHEY_COMPLEX_SMALL, 0.9, cvScalar(150,200,250), 1.2, CV_AA);
			imshow("Image", dst);
		}
		cvShowImage("Camera", frame); // Original stream with detected ball overlay
		cvShowImage("HSV", hsv_frame); // Original stream in the HSV color space
		cvShowImage("After Color Filtering", thresholded); // The stream after color filtering
        cvReleaseMemStorage(&storage);
		if ((cvWaitKey(10) & 255) == 27)
			break;

    }

	cvReleaseCapture(&capture);
	cvDestroyWindow("mywindow");
	return 0;
}*/


