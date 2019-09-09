#ifndef _GENLANDMASK_H_
#define _GENLANDMASK_H_

using namespace cv;
using namespace std; 

void drawLandmarks(Mat &im, vector<Point2f> &landmarks);
bool landMaskInit();
bool landMaskGet(Mat frame, vector< vector<Point2f> > *landmarks);

#endif 
