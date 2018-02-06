#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>

#include "lodepng.h"
#include "heatmap.h"
#include "colorschemes/Spectral.h"
#include "GenerateHeatmap.h"

using namespace std;
using namespace cv;

void GenerateHeatmap::generate_heatmap(string head_center_point)
{

	if (head_center_point.empty())
	{
		cerr << "Hello," << "please input the path of datas......" << endl;
		getchar();
		exit(1);
	}

	ifstream file(head_center_point);
	if (!file)
	{
		cerr << "error......" << endl;
		getchar();
		exit(1);
	}

	int x = 0, y = 0;
	int max_x = 0, max_y = 0;
	vector<Point> p;
	string s;
	char*a[2];
	char *next_token = NULL;
	while (getline(file, s))
	{
		char buf[10];
		strcpy_s(buf, s.c_str());//s.c_str()将s转string转char然后复制给buf
		char*temp = strtok_s(buf, ",", &next_token);
		int i = 0;
		while (temp)
		{
			a[i] = temp;
			i++;
			temp = strtok_s(NULL, ",", &next_token);
		}
		x = atoi(a[0]);
		y = atoi(a[1]);
		Point center(x, y);
		if (max_x < x) max_x = x;
		if (max_y < y) max_y = y;
		p.push_back(center);
	}
	static const size_t w = max_x, h = max_y;
	int npoints = p.size();
	

	// Create the heatmap object with the given dimensions (in pixel).
	heatmap_t* hm = heatmap_new(w, h);

	// We definitely need a larger stamp for this huge-ass resolution!
	// A radius of 128 means we'll get a (2*128+1)?=257? pixel stamp.
	//heatmap_stamp_t* stamp = heatmap_stamp_gen(60);
	auto stamp = heatmap_stamp_gen_nonlinear(50, [](float d) {return d * d * d * d * d * d; });

	// Add a bunch of random points to the heatmap now.
	for (unsigned i = 0; i < npoints; ++i) {
		// Notice the special function to specify the stamp.
		heatmap_add_point_with_stamp(hm, p[i].x, p[i].y, stamp);
	}

	// We're done with adding points, we don't need the stamp anymore.
	heatmap_stamp_free(stamp);

	//std::cout << "[1/3] All points added to the heatmap." << std::endl;

	// This creates an image out of the heatmap.
	// `image` now contains the image data in 32-bit RGBA.
	std::vector<unsigned char> image(w*h * 4);
	heatmap_render_to(hm, heatmap_cs_Spectral_discrete, &image[0]);
	//auto stamp = heatmap_stamp_gen_nonlinear(10, [](float d) {return d * d; });

	// Now that we've got a finished heatmap picture, we don't need the map anymore.
	heatmap_free(hm);

	//std::cout << "[2/3] Heatmap done rendering. (Saving to PNG will take some time...)" << std::endl;

	// Finally, we use the fantastic lodepng library to save it as an image.
	if (unsigned error = lodepng::encode(heatmap_png, image, w, h)) {
		std::cerr << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		exit(1);
	}

	//std::cout << "[3/3] All done, T. Hanks for your patience." << std::endl;

	//Mat pic=imread(heatmap_png);
	//Mat frame = imread("IMG_2.jpg"); // origin image
	//Mat heatmap = imread(heatmap_png); // heatmap image
	//imshow("heatmap", heatmap);

	//Mat overlay;
	//frame.copyTo(overlay);
	//double alpha = 0.6;
	//rectangle(overlay, Point(0, 0), frame.size(), Scalar(246, 182, 92), -1); 
	//addWeighted(overlay, alpha, frame, 1 - alpha, 0, frame);
	//addWeighted(heatmap, alpha, frame, 1 - alpha, 0, frame);
	//imshow("frame", frame);

	//waitKey(1);
	//exit(1);
}

