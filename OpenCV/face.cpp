#if 1

#include <opencv2/opencv.hpp>
#include <iostream>
# include <deque>
#include <stdio.h>  

using namespace std;
using namespace cv;

#define D_USE_IPCAM 1


/** Function Headers */
void detectAndDisplay(Mat frame,double );

/** Global variables */
//String face_cascade_name = "/Users/dengyan/Desktop/build/etc/haarcascades/haarcascade_frontalface_alt_tree.xml";
//String face_cascade_name = "/Users/dengyan/Desktop/build/etc/haarcascades/haarcascade_frontalface_alt.xml";
String face_cascade_name = "/Users/dengyan/Desktop/build/etc/haarcascades/haarcascade_frontalface_alt2.xml";
//String face_cascade_name = "/Users/dengyan/Desktop/build/etc/haarcascades/haarcascade_frontalcatface.xml";


//String eyes_cascade_name = "/Users/dengyan/Desktop/build/etc/haarcascades/haarcascade_lefteye_2splits.xml";
String eyes_cascade_name = "/Users/dengyan/Desktop/build/etc/haarcascades/haarcascade_eye.xml";
//String eyes_cascade_name = "/Users/dengyan/Desktop/build/etc/haarcascades/haarcascade_eye_tree_eyeglasses.xml";

CascadeClassifier face_cascade;   //定义人脸分类器  
CascadeClassifier eyes_cascade;   //定义人眼分类器  
String window_name = "Capture - Face detection";
String window_picture = "picture";

int gray[255];
int forgray[255];

void calgray(Mat &photo) {
    for (int i = 0; i < photo.rows; i++)
        for (int j = 0; j < photo.cols; j++)
            forgray[photo.at<uchar>(i, j)]++;
}

double ans = 0;

double rate = 0.15;

int flag = 0;

bool judge(int * fp, int sum) {
    ans = 0;
    for (int i = 0; i < 255; i++) {
        ans += abs(fp[i] - gray[i]);
    }
    ans /= sum;
    if (ans > rate) //两张图的变化大于0.2
        return true;

    cout << rate << " " << ans << endl;
    return false;
}

int main(void)
{
	Mat frame = imread("../meeting.jpg");
	bool ret = false;

	//Mat frame;  

	//-- 1. Load the cascades  
	ret = face_cascade.load(face_cascade_name);
	if (!ret){ printf("--(!)Error loading face cascade\n"); return -1; };

	ret = eyes_cascade.load(eyes_cascade_name);
	if (!ret){ printf("--(!)Error loading eyes cascade\n"); return -1; };

#if D_USE_IPCAM
	//-- 2. Read the video stream 
	VideoCapture capture;
	capture.open("../cctv.mp4");
	if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }

    //capture.set(CAP_PROP_POS_FRAMES,1200 * 30);
	capture.set(CAP_PROP_POS_MSEC, 40 * 1000);

	while (capture.read(frame))
#endif
	{
		if (frame.empty())
		{
			printf(" --(!) No captured frame -- Break!");
			return -1;
		}
		double a = capture.get(CAP_PROP_POS_FRAMES);
		//-- 3. Apply the classifier to the frame  
		detectAndDisplay(frame, a);

#if D_USE_IPCAM
		int c = waitKey(30);
#else
		int c = waitKey(0);
#endif
		if ((char)c == 27) { return 0; } // escape  
	}
	return 0;
}

/** @function detectAndDisplay */

int n = 0;


void detectAndDisplay(Mat frame1,double f)
{
	Mat frame_gray;
    std::vector<Rect> faces;

	cvtColor(frame1, frame_gray, COLOR_BGR2GRAY);

    memset(forgray, 0, sizeof(forgray));
    calgray(frame_gray);

    equalizeHist(frame_gray, frame_gray);

    //-- Detect faces

    face_cascade.detectMultiScale(frame_gray, faces, 1.2, 10, CASCADE_SCALE_IMAGE, Size(50, 50), Size(500, 500));

	for (size_t i = 0; i < faces.size(); i++)
	{
		//Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);  
		//ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		rectangle(frame1, faces[i], Scalar(255, 0, 0), 2, 8, 0);

	}

	if (flag == 1) { //若刚刚以及截图并保存了
	    if (rate >= 0.15) {
            rate *= 0.99;
            if (faces.empty()) //如果没有检测到人，让阀值更快下降
                rate -= 0.01 * ans;
            else //如果和上一次截图差不多，那么增加rate，如果差别相差大于0.3，则可以加速rate下降
                rate += 0.001 * (0.3 - ans);
	    }
        else
            flag = 0;
	}


	if (!faces.empty()) {
        if (judge(forgray, frame_gray.rows * frame_gray.cols)) {
                rate = 0.4; //由于此时截图了一次，不想让其再短时间之内再截图一次，提高阀值
                flag = 1;
                cout << "write" << endl;
                memcpy(gray, forgray, sizeof(forgray));
                imwrite("../" + to_string(n++) + ".png", frame1);
        }
	}
	//-- Show what you got  
	namedWindow(window_name, 2);
	imshow(window_name, frame1);
	/*namedWindow(window_picture, 2);
	imshow(window_picture, frame1);*/
}

#endif