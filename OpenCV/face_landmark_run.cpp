#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "facialLandmarkDetection.cpp"
#include <iostream>
#include <fstream>
#include <stdio.h>  


using namespace std;
using namespace cv;

#if 1
// Variable for landmarks. 
// Landmarks for one face is a vector of points
// There can be more than one face in the image. Hence, we 
// use a vector of vector of points. 
vector< vector<Point2f> > gv_landmarks;

int main(int argc, char** argv)
{
	bool success = false;
	
	
	if (argc != 2)
	{
	printf("usage: genlandmask  xxxx.jpg \n ");
	return 0;
	}

	string filename = argv[1];
	printf("filename=%s \n", argv[1]);

	success = landMaskInit();
	if (success != true)
	{
		printf("landMaskInit error\n");
		return -1;
	}
	Mat frame;
	frame = imread(filename);


	success = landMaskGet(frame, &gv_landmarks);


	if (success)
	{
		fstream outputFile;
		outputFile.open(filename + ".txt", ios::out);
		// If successful, render the landmarks on the face
		for (int i = 0; i < gv_landmarks.size(); i++)
		{
			drawLandmarks(frame, gv_landmarks[i]);

			for (int j = 0; j < gv_landmarks[i].size(); j++)
			{
				outputFile << (int)gv_landmarks[i][j].x << " " << (int)gv_landmarks[i][j].y << endl;
			}
		}
		outputFile.close();
	}



	// Display results 
	imshow("Facial Landmark Detection", frame);

	
	waitKey(0);


	vector< vector<Point2f> > tmp ;
	tmp.swap(gv_landmarks);


	exit(0);
}
#endif
