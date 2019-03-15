#include "Filter.h"
using namespace std;
using namespace cv;

vector<Mat> Getcontours(InputArray src, InputArray src_s)
{
	vector<vector<Point> > contours;
	vector<vector<Point> > Next_contours;
	vector<Vec4i> hierarchy;
	Mat src_gray,src_p;
	vector<Point2f>  center;
	vector<float> radius;
	src.copyTo(src_gray);
	src_s.copyTo(src_p);
	//查找轮廓

	findContours(src_gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));

	vector <vector<Point>> contours_poly(contours.size());

	vector<float> temp(contours.size());
	//画轮廓
	Mat drawing(src.rows(), src.cols(), src.type(), cv::Scalar::all(0));


	/*for (int i = 0; i< contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);//逼近曲线，应该要调整
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);

	}*/


	float lengthMax = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		if (lengthMax<contours[i].size())
		{
			lengthMax = contours[i].size();
		}
		
	}
	int k = 0; Point2f thisCenter; float thisRadius;
	for (int j = 0; j < contours.size(); j++)
	{
		Scalar color = Scalar(255, 255, 255);
		
		if (contours[j].size()>lengthMax*0.95 && contours[j].size()<lengthMax*1.05)
		{
			drawContours(drawing, contours, j, color, 2, 8, hierarchy, 0, Point());
			Next_contours.push_back(contours[j]);

			approxPolyDP(Mat(contours[j]), contours_poly[j], 3, true);//逼近曲线，应该要调整
			minEnclosingCircle(contours_poly[j], thisCenter, thisRadius);
			circle(drawing, thisCenter, thisRadius, Scalar(255, 255, 0), 3, 8, 0);
			center.push_back(thisCenter);
			radius.push_back(thisRadius);
		}


	}
	imwrite("searchedPoint.jpg", drawing);
	vector<float>::iterator smallest = max_element(std::begin(radius), std::end(radius));
	float myDistance = *smallest * 0.9;
	//int id = distance(std::begin(radius), biggest);

	vector<Mat> roiArea;
	Mat rois;

	for (int m = 0; m < radius.size(); m++)
	{
		src_p(Rect(center.at(m).x - myDistance, center.at(m).y - myDistance, myDistance * 2, myDistance * 2)).copyTo(rois);
		Mat roiMask(myDistance * 2, myDistance * 2, rois.type(), cv::Scalar::all(0));
		circle(roiMask, Point2f(myDistance, myDistance), myDistance, Scalar(255, 255, 255), -1, 8, 0);
		bitwise_not(roiMask, roiMask);
		imwrite("mask.jpg", rois);
		roiArea.push_back(rois+roiMask);
		imwrite("roi.jpg", roiArea[m]);
	}
	
	return roiArea;
	//centers = center[0];
	
}

void lackDetect(InputArray src)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Mat src_temp; vector<vector<Point> > Next_contours;

	vector<Point2f>  center;
	vector<float> radius;

	src.copyTo(src_temp);
	Mat drawing(src.rows(), src.cols(), src.type(), cv::Scalar::all(0));
	findContours(src_temp, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector <vector<Point>> contours_poly(contours.size()); vector<double> areas;
	Point2f thisCenter; float thisRadius; int k = 0;
	for (int j = 0; j < contours.size(); j++)
	{
		Scalar color = Scalar(255, 255, 255);
	
			drawContours(drawing, contours, j, color, 1, 8, hierarchy, 0, Point());
			Next_contours.push_back(contours[j]);

			approxPolyDP(Mat(contours[j]), contours_poly[j], 3, true);//逼近曲线，应该要调整
			minEnclosingCircle(contours_poly[j], thisCenter, thisRadius);
			double area=contourArea(contours[j], true);
			areas.push_back(area);
			if (abs(area)>10 && abs(area)<1000 )
			{
				circle(drawing, thisCenter, thisRadius, Scalar(255, 255, 255), 2, 8, 0);
				k++;

			}
			
			center.push_back(thisCenter);
			radius.push_back(thisRadius);
	


	}

	imwrite("result.jpg", src_temp);
	imwrite("contours.jpg", drawing);
	waitKey();


}

void thresholdMyimage(Mat&A_img, Mat&B_img)
{
	Mat srcimg, dstimg, roiimg;
	srcimg = imread("B11.bmp", 0);

	threshold(srcimg, dstimg, 100, 255, THRESH_BINARY);
	threshold(srcimg, roiimg, 200, 255, THRESH_BINARY);

	Mat elementA = getStructuringElement(MORPH_RECT, Size(35, 35));

	dilate(roiimg, roiimg, elementA);
	

	imwrite("roiimg.jpg", roiimg);

	Mat elementB = getStructuringElement(MORPH_RECT, Size(5, 5));
	//dilate(dstimg, dstimg, elements);
	//erode(dstimg, dstimg, elements);
	imwrite("dstimg.jpg", dstimg);
	A_img = roiimg;
	B_img = dstimg;
}
int main()
{
	Mat A_img, B_img;
	
	thresholdMyimage(A_img, B_img);

	imwrite("erode_result.jpg", B_img);
	vector<Mat> roiarea = Getcontours(A_img, B_img);
	Mat test_img = roiarea[2].clone();
	imshow("1", test_img);
	//erode(test_img, test_img, element);
	//dilate(test_img, test_img, element);
	imshow("2", test_img);
	imwrite("test_are.jpg", test_img);
	lackDetect(test_img);
	waitKey();




}



