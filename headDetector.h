#ifndef HEADDETECTOR_H
#define HEADDETECTOR_H

using namespace std;
using namespace cv;

class headDetector {
private:
	const string head_center_txt = "head_center.txt";
	const string testPic = "list.txt";
	//String head_cascade_name = "cascades.xml";
	int n = 1;

public:
	//CascadeClassifier heads_cascade;
	//String head_cascade_name = "cascades.xml";

	void drawCross(Mat img, CvPoint point, CvScalar color, int size, int thickness);
	Mat detectAndDisplay(Mat frame, CascadeClassifier detect_);
	void frame_show(CascadeClassifier detect);
};
#endif