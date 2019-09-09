# include <opencv2/opencv.hpp>
#include "facialLandmarkDetection.cpp"
#include "face_swap.cpp"
#include <iostream>
using namespace std;
using namespace cv;

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define D_USE_IPCAM 1

/** Function Headers */
void detectAndDisplay(Mat &frame);

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

double distance(vector<Point2f> &point, double &x, double &y) { //计算两眼中心距
    //左眼中心坐标 36和39
    x = (point[39].x + point[36].x) / 2;
    y = (point[39].y + point[36].y) / 2;
    //右眼 42和45
    return (point[45].x + point[42].x) / 2 - x;
}

Mat hatAlpha;
Mat hatAlpha1;
int hat;
int openface;
int mask;
Mat mask1, mask2, mask3, mask4;
int isStop;
Mat lastframe;

int main() {
    hatAlpha = imread("../marry.png", -1);//穿戴图片
    hatAlpha1 = imread("../doctor.png", -1);//穿戴图片
    Mat doctor_button = imread("../doctor_button.png");
    resize(doctor_button, doctor_button, Size(100, 50));
    Mat marry_button = imread("../marry_button.png");
    resize(marry_button, marry_button, Size(100, 50));
    Mat mask_button = imread("../mask_button.png");
    resize(mask_button, mask_button, Size(100, 50));
    Mat mask_button1 = imread("../mask_button1.png");
    resize(mask_button1, mask_button1, Size(100, 50));
    Mat mask_button2 = imread("../mask_button2.png");
    resize(mask_button2, mask_button2, Size(100, 50));
    Mat mask_button3 = imread("../mask_button3.png");
    resize(mask_button3, mask_button3, Size(100, 50));
    Mat mask_button4 = imread("../mask_button4.png");
    resize(mask_button4, mask_button4, Size(100, 50));

    Mat masks[5] = {mask_button1, mask_button2, mask_button3, mask_button4, mask_button};


    mask1 = imread("../面具1.png", -1);//穿戴图片
    mask2 = imread("../面具2.png", -1);//穿戴图片
    mask3 = imread("../面具3.png", -1);//穿戴图片
    mask4 = imread("../面具4.png", -1);//穿戴图片

    cvui::init("Windous");

    cv::Mat frame = cv::Mat(cv::Size(400, 200), CV_8UC3);
    VideoCapture capture;
    capture.open("../cctv.mp4");

    Mat start = imread("../start.png");
    resize(start, start, Size(48, 22));
    Mat stop = imread("../stop.png");
    resize(stop, stop, Size(48, 22));
    Mat forward = imread("../forward.png");
    resize(forward, forward, Size(48, 22));
    Mat back = imread("../back.png");
    resize(back, back, Size(48, 22));

    Mat * state = &start;

    double end = capture.get(CAP_PROP_FRAME_COUNT) / 25 / 60; //为几点几分钟
    int endm = (int)end; //视屏时间的分钟部分
    int ends = (int)((end - endm) * 60); //视屏时间的秒钟部分

    double value = 0;
    const char *theLabelFormat = "%.2Lf";

    char buf[30];

    bool ret = false;
    ret = face_cascade.load(face_cascade_name);
    if (!ret){ printf("--(!)Error loading face cascade\n"); return -1; };

    success = landMaskInit();
    if (success != true)
    {
        printf("landMaskInit error\n");
        exit(-1);
    }

    if (!capture.isOpened())
    {
        printf("--(!)Error opening video capture\n");
        return -1;
    }
    capture.set(CAP_PROP_POS_MSEC, 40 * 1000);
    //capture.set(CAP_PROP_POS_FRAMES, 30 * 1200);

    while(isStop || capture.read(frame)) { //利用||运算符的特征，如果isStop为1，表示现在为暂停状态，此时由于||运算符左边已经为真，右边不会继续运算
        //由于没有进行读取图片，但是仍然需要处理，这样可以在暂停状态下换脸和头饰，因此使用lastframe变量保存上一帧的，这样就在暂停时一直用那一帧的图片来进行处理
        if (!isStop) //若非暂停状态
            lastframe = frame.clone(); //保存当前帧
        if (isStop) { //若暂停状态
            frame = lastframe.clone(); //读取上一帧
        }

        int status = cvui::iarea(0, frame.rows - 72, frame.cols, 72); //最底下的操控区

        switch (status) { //获取操控区状态
            case cvui::CLICK:;
            case cvui::DOWN:;
            case cvui::OVER: {
                if (cvui::button(frame, frame.cols * 0.5 - 12.5, frame.rows - 40, *state, *state, *state)) { //暂停按钮
                    isStop = !isStop;
                    state = state==&start?&stop:&start;
                }
                if (cvui::button(frame, frame.cols * 0.5 + 100, frame.rows - 40, forward, forward, forward)) { //快进按钮
                    capture.set(CAP_PROP_POS_FRAMES , capture.get(CAP_PROP_POS_FRAMES) + 25 * 15);
                    capture.read(lastframe);
                }
                if (cvui::button(frame, frame.cols * 0.5 - 125, frame.rows - 40, back, back, back)) { //快退按钮
                    int cur = capture.get(CAP_PROP_POS_FRAMES) - 25 * 15;
                    capture.set(CAP_PROP_POS_FRAMES , cur<0?0:cur);
                    capture.read(lastframe);
                }
                value = capture.get(CAP_PROP_POS_FRAMES) / 25 / 60;
                int curm = (int)value;
                int curs = int((value - curm) * 60);
                sprintf(buf, "%02d:%02d/%02d:%02d", curm, curs, endm, ends);
                if (cvui::trackbar(frame, 0, frame.rows - 79, frame.cols, &value, 0.0, end, 1, theLabelFormat, cvui::TRACKBAR_HIDE_LABELS|cvui::TRACKBAR_HIDE_VALUE_LABEL)) {
                    cv::Rect rec(frame.cols * 0.5 - 50, frame.rows * 0.5 - 20, 100, 40);
                    cvui::rect(frame, rec.x, rec.y, rec.width, rec.height, 0x333333, 0x33000000); //显示拖动进度条时的中间框
                    curm = (int)value; //获取当前视屏时间的分钟部分
                    curs = int((value - curm) * 60); //获取当前视屏时间的秒钟部分
                    sprintf(buf, "%02d:%02d/%02d:%02d", curm, curs, endm, ends); //格式化输出进度
                    cvui::text(frame, frame.cols * 0.5 - 38, frame.rows * 0.5 - 5, buf); //显示拖动进度条时屏幕中间的进度时间
                    capture.set(CAP_PROP_POS_FRAMES, value * 25 * 60); //使视屏定位到进度条对应的位置
                    if (isStop) //处理由于暂停时拖动进度条屏幕画面不变的问题
                        capture.read(lastframe);
                }
                cvui::text(frame, frame.cols * 0.02, frame.rows - 36, buf); //显示左下角的进度时间
                break;
            }
            case cvui::OUT:	break;
        }

        if (cvui::button(frame, frame.cols - 150, int(frame.rows * 0.20), //头饰按钮
                          marry_button, marry_button, marry_button)) {
            hat = hat != 1 ? 1 : 0;
        }

        if (cvui::button(frame, frame.cols - 150, int(frame.rows * 0.40), //头饰按钮
                         doctor_button, doctor_button, doctor_button)) {
            hat = hat != 2 ? 2 : 0;
        }

        if (cvui::button(frame, frame.cols - 150, int(frame.rows * 0.60), 100, //换脸按钮
                         50, "Change face")) {
            openface = !openface;
        }
        if (cvui::button(frame, frame.cols - 150, int(frame.rows * 0.80), //面具按钮
                         masks[mask], masks[mask], masks[mask])) {

            mask = ++mask%5; //切换面具
        }

        cvui::update();

        detectAndDisplay(frame);
        cvui::imshow("Windous", frame);

        if (cv::waitKey(40) == 27) {
            break;
        }
    }
    return 0;
}


