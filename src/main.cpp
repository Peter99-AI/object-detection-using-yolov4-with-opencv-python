#include<iostream>
#include<opencv2/opencv.hpp>

#define OPENCV
#include "yolo_v2_class.hpp"


int TestYolo() {
	std::string root = "/home/azues/Documents/C++/File/";
	std::string cfgname  = root + "yolov4-tiny-fod.cfg";    
	std::string weights_file = root + "yolov4-tiny-fod_best.weights";

	Detector detector(cfgname, weights_file, 0);

	cv::VideoCapture capture;
	capture.open("/home/azues/Documents/C++/File/sample4.MP4");
	cv::VideoWriter writer;
	writer.open("/home/azues/Documents/C++/File/output.avi", cv::VideoWriter::fourcc('D', 'I', 'V', 'X'), 30, cv::Size(1920, 1080), 1);

	if (!capture.isOpened())
		return 0;
	cv::Mat src8uc3;
	cv::Mat _src8uc3;
	
	while (1) {
		capture >> src8uc3;
		if (src8uc3.rows == 0)
			break;

		cv::resize(src8uc3, _src8uc3, cv::Size(1920, 1080));
		cv::Mat dst;
		//HisEq(_src8uc3, _src8uc3);

		std::vector<bbox_t> bbox_base = detector.detect(_src8uc3, 0.2);
		for (int i = 0; i < bbox_base.size(); i++) {
			cv::Rect rc(bbox_base[i].x, bbox_base[i].y, bbox_base[i].w, bbox_base[i].h);
			cv::rectangle(_src8uc3, rc, cv::Scalar(0, 255, 0), 1);
			cv::putText(_src8uc3, "FOD", cv::Point(rc.x, rc.y - 5), 1, 1, cv::Scalar(0, 255, 0), 2);
		}


		cv::imshow("src image", _src8uc3);
		char c = cv::waitKey(10);
		if (c == 'q')
			break;

		writer << _src8uc3;
	}

	writer.release();
	return 0;
}

int main(){
    TestYolo();
    return 0;
}