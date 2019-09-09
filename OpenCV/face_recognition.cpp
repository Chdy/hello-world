
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/opencv_modules.hpp"

#include "opencv2/face/facerec.hpp"
#include "opencv2/face.hpp"
#include "opencv2/objdetect.hpp"

#define LOG_TAG "opencv"

using namespace std;
using namespace cv;
using namespace cv::face;

#define D_USE_IPCAM 1


/** Function Headers */
void detectAndDisplay(Mat frame);
void getFaceData(Mat frame1);
void faceTrain();
void faceRecog(Mat frame1);
/** Global variables */
//String face_cascade_name = "E:\\opencv3.0\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt_tree.xml";
//String face_cascade_name = "E:\\opencv3.0\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml";
String face_cascade_name = "/Users/dengyan/Desktop/build/etc/haarcascades/haarcascade_frontalface_alt2.xml";
//String face_cascade_name = "E:\\opencv3.0\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalcatface.xml";

//String eyes_cascade_name = "E:\\opencv3.0\\opencv\\build\\etc\\haarcascades\\haarcascade_lefteye_2splits.xml";
String eyes_cascade_name = "/Users/dengyan/Desktop/build/etc/haarcascades/haarcascade_eye.xml";
//String eyes_cascade_name = "E:\\opencv3.0\\opencv\\build\\etc\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";

CascadeClassifier face_cascade;   //定义人脸分类器  
CascadeClassifier eyes_cascade;   //定义人眼分类器  
String window_name = "Capture - Face detection";

vector<Rect> gvr_faces;

Ptr<FaceRecognizer> gface_recog = EigenFaceRecognizer::create();
int gi_havemodefile = 0;
/** @function main */
int main(void)
{
	Mat frame = imread("../meeting.jpg");
	bool ret = false;
	char uc_startTraing = 0;
	int ul_framecount = 0;

	//-- 1. Load the cascades  
	ret = face_cascade.load(face_cascade_name);
	if (!ret){ printf("--(!)Error loading face cascade\n"); return -1; };

	ret = eyes_cascade.load(eyes_cascade_name);
	if (!ret){ printf("--(!)Error loading eyes cascade\n"); return -1; };


	
	
	
#if D_USE_IPCAM
	//-- 2. Read the video stream 
	VideoCapture capture;
	//capture.open(0);  
	capture.open("../cctv.mp4");
	//capture.open("e:\\picture\\cctv.mp4");
	if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }  

	printf("usage:  ESC （exit）   t（training）   \n");
	while (capture.read(frame))
#endif
	{
		if (frame.empty())
		{
			printf(" --(!) No captured frame -- Break!");
			return -1;
		}

		//-- 3. Apply the classifier to the frame  
		detectAndDisplay(frame);

		
		
		
#if D_USE_IPCAM
		int c = waitKey(20);
#else
		int c = waitKey(0);
#endif
		//if (gvr_faces.size() > 0)
		{
			switch ((char)c)
			{
			case 27:
				printf("esc pressed\n");
				return 0;
			case 116:
				//uc_startTraing = 1;
				double position = 10*1000;
				position = capture.get(CAP_PROP_POS_MSEC)+10*1000;
				capture.set(CAP_PROP_POS_MSEC, position);
				
				break;
			}
			/*
			if (uc_startTraing)
			{
				printf("getFaceData\n");
				ul_framecount++;

				//抓图
				getFaceData(frame);
				if (ul_framecount >= 20)
				{
					printf("training\n");
					//训练
					faceTrain();
					ul_framecount = 0;
					uc_startTraing = 0;
				}

			}	
			*/
			
		}	
		
	}  
	return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay(Mat frame1)
{
	Mat frame_gray;
	/*
	cvtColor(frame1, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//-- Detect faces  
	face_cascade.detectMultiScale(frame_gray, gvr_faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(50, 50), Size(500, 500));
	for (size_t i = 0; i < gvr_faces.size(); i++)
	{
		//Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);  
		//ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);  
		rectangle(frame1, gvr_faces[i], Scalar(255, 0, 0), 2, 8, 0);
		
	}
	
	String savepath = "face_rec_model.xml";
	Ptr<FaceRecognizer> gface_recog = EigenFaceRecognizer::create();
	char *pPath = "face_rec_model.xml";
	fstream _file;
	_file.open(pPath, ios::in);
	if (!_file)
	{
		printf("have not face_rec_model.xml\n ");

	}
	else
	{
		gface_recog->read("face_rec_model.xml");
		gi_havemodefile = 1;
	}
	//faceRecog(frame_gray);  //识别人脸
	if(gi_havemodefile  && gvr_faces.size() > 0)
	{
		int predicted_label = -1;
		double predicted_confidence = 0.0;
		Mat faceROI = frame_gray(gvr_faces[0]);
		resize(faceROI, faceROI, Size(50, 50));
	
		// Get the prediction and associated confidence from the model
		gface_recog->predict(faceROI, predicted_label, predicted_confidence);

		if ((predicted_label == 1) && (predicted_confidence < 900))
		{
			string pName = "Recognized  face";
			Point siteNo;
			printf("face recongnition predicted_label =%d predicted_confidence =%8f\n", predicted_label, predicted_confidence);

			//rectangle(frame1, gvr_faces[0], Scalar(0, 255, 0), 2, 8, 0);

			siteNo.x = gvr_faces[0].x;
			siteNo.y = gvr_faces[0].y;
			putText(frame1, pName, siteNo, 3, 0.7, Scalar(0, 255, 0), 1.5);

		}
	}

	*/
	//-- Show what you got  
	namedWindow(window_name, 2);
	imshow(window_name, frame1);
}

#if 1

vector <Mat> gvm_faces;
vector <int> gvi_labels;
/** @function detectAndDisplay */
void getFaceData(Mat frame1)
{
	Mat frame_gray;
	cvtColor(frame1, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	Mat faceROI = frame_gray(gvr_faces[0]);
	resize(faceROI, faceROI, Size(50,50));
	gvm_faces.push_back(faceROI);
	gvi_labels.push_back(1);
	
}

void faceTrain()
{
	Ptr<FaceRecognizer> face_recog = EigenFaceRecognizer::create();
	printf("face recongnition train -the threshold=%8f\n", face_recog->getThreshold());
	//
	face_recog->setThreshold(1500.0f);//threshold
	printf("face recongnition the threshold=%8f\n", face_recog->getThreshold());
	face_recog->train(gvm_faces, gvi_labels);
	printf("face recongnition train over\n");

	string savepath = "face_rec_model.xml";
	face_recog->save(savepath);
}

void faceRecog(Mat frame1)
{
	
	
}


#endif