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
	Mat srcFilter;//输入待检测的图像
	Mat dstFilter;//原图上标记后的结果
	void areaDetect();
	void FilterDetect();//检测的函数
};

















#endif