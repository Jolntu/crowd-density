1��head_center.txt��ż�⵽����ͷλ�����꣨���룩
2��IMG_2.jpg�Ǽ���ͼ��heatmap.png���ɼ�⵽�ĵ����ɵ�����ͼ���������     result.png�Ǽ�⵽����ͷͼ��
3��ʹ�÷�����
   #include <opencv2/opencv.hpp>
   

#include "GenerateHeatmap.h"
   

using namespace std;
   
using namespace cv;
   


int main(int argc,char* argv[])

   {
	
       GenerateHeatmap a;
	
       a.generate_heatmap("head_center.txt");
    
}
