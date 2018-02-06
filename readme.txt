1、head_center.txt存放检测到的人头位置坐标（输入）
2、IMG_2.jpg是检测的图像，heatmap.png是由检测到的点生成的热力图（输出），     result.png是检测到的人头图像
3、使用方法：
   #include <opencv2/opencv.hpp>
   

#include "GenerateHeatmap.h"
   

using namespace std;
   
using namespace cv;
   


int main(int argc,char* argv[])

   {
	
       GenerateHeatmap a;
	
       a.generate_heatmap("head_center.txt");
    
}
