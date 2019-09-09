#ifndef _renderFace_H_
#define _renderFace_H_

using namespace cv; 
using namespace std; 

#define COLOR Scalar(255, 200,0)

// drawPolyLine draws a poly line by joining 
// successive points between the start and end indices. 
void drawPolyline
(
  Mat &im, 
  const vector<Point2f> &landmarks,
  const int start,
  const int end,
  bool isClosed = false
)
{
    // Gather all points between the start and end indices
    vector <Point> points;
    for (int i = start; i <= end; i++)
    {
        points.push_back(cv::Point(landmarks[i].x, landmarks[i].y));
    }
    // Draw polylines. 
    polylines(im, points, isClosed, COLOR, 2, 16);
    
}                         
  



#endif // _renderFace_H_