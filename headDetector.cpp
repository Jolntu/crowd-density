#include "opencv2/opencv.hpp"
#include "objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "headDetector.h"
#include "GenerateHeatmap.h"

#include  <iostream>
#include  <fstream> 
#include  <stdio.h>

using namespace std;
using namespace cv;

void headDetector::drawCross(Mat img, CvPoint point, CvScalar color, int size, int thickness)
{
	line(img, cvPoint(point.x - size / 2, point.y), cvPoint(point.x + size / 2, point.y), color, thickness, 8, 0);
	line(img, cvPoint(point.x, point.y - size / 2), cvPoint(point.x, point.y + size / 2), color, thickness, 8, 0);
}

Mat headDetector::detectAndDisplay(Mat frame, CascadeClassifier detect_)
{
	vector<Rect> head;
	vector<Point> p;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);  //直方图均衡化
	Point xy = frame.size();
	p.push_back(xy);

	detect_.detectMultiScale(frame_gray, head, 1.100000000000000089, 3, 0, Size(0.1, 0.1), Size(25, 25));
	int numPeople = head.size();
	cout << "Seq_" << n << "," << "the total number of people are:" << numPeople << endl;


	for (size_t i = 0; i < head.size(); i++) {
		Point left_bottom(head[i].x, head[i].y);
		Point upper_right(head[i].x + head[i].width, head[i].y + head[i].height);
		Point center(head[i].x + head[i].width*0.5, head[i].y + head[i].height*0.5);
		p.push_back(center);

		rectangle(frame, left_bottom, upper_right, Scalar(0, 255, 0), 1, 8, 0);
		drawCross(frame, center, Scalar(0, 0, 255), 8, 1);
		string text = to_string(i + 1);
		putText(frame, text, upper_right, cv::FONT_HERSHEY_PLAIN, 0.9, Scalar(255, 0, 0), 1, 8, false);
	}

	ofstream out(head_center_txt);
	for (int i = 0; i < p.size(); ++i) {
		if (out.is_open())
		{
			out << p[i].x << "," << p[i].y << "\n";
		}
		if (i == p.size() - 1) {
			out.close();
		}
	}

	//GenerateHeatmap a;
	//a.generate_heatmap("head_center.txt");

	//imshow("result", frame);
	//imwrite("result.png", frame);
	++n;
	return frame;
}

void headDetector::frame_show(CascadeClassifier detect)
{
	ifstream file(testPic, ifstream::in);
	if (!file) { string erro_message = "No valid input file was given..."; CV_Error(CV_StsBadArg, erro_message); }
	string path;
	Mat frame;
	while (getline(file, path))
	{
		if (!path.empty())
		{
			frame = imread(path);
			detectAndDisplay(frame, detect);
			resize(frame, frame, Size(520, 440));
			if (!file) { string erro_message = "No valid input frame was given..."; CV_Error(CV_StsBadArg, erro_message); }
			//imshow("1", frame);
			//string pic = "heatmap.png";
			//if (!pic) { remove pic; }

			GenerateHeatmap b;
			b.generate_heatmap("head_center.txt");
			Mat heatmap = imread("heatmap.png");
			resize(heatmap, heatmap, Size(520, 440));
			//Mat heatmap_(heatmap.size(), frame.type(), Scalar(150, 0, 0)); 
			//Mat frame_;
			//addWeighted(frame,0.7,heatmap_,0.3,0,frame_);
	
			//cout << heatmap.cols << " " << heatmap.rows << endl;
			addWeighted(frame, 0.4, heatmap, 0.6,0.0, heatmap);
			if (!file) { string erro_message = "No valid input heqatmap was given..."; CV_Error(CV_StsBadArg, erro_message); }
			//imshow("2", heatmap);
			//imshow("heatmap", heatmap);

			Mat img_show(Size(1040,440),CV_8UC3);
			frame.copyTo(img_show(Rect(0, 0, 520, 440)));
			heatmap.copyTo(img_show(Rect(520, 0, 520, 440)));
			imshow("result", img_show);
			waitKey(0);
		}
	}
}