#include <opencv2/opencv.hpp>

#include "GenerateHeatmap.h"
#include "headDetector.h"

using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
	CascadeClassifier heads_cascade;
	String head_cascade_name = "cascades.xml";
	headDetector a;

	if (!heads_cascade.load(head_cascade_name)) { printf("--(!)Error loading...\n"); getchar(); return -1; }
	a.frame_show(heads_cascade);


	//GenerateHeatmap b;
	//b.generate_heatmap("head_center.txt");
	return 0;
}

