#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "facialLandmarkDetection.cpp"
#include "face_swap.cpp"

#define CVUI_IMPLEMENTATION
#include "cvui.h"

using namespace std;
using namespace cv;

#define WINDOW1_NAME "Window 1"

void detectAndDisplay(Mat frame);

/** Global variables */

String face_cascade_name = "/Users/dengyan/Desktop/build/etc/haarcascades/haarcascade_frontalface_alt2.xml";

String eyes_cascade_name = "/Users/dengyan/Desktop/build/etc/haarcascades/haarcascade_eye.xml";

CascadeClassifier face_cascade;   //定义人脸分类器
CascadeClassifier eyes_cascade;   //定义人眼分类器  cd
String window_name = "Capture - Face detection";

vector< vector<Point2f> > gv_landmarks;
bool success = false;

void mapToMat(const cv::Mat &srcAlpha, cv::Mat &dest, int x, int y)
{
    int nc = 3;
    int alpha = 0;

    for (int j = 0; j < srcAlpha.rows; j++)
    {
        for (int i = 0; i < srcAlpha.cols * 3; i += 3)
        {
            alpha = srcAlpha.ptr<uchar>(j)[i / 3 * 4 + 3];

            if (alpha != 0) //4通道图像的alpha判断
            {
                for (int k = 0; k < 3; k++)
                {
                    // if (src1.ptr<uchar>(j)[i / nc*nc + k] != 0)
                    if ((j + y < dest.rows) && (j + y >= 0) &&
                        ((i + x * 3) / 3 * 3 + k < dest.cols * 3) && ((i + x * 3) / 3 * 3 + k >= 0) &&
                        (i / nc * 4 + k < srcAlpha.cols * 4) && (i / nc * 4 + k >= 0))
                    {
                        dest.ptr<uchar>(j + y)[(i + x*nc) / nc*nc + k] = srcAlpha.ptr<uchar>(j)[(i) / nc * 4 + k];
                    }
                }
            }
        }
    }
}

Mat hatAlpha;
Mat hatAlpha1;
Mat * hat;

double distance(vector<Point2f> &point, double &x, double &y) {
    //左眼中心坐标 36和39
    x = (point[39].x + point[36].x) / 2;
    y = (point[39].y + point[36].y) / 2;
    //右眼 42和45
    return (point[45].x + point[42].x) / 2 - x;
}

int isStop;
Mat lastframe;