/** @function detectAndDisplay */
void detectAndDisplay(Mat &frame1)
{
	std::vector<Rect> faces;
	Mat frame_gray;


	if (openface || mask) { //是否需要使用landmask
        success = landMaskGet(frame1, &gv_landmarks);
	}

    if (openface && success) //是否使用换脸，若使用，目前只处理画面中大于两个人脸情况的前两个识别出来的人脸
    {
        if (gv_landmarks.size() >= 2) {
            Mat frame2 = frame1.clone(); //先将frame1拷贝一份，防止人物一被人物二覆盖后无法使用人物一去覆盖人物二
            vector<Point2f> &points1 = gv_landmarks[0], &points2 = gv_landmarks[1];
            face_swap(frame1, points1, frame1, points2); //将人物一覆盖到人物二
            face_swap(frame2, points2, frame1, points1); //将人物二覆盖人物一，这里使用的是frame2，这张图没有被更改过，所以仍然有原始的人物二信息
        }
    }

	if (hat || mask) { //当开启头饰和面具功能时

        cvtColor(frame1, frame_gray, COLOR_BGR2GRAY);
        equalizeHist(frame_gray, frame_gray);

        //-- Detect faces
        face_cascade.detectMultiScale(frame_gray, faces, 1.2, 10, CASCADE_SCALE_IMAGE, Size(50, 50), Size(500, 500));

        for (size_t i = 0; i < faces.size(); i++)
        {

            Mat faceROI = frame_gray(faces[i]);

            if (hat == 1) //判断使用哪个头饰，若hat为0，则不使用
            {
                Mat hatback = hatAlpha;
                resize(hatAlpha, hatback, Size(faces[i].width*1.3, faces[i].height), 0, 0, INTER_LANCZOS4);
                mapToMat(hatback, frame1, faces[i].x - faces[i].width*(0.3 / 2), faces[i].y - 0.6*faces[i].height);
            }
            else if (hat == 2)
            {
                Mat hatback = hatAlpha1;
                resize(hatAlpha1, hatback, Size(faces[i].width*1.5, faces[i].height*0.8), 0, 0, INTER_LANCZOS4);
                mapToMat(hatback, frame1, faces[i].x - faces[i].width*(0.5/2), faces[i].y - 0.6*faces[i].height);
            }

            if (mask && i < gv_landmarks.size()) { //使用面具，mask为0则不使用
                double x, y;
                double d = distance(gv_landmarks[i], x, y); //计算人物两眼间距，x，y参数均由引用类型接收
                switch (mask) { //判断使用哪个面具
                    case 1: {
                        double scale = d/344; //计算人物两眼间距和面具两眼间距的比例，基于这个值缩放面具，344为该面具两眼中心的距离，单位为像素
                        Mat mask5 = mask1; //先拷贝一份，防止mask1被更改，虽然应该用clone函数进行深拷贝，但是这里直接使用拷贝构造函数也能正确运行
                        resize(mask1, mask5, Size(mask1.cols * scale, mask1.rows * scale), 0, 0, INTER_LANCZOS4); //缩放面具
                        mapToMat(mask5, frame1, x - 434 * scale, y - 760 * scale); //根据面具左眼到面具图片左上角的距离进行定位
                        break;
                    }
                    case 2: {
                        double scale = d/515;
                        Mat mask5 = mask2;
                        resize(mask2, mask5, Size(mask2.cols * scale, mask2.rows * scale), 0, 0, INTER_LANCZOS4);
                        mapToMat(mask5, frame1, x - 1327 * scale, y - 1354 * scale);
                        break;
                    }
                    case 3: {
                        double scale = d/200;
                        Mat mask5 = mask3;
                        resize(mask3, mask5, Size(mask3.cols * scale, mask3.rows * scale), 0, 0, INTER_LANCZOS4);
                        mapToMat(mask5, frame1, x - 200 * scale, y - 300 * scale);
                        break;
                    }
                    case 4: {
                        double scale = d/756;
                        Mat mask5 = mask4;
                        resize(mask4, mask5, Size(mask4.cols * scale, mask4.rows * scale), 0, 0, INTER_LANCZOS4);
                        mapToMat(mask5, frame1, x - 700 * scale, y - 1310 * scale);
                        break;
                    }
                }
            }

        }
    }

}


