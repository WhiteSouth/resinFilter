#ifndef _SECOND_LAYER_H_
#define _SECOND_LAYER_H_
#include <algorithm>
#include <math.h>
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <direct.h>
#include <ctime>
#include<sstream>
#include <io.h>

using namespace std;
using namespace cv;
class resinFilter
{	
public:
	resinFilter();
	~resinFilter();
	void threshold();
	vector<string> pathGet(string filepath, string postFix);

private:
	Mat srcFilter;//���������ͼ��
	Mat dstFilter;//ԭͼ�ϱ�Ǻ�Ľ��
	void areaDetect();
	void FilterDetect();//���ĺ���
};

















#endif