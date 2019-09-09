#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include "drawLandmarks.hpp"
//#include "genlandmask.hpp"

#include "stdio.h"

#define  D_USE_IPCAM  0
using namespace std;
using namespace cv;
using namespace cv::face;

char gc_landMaskInit = 0;

CascadeClassifier gm_faceDetector;
Ptr<Facemark> gm_facemark ;

void drawLandmarks(Mat &im, vector<Point2f> &landmarks)
{
	// Draw face for the 68-point model.
	if (landmarks.size() == 68)
	{
		drawPolyline(im, landmarks, 0, 16);           // Jaw line
		drawPolyline(im, landmarks, 17, 21);          // Left eyebrow
		drawPolyline(im, landmarks, 22, 26);          // Right eyebrow
		drawPolyline(im, landmarks, 27, 30);          // Nose bridge
		drawPolyline(im, landmarks, 30, 35, true);    // Lower nose
		drawPolyline(im, landmarks, 36, 41, true);    // Left eye
		drawPolyline(im, landmarks, 42, 47, true);    // Right Eye
		drawPolyline(im, landmarks, 48, 59, true);    // Outer lip
		drawPolyline(im, landmarks, 60, 67, true);    // Inner lip
	}
	else
	{ // If the number of points is not 68, we do not know which 
	  // points correspond to which facial features. So, we draw 
	  // one dot per landamrk. 
		for (int i = 0; i < landmarks.size(); i++)
		{
			circle(im, landmarks[i], 3, COLOR, FILLED);
		}
	}

}

bool landMaskInit()
{
	bool success = false;
	if (gc_landMaskInit)
	{
		printf("only need to init once\n");
		return false; 
	}
	// Load Face Detector
	success = gm_faceDetector.load("/Users/dengyan/Desktop/build/etc/haarcascades/haarcascade_frontalface_alt2.xml");
	if (success != true)
	{
		printf("haarcascade_frontalface_alt2.xml load fail\n");
		return false;
	}
	gm_facemark = FacemarkLBF::create();
	// Create an instance of Facemark
	// Load landmark detector
	 gm_facemark->loadModel("/Users/dengyan/Desktop/build/etc/lbfmodel.yaml");
	
	 return true;
	
}



bool landMaskGet(Mat frame, vector< vector<Point2f> > *landmarks)
{
	Mat gray;
	// Find face
	vector<Rect> faces;
	// Convert frame to grayscale because
	// faceDetector requires grayscale image.
	cvtColor(frame, gray, COLOR_BGR2GRAY);

	// Detect faces
	//faceDetector.detectMultiScale(gray, faces);
	gm_faceDetector.detectMultiScale(gray, faces,1.2, 10, CASCADE_SCALE_IMAGE, Size(50, 50), Size(500, 500));

	// Run landmark detector
	bool success = gm_facemark->fit(frame, faces, *landmarks);

	return true;
	   
}