int main() {
    cvui::init("123");

    // Create a frame
    cv::Mat frame = cv::Mat(cv::Size(400, 200), CV_8UC3);

    VideoCapture capture;
    capture.open("../cctv.mp4");

    Mat start = imread("../start.png");
    resize(start, start, Size(25, 25));
    Mat stop = imread("../stop.png");
    resize(stop, stop, Size(25, 25));
    Mat forward = imread("../forward.png");
    resize(forward, forward, Size(25, 25));
    Mat back = imread("../back.png");
    resize(back, back, Size(25, 25));

    Mat * state = &start;

    double end = capture.get(CAP_PROP_FRAME_COUNT) / 25 / 60; //为几点几分钟
    int endm = (int)end;
    int ends = (int)((end - endm) * 60);

    double value = 0;
    const char *theLabelFormat = "%.2Lf";

    char buf[30];


    while (isStop || capture.read(frame)) {
        if (!isStop)
            lastframe = frame.clone();
        if (isStop) {
            frame = lastframe.clone();
        }

        cv::Rect rectangle(0, frame.rows - 72, frame.cols, 72);
        cvui::rect(frame, rectangle.x, rectangle.y, rectangle.width, rectangle.height, 0xff0000);

        int status = cvui::iarea(rectangle.x, rectangle.y, rectangle.width, rectangle.height);

        switch (status) {
            case cvui::CLICK:;
            case cvui::DOWN:;
            case cvui::OVER: {
                if (cvui::button(frame, frame.cols * 0.5 - 12.5, frame.rows - 40, *state, *state, *state)) {
                    isStop = !isStop; //需要处理重复打画的问题
                    state = state==&start?&stop:&start;
                }
                if (cvui::button(frame, frame.cols * 0.5 + 100, frame.rows - 40, forward, forward, forward)) {
                    capture.set(CAP_PROP_POS_FRAMES , capture.get(CAP_PROP_POS_FRAMES) + 25 * 15);
                    capture.read(lastframe);
                }
                if (cvui::button(frame, frame.cols * 0.5 - 125, frame.rows - 40, back, back, back)) {
                    int cur = capture.get(CAP_PROP_POS_FRAMES) - 25 * 15;
                    capture.set(CAP_PROP_POS_FRAMES , cur<0?0:cur);
                    capture.read(lastframe);
                }
                cvui::printf(frame, 240, 70, "Mouse is: OVER");
                value = capture.get(CAP_PROP_POS_FRAMES) / 25 / 60;
                int curm = (int)value;
                int curs = int((value - curm) * 60);
                sprintf(buf, "%02d:%02d/%02d:%02d", curm, curs, endm, ends);
                if (cvui::trackbar(frame, 0, frame.rows - 79, frame.cols, &value, 0.0, end, 1, theLabelFormat, cvui::TRACKBAR_HIDE_LABELS|cvui::TRACKBAR_HIDE_VALUE_LABEL)) {
                    cv::Rect rec(frame.cols * 0.5 - 50, frame.rows * 0.5 - 20, 100, 40);
                    cvui::rect(frame, rec.x, rec.y, rec.width, rec.height, 0x333333, 0x33000000);
                    curm = (int)value;
                    curs = int((value - curm) * 60);
                    sprintf(buf, "%02d:%02d/%02d:%02d", curm, curs, endm, ends);
                    cvui::text(frame, frame.cols * 0.5 - 38, frame.rows * 0.5 - 5, buf);
                    capture.set(CAP_PROP_POS_FRAMES, value * 25 * 60);
                    if (isStop)
                        capture.read(lastframe);
                }
                cvui::text(frame, frame.cols * 0.02, frame.rows - 36, buf);
                break;
            }
            case cvui::OUT:	break;
        }

        // Show the coordinates of the mouse pointer on the screen
        //cvui::printf(frame, 240, 50, "Mouse pointer is at (%d,%d)", cvui::mouse().x, cvui::mouse().y);

        // This function must be called *AFTER* all UI components. It does
        // all the behind the scenes magic to handle mouse clicks, etc.
        cvui::update();

        // Show everything on the screen
        cv::imshow("123", frame);

        // Check if ESC key was pressed
        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}

/*
          value = capture.get(CAP_PROP_POS_FRAMES) / 25 / 60;
        if (cvui::trackbar(frame, 0, frame.rows * 0.93, frame.cols, &value, 0.0, end, 1, theLabelFormat, cvui::TRACKBAR_HIDE_LABELS|cvui::TRACKBAR_HIDE_VALUE_LABEL)) {
            cvui::text(frame, 30, 40, "1");
            capture.set(CAP_PROP_POS_FRAMES, value * 25 * 60);
        }
 */

void detectAndDisplay(Mat frame1)
{
    std::vector<Rect> faces;
    Mat frame_gray;

    success = landMaskGet(frame1, &gv_landmarks);


    cvtColor(frame1, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //-- Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.2, 10, CASCADE_SCALE_IMAGE, Size(50, 50), Size(500, 500));

    for (size_t i = 0; i < faces.size(); i++)
    {
        //Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        //ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
        //rectangle(frame1, faces[i], Scalar(255, 0, 0), 2, 8, 0);

        Mat faceROI = frame_gray(faces[i]);

        rectangle(frame1, faces[i], Scalar(255, 0, 0), 2, 8, 0);

        if (hat) {
            resize(*hat, hatAlpha, Size(faces[i].width*1.3, faces[i].height), 0, 0, INTER_LANCZOS4);
            mapToMat(*hat, frame1, faces[i].x - faces[i].width*(0.3 / 2), faces[i].y - 0.6*faces[i].height);
        }
    }
    if (success)
    {
        for (int i = 0; i < gv_landmarks.size(); i++)
        {
            drawLandmarks(frame1, gv_landmarks[i]);
        }
    }
    namedWindow(window_name, 2);
    imshow(window_name, frame1);
}
