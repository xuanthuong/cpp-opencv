#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
	//if (argc < 2)
	//{
	//	std::cerr << "Usage: " << argv[0] << " [image file name]" << std::endl;
	//	return -1;
	//}
	//else if (argc > 2)
	//{
	//	std::cerr << "too much arguments->" << "Usage: " << argv[0] << " [image file name]" << std::endl;
	//	return -1;
	//}
	//argv[1] = "../images/testSI.jpg";
	cv::Mat srcImg = cv::imread("testSI.jpg");
	if (!srcImg.data)
	{
		std::cout << "Problem loading image!!!" << std::endl;
		return -1;
	}
	cv::Mat gray;
	if (srcImg.channels() == 3)
		cv::cvtColor(srcImg, gray, CV_BGR2GRAY);
	else
		gray = srcImg;

	adaptiveThreshold(~gray, gray, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 15, -2);
	cv::imwrite("threshold.bmp", gray);

	cv::Mat hrzGray = gray.clone();
	cv::Mat vrtcGray = gray.clone();

	int hKernelSize = gray.cols / 30;
	int vKernelSize = gray.rows / 30;
	cv::Mat hKernel = cv::getStructuringElement(cv::MorphShapes::MORPH_RECT, cv::Size::Size_(hKernelSize, 1));
	cv::Mat vKernel = cv::getStructuringElement(cv::MorphShapes::MORPH_RECT, cv::Size::Size_(1, vKernelSize));

	erode(hrzGray, hrzGray, hKernel, cv::Point(-1, -1));
	dilate(hrzGray, hrzGray, hKernel, cv::Point(-1, -1));

	//cv::namedWindow("Horizontal Line", cv::WINDOW_NORMAL);
	//cv::resizeWindow("Horizontal Line", 800, 1000);
	//imshow("Horizontal Line", hrzGray);

	erode(vrtcGray, vrtcGray, vKernel, cv::Point(-1, -1));
	dilate(vrtcGray, vrtcGray, vKernel, cv::Point(-1, -1));

	//cv::namedWindow("Vertical Line", cv::WINDOW_NORMAL);
	//cv::resizeWindow("Vertical Line", 800, 1000);
	//imshow("Vertical Line", hrzGray);

	cv::Mat mask = hrzGray + vrtcGray;
	//cv::namedWindow("Line only", cv::WINDOW_NORMAL);
	//cv::resizeWindow("Line only", 800, 1000);
	//imshow("Line only", mask);
	cv::imwrite("line_only.bmp", mask);

	cvWaitKey(0);
	return 0;
}