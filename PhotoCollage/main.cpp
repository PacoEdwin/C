//// CannyStill.cpp
////
//#include<opencv2/opencv.hpp>
//
//#include<iostream>
//#include<vector>
//#include<stdint.h>
//#include<conio.h>
//#include<math.h>
//#include<algorithm>
//#include<fstream>
//// may have to modify this line if not using Windows
//using namespace std;
//using namespace cv;
///////////////////////////
////////////////////////////////////////////////////////////////////////////
////lesson_2
////int main()
////{
////	Mat testColor = imread("image.png", CV_LOAD_IMAGE_COLOR);
////	Mat testGray = imread("image.png", CV_LOAD_IMAGE_GRAYSCALE);
////	imshow("color", testColor);
////	imshow("graycolor", testGray);
////	imwrite("outputGray.png", testGray);
////	waitKey();
////}
//
////lesson_3
////int main()
////{
////	Mat file1 = imread("image.png", CV_LOAD_IMAGE_UNCHANGED);
////	Mat file2 = imread("image.png", CV_LOAD_IMAGE_GRAYSCALE);
////	namedWindow("Color", CV_WINDOW_FREERATIO);
////	namedWindow("Fixed", CV_WINDOW_AUTOSIZE);
////	imshow("Color", file1);
////	imshow("Fixed", file2);
////	//resizeWindow("Color", file1.cols/2, file1.rows/2);
////	//resizeWindow("Fixed", file1.cols / 2, file1.rows / 2);
////	moveWindow("Color", 0, 500);
////	moveWindow("Fixed", file1.cols+5, 500);
////	waitKey();
////}
//
////lesson4
////int main()
////{
////	Mat original = imread("me.jpg", CV_LOAD_IMAGE_COLOR);
////	Mat modified = imread("me.jpg", CV_LOAD_IMAGE_COLOR);
////	Mat kek= imread("me.jpg", CV_LOAD_IMAGE_COLOR);
////	for (int r=0;r<modified.rows;r++)
////	{
////		for (int c=0;c<modified.cols;c++)
////		{
////			modified.at<cv::Vec3b>(r, c)[1]*=0.5f;
////		}
////	}
////	Rect cropped_roi(0, 0, 700, 700);
////	original= kek(cropped_roi);
////	imshow("Original", original);
////	imshow("Modified", modified);
////	waitKey();
////}
//pair<double, double> rotate(double x, double y, double a)
//{
//	pair<double, double> coord;
//	//coord.first= x*cos(a) + y*sin(a);
//	//coord.second = -x*sin(a) + y*cos(a);
//	coord.first = x*cos(a) - y*sin(a);
//	coord.second = x*sin(a) + y*cos(a);
//	return coord;
//}
//float rad(float angle)
//{
//	float pi = acos(-1);
//	return pi*angle / 180;
//}
//float degree(float rad)
//{
//	float pi = acos(-1);
//	return rad * 180 / pi;
//}
//void crop_rotated(Mat img, int x, int y, double angle)
//{
//	angle = -angle;
//	pair<double, double> coord = rotate(x, y, rad(angle));
//	cv::bitwise_not(img, img);
//	std::vector<cv::Point> points;
//	cv::Mat_<uchar>::iterator it = img.begin<uchar>();
//	cv::Mat_<uchar>::iterator end = img.end<uchar>();
//	for (; it != end; ++it)
//		if (*it)
//			points.push_back(it.pos());
//
//	cv::RotatedRect box = cv::minAreaRect(cv::Mat(points));
//	cv::Mat rot_mat = cv::getRotationMatrix2D(box.center, angle, 1);
//	cv::Mat rotated;
//	cv::warpAffine(img, rotated, rot_mat, img.size(), cv::INTER_CUBIC);
//	cv::Size box_size = box.size;
//	if (box.angle < -45.)
//		std::swap(box_size.width, box_size.height);
//	cv::Mat cropped;
//	cv::getRectSubPix(rotated, box_size, box.center, cropped);
//	std::cout<< coord.first <<" "<< coord.second<<endl;
//	cv::Rect cropped_roi(static_cast<int> (coord.first), static_cast<int>(coord.second), 100, 100);
//	cv::Mat kek = rotated;
//	Mat lol;
//	lol = kek(cropped_roi);
//	cv::imshow("Original", img);
//	cv::imshow("Rotated", rotated);
//	cv::imshow("Cropped", cropped);
//	cv::imshow("Cropped_rotated",lol);
//	std::cout << "cropped size " << cropped.rows << " " << cropped.cols << endl << "cropped_rotated size " << lol.rows << " " << lol.cols<<" ";
//	cv::waitKey(0);
//}
//pair<float, float> rotate_sides(float h, float w, float angle)
//{
//	float nW = h*sin(angle) + w*cos(angle);
//	float nH = h*cos(angle) + w*sin(angle);
//	pair<float, float> a;
//	a.first = nW;
//	a.second = nH;
//	return a;
//}
//Mat rotate_bound(Mat src, float rad)
//{
//
//	float angle = degree(rad);
//
//	// get rotation matrix for rotating the image around its center in pixel coordinates
//	cv::Point2f center((src.cols - 1) / 2.0, (src.rows - 1) / 2.0);
//	cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
//	// determine bounding rectangle, center not relevant
//	cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
//	// adjust transformation matrix
//	rot.at<double>(0, 2) += bbox.width / 2.0 - src.cols / 2.0;
//	rot.at<double>(1, 2) += bbox.height / 2.0 - src.rows / 2.0;
//
//	cv::Mat dst;
//	cv::warpAffine(src, src, rot, bbox.size());
//	return src;
//}
//void asdasd(vector<int> &a)
//{
//	a[1]++;
//}
//int main()
//{
//	vector<int> a(5);
//	vector<int> &b = a;
//	b.pop_back();
//	Scalar colorTab[] =
//	{
//	
//		Scalar(0, 0, 255),
//		Scalar(0,255,0),
//		Scalar(255,100,100),
//		Scalar(255,0,255),
//		Scalar(0,255,255)
//	};
//	//cv::Rect cropped_roi( x, y, width, height );
//		cv::Mat img = cv::imread("0.jpg", CV_LOAD_IMAGE_COLOR);
//			float angle = rad(45);
//			float desired_pixels = 150 * 267;
//			const float
//				current_pixels = static_cast< float >(img.size().area()),
//				area_scaling = desired_pixels / current_pixels,
//				side_scaling = sqrt(area_scaling);
//			cv::resize(img, img, cv::Size(), side_scaling, side_scaling);
//			Mat dst = rotate_bound(img, angle);
//	
//		//imshow("rot", dst);
//		vector<pair<float, float>> coords, rot, pop;
//		pop.push_back(make_pair<float>(img.cols / 4., img.rows / 4.));
//		pop.push_back(make_pair<float>(3 * img.cols / 4., img.rows / 4.));
//		pop.push_back(make_pair<float>(img.cols / 4., 3 * img.rows / 4.));
//		pop.push_back(make_pair<float>(3 * img.cols / 4., 3 * img.rows / 4.));
//		float c_row = pop[3].second - pop[0].second;
//		float c_col = pop[3].first - pop[0].first;
//		rot.push_back(rotate(img.cols / 4. - c_col, img.rows / 4.- c_row,-angle));
//		rot.push_back(rotate(3 * img.cols / 4. - c_col, img.rows / 4.- c_row,-angle));
//		rot.push_back(rotate(img.cols / 4. - c_col, 3 * img.rows / 4.- c_row,-angle));
//		rot.push_back(rotate(3 * img.cols / 4. - c_col, 3 * img.rows / 4.- c_row,-angle));
//		circle(img, Point(rot[0].first + c_col, rot[0].second+ c_row), 10, colorTab[2], FILLED, LINE_AA);
//		circle(img, Point(rot[1].first + c_col, rot[1].second + c_row), 10, colorTab[2], FILLED, LINE_AA);
//		circle(img, Point(rot[2].first + c_col, rot[2].second + c_row), 10, colorTab[2], FILLED, LINE_AA);
//		circle(img, Point(rot[3].first + c_col, rot[3].second + c_row), 10, colorTab[2], FILLED, LINE_AA);
//		circle(img, Point(c_col, c_row), 10, colorTab[2], FILLED, LINE_AA);
//		coords.push_back(rotate(0, 0,-angle));
//		coords.push_back(rotate(img.cols, 0, -angle));
//		coords.push_back(rotate(0, img.rows, -angle));
//		coords.push_back(rotate(img.cols, img.rows, -angle));
//		cout << dst.rows << " " << dst.cols;
//		for(int i=0;i<4;i++)
//			circle(dst, Point(coords[i].first,coords[i].second),10, colorTab[1], FILLED, LINE_AA);
//		circle(dst, Point(coords[0].first, coords[0].second + sin(angle)*img.cols), 10, colorTab[0], FILLED, LINE_AA);
//		circle(dst, Point(coords[1].first, coords[1].second + sin(angle)*img.cols), 10, colorTab[0], FILLED, LINE_AA);
//		circle(dst, Point(coords[2].first, coords[2].second+ sin(angle)*img.cols), 10, colorTab[0], FILLED, LINE_AA);
//		circle(dst, Point(coords[3].first, coords[3].second+ sin(angle)*img.cols), 10, colorTab[0], FILLED, LINE_AA);
//		
//		vector<pair<float, float>> asd;
//		asd.push_back(rotate(0-img.cols/2., 0-img.rows/2., -angle));
//		asd.push_back(rotate(img.cols - img.cols / 2., 0 - img.rows / 2., -angle));
//		asd.push_back(rotate(0 - img.cols / 2., img.rows - img.rows / 2., -angle));
//		asd.push_back(rotate(img.cols - img.cols / 2., img.rows - img.rows / 2., -angle));
//		for (int i = 0; i<4; i++)
//			circle(dst, Point(asd[i].first+dst.cols/2., asd[i].second+dst.rows/2.), 2, colorTab[4], FILLED, LINE_AA);
//		
//		////Mat keke = rotate_bound(img, rad(45));
//		////imshow("keke", keke);
//		////waitKey(0);
//		////pair<float, float> s = rotate_sides(img.rows, img.cols, rad(45));
//
//		////походу никак
//		std::array< cv::Point2f, 3 > from_triangle_cv, to_triangle_cv;
//		from_triangle_cv[0] = Point2f(0,0);
//		from_triangle_cv[1] = Point2f(img.cols,0);
//		from_triangle_cv[2] = Point2f(0, img.rows);
//		////to_triangle_cv[0] = Point2f(img.cols/4.,img.rows/4.);
//		////to_triangle_cv[1] = Point2f(3*img.cols/4., img.rows / 4.);
//		////to_triangle_cv[2] = Point2f(img.cols / 4., 3 * img.rows/4.);
//		////circle(img, Point(img.cols / 4., img.rows / 4.), 2, colorTab[4], FILLED, LINE_AA);
//		////circle(img, Point(img.cols / 4., 3 * img.rows / 4.), 2, colorTab[4], FILLED, LINE_AA);
//		////circle(img, Point(3 * img.cols / 4., img.rows / 4.), 2, colorTab[4], FILLED, LINE_AA);
//		////circle(img, from_triangle_cv[0], 2, colorTab[4], FILLED, LINE_AA);
//		////circle(img, from_triangle_cv[1], 2, colorTab[4], FILLED, LINE_AA);
//		////circle(img, from_triangle_cv[2], 2, colorTab[4], FILLED, LINE_AA);
//		vector<pair<float, float>> aaa;
//		////aaa.push_back(rotate(img.cols/2., img.rows/2.,angle));
//		////aaa.push_back(rotate(img.cols, img.rows/2.,angle));
//		////aaa.push_back(rotate(img.cols/2., img.rows, angle));
//		////aaa.push_back(rotate(0-img.cols/2,0-img.rows/2., -angle));
//		////aaa.push_back(rotate(0 - img.cols / 2., img.rows - img.rows / 2., -angle));
//		////aaa.push_back(rotate(img.cols - img.cols / 2., 0 - img.rows / 2., -angle));
//		aaa.push_back(rotate(img.cols / 2. - img.cols / 2, img.rows / 2. - img.rows / 2.,-angle));
//		aaa.push_back(rotate(img.cols - img.cols / 2., img.rows / 2. - img.rows / 2.,-angle));
//		aaa.push_back(rotate(img.cols / 2. - img.cols / 2., img.rows - img.rows / 2., -angle));
//		to_triangle_cv[0] = Point2f(aaa[0].first + dst.cols / 2.,aaa[0].second + dst.rows / 2.);
//		to_triangle_cv[1] = Point2f(aaa[1].first + dst.cols / 2., aaa[1].second + dst.rows / 2.);
//		to_triangle_cv[2] = Point2f(aaa[2].first + dst.cols / 2., aaa[2].second + dst.rows / 2.);
//		imshow("original", img);
//		const auto lol = getAffineTransform(from_triangle_cv.data(), to_triangle_cv.data());
//		vector<Point2f> from;
//		for (int i = 0; i < 3; i++)
//		{
//			from.push_back(Point2f(from_triangle_cv[i].x, from_triangle_cv[i].y));
//		}
//		vector<Point2f> to;
//		cv::transform(from, to, lol);
//		Mat warped;
//		cv::warpAffine(img, warped, lol, Size(static_cast<int>(img.cols),
//			static_cast<int>(img.rows)),cv::WARP_INVERSE_MAP,
//			cv::BORDER_CONSTANT,img.at< cv::Vec3b >(cv::Point(0, 0)));
//		Mat resized;
//		cv::resize(warped, resized, cv::Size(img.cols / 2., img.rows / 2.));
//		Rect cropped_roi(img.cols / 4., img.rows / 4., img.cols / 2., img.rows / 2.);
//		imshow("warped", warped);
//		imshow("dst", dst);
//		imshow("cropped", warped(cropped_roi));
//		imshow("cropped_original", img(cropped_roi));
//		imshow("resized", resized);
//		waitKey(0);
//
//		//////float deg=45;
//		//////if (deg == 270 || deg == -90) {
//		//////	// Rotate clockwise 270 degrees
//		//////	cv::transpose(img, img);
//		//////	cv::flip(img, img, 0);
//		//////}
//		//////else if (deg == 180 || deg == -180) {
//		//////	// Rotate clockwise 180 degrees
//		//////	cv::flip(img, img, -1);
//		//////}
//		//////else if (deg == 90 || deg == -270) {
//		//////	// Rotate clockwise 90 degrees
//		//////	cv::transpose(img, img);
//		//////	cv::flip(img, img, 1);
//		//////}
//		//////else if (deg == 360 || deg == 0 || deg == -360) {
//		//////	if (img.data != img.data) {
//		//////		img.copyTo(img);
//		//////	}
//		//////}
//		//////else
//		//////{
//		//////	cv::Point2f src_center(img.cols / 2.0F, img.rows / 2.0F);
//		//////	cv::Mat rot_mat = getRotationMatrix2D(src_center, 360 - deg, 1.0);
//		//////	warpAffine(img, img, rot_mat, img.size());
//		//////}
//		//////imshow("rotated", img);
//
//
//		////waitKey(0);
//		////
//		////Mat warped;
//		////imshow("img", img);
//		////cv::waitKey(0);
//		////cout << img.rows/2 << " " << img.cols/2 << endl;
//		//int len = max(img.cols, img.rows);
//		//Point2f center(img.cols/2.f,img.rows/2.f);
//		////Point2f center(s.first / 2.f, s.second / 2.f);
//
//		//Mat M = getRotationMatrix2D(center, 45, 1.0);
//		//imshow("a", img);
//		//warpAffine(img, rotated, M, img.size()/*Size(s.first,s.second)*/,  cv::WARP_INVERSE_MAP,cv::BORDER_CONSTANT);
//		//
//		////warpAffine(img, rotated, M, Size(s.first,s.second),  cv::WARP_INVERSE_MAP,cv::BORDER_CONSTANT);
//		//
//		//imshow("rotated", rotated);
//		//cv::waitKey(0);
//
//		//crop_rotated(img, img.rows/2, img.cols/2, 45);
//}
//lesson5
//int main()
//{
//	Mat original = imread("me.jpg", CV_LOAD_IMAGE_COLOR);
//
//	Mat splitChannels[3];
//
//	split(original, splitChannels);
//	imshow("B", splitChannels[0]);
//	imshow("G", splitChannels[1]);
//	imshow("r", splitChannels[2]);
//
//	splitChannels[2] = Mat::zeros(splitChannels[2].size(),CV_8UC1);
//	Mat output;
//	merge(splitChannels, 3, output);
//	imshow("Mereged", output);
//	waitKey();
//}

////lesson6,lesson7,lesson8,lesson9,lesson10
//void takeDFT(Mat& source, Mat& destination)
//{
//	Mat originalComplex[2] = { source,Mat::zeros(source.size(),CV_32F) };
//	Mat dftReady;
//	merge(originalComplex, 2, dftReady);
//	Mat dftOfOriginal;
//	dft(dftReady, dftOfOriginal, DFT_COMPLEX_OUTPUT);
//	destination = dftOfOriginal;
//}
//
//void recenterDFT(Mat& source)
//{
//	int centerX = source.cols / 2;
//	int centerY = source.rows / 2;
//	Mat q1(source, Rect(0, 0,centerX,centerY));
//	Mat q2(source, Rect(centerX, 0, centerX, centerY));
//	Mat q3(source, Rect(0, centerY, centerX, centerY));
//	Mat q4(source, Rect(centerX, centerY, centerX, centerY));
//
//	Mat swapMap;
//	q1.copyTo(swapMap);
//	q4.copyTo(q1);
//	swapMap.copyTo(q4);
//	q2.copyTo(swapMap);
//	q3.copyTo(q2);
//	swapMap.copyTo(q3);
//
//}
//
//void showDFT(Mat& source)
//{
//	Mat splitArray[2] = { Mat::zeros(source.size(),CV_32F), Mat::zeros(source.size(),CV_32F) };
//	split(source, splitArray);
//
//	Mat dftMagnitude;
//	magnitude(splitArray[0], splitArray[1], dftMagnitude);
//
//	dftMagnitude += Scalar::all(1);
//	log(dftMagnitude, dftMagnitude);
//	normalize(dftMagnitude, dftMagnitude, 0, 1, CV_MINMAX);
//	recenterDFT(dftMagnitude);
//	imshow("DFT", dftMagnitude);
//	waitKey();
//}
//
//void invertDFT(Mat &source, Mat& destination)
//{
//	Mat inverse;
//	dft(source, inverse, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
//
//	destination = inverse;
//}
//
//void createGaussian(Size& size, Mat& output, int uX, int uY, float sigmaX, float sigmaY, float  amplitude =1.0f)
//{
//	Mat temp = Mat(size, CV_32F);
//
//	for (int r =0;r<size.height;r++)
//	{
//		for (int c=0 ;c<size.width;c++)
//		{
//			float x = ((c - uX)*((float)c - uX)) / (2.0f *sigmaX*sigmaX);
//			float y = ((r - uY)*((float)r - uY)) / (2.0f *sigmaY*sigmaY);
//			float value = amplitude* exp(-(x + y));
//			temp.at<float>(r, c) = value;
//		}
//	}
//	normalize(temp, temp, 0.0f, 1.0f, NORM_MINMAX);
//	output = temp;
//}
//
//int main()
//{
//	/*Mat original = imread("me.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//	Mat originalFloat;
//
//	original.convertTo(originalFloat, CV_32FC1, 1.0 / 255.0);
//	Mat dftOfOriginal; 
//	takeDFT(originalFloat, dftOfOriginal);
//	showDFT(dftOfOriginal);
//	Mat invertedDFT;
//	invertDFT(dftOfOriginal,invertedDFT);
//
//	imshow("InvertDFT result", invertedDFT);
//	waitKey();*/
//	Mat output;
//	createGaussian(Size(256, 256),output, 256/2, 128, 10,10);
//	imshow("Gaussian", output);
//	waitKey();
//}

//lesson12
//const int fps = 20 ;
//int main()
//{
//	Mat frame;
//	VideoCapture vid(0);
//	if (!vid.isOpened())
//	{
//		return -1;
//	}
//	while (vid.read(frame))
//	{
//		imshow("Webcam", frame);
//		if (waitKey(1000 / fps) >= 0)
//		{
//			break;
//		}
//	}
//}
//vector<vector<int>> coord;
//int size_x = 0,size_y=0;
//bool verify = false;
//void convert(string s)
//{
//	int num1, num2;
//	string tmp;
//	bool check = false;
//	for (int i = 0; i < s.size(); i++)
//	{
//		if (s[i] == ';')
//		{
//			check = true;
//			num1 = stoi(tmp);
//			tmp = "";
//			continue;
//		}
//		if (!check)
//			tmp += s[i];
//		else
//			tmp += s[i];
//	}
//	num2 = stoi(tmp);
//	coord.resize(coord.size() + 1);
//	coord[coord.size() - 1].push_back(num1);
//	coord[coord.size() - 1].push_back(num2);
//	if (num1 > size_x)
//		size_x = num1;
//	if (num2 > size_y)
//		size_y = num2;
//}
//void generate(vector<vector<double>> &c)
//{
//	for (int i = 0; i < c.size(); i++)
//	{
//		c[i][0] = (int)(rand() % size_x);
//		c[i][1] = (int)(rand() % size_y);
//	}
//}
//
//double euclidian(double x1,double y1,double x0, double y0)
//{
//	return sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1-y0));
//}
//
//bool check(vector<double> norm,double epsilon)
//{
//	bool checked = false;
//	for (int i = 0; i < norm.size(); i++)
//	{
//		if (norm[i] > epsilon )
//			checked = true;
//	}
//	return checked;
//}
//
//vector<double> dist_method(vector<vector<double>> c, vector<vector<double>> c_old)
//{
//	vector<double> norm(c.size());
//	for (int i=0; i < c.size(); i++)
//		norm[i] = euclidian(c[i][0],c[i][1],c_old[i][0],c_old[i][1]);
//	return norm;
//}
//
//int argminD(int x, int y, vector<vector<double>> c)
//{
//	double dist=10000000;
//	int j = 0;
//	for (int i = 0; i < c.size(); i++)
//	{
//		double a = euclidian(x, y, c[i][0], c[i][1]);
//		if (a < dist)
//		{
//			dist = a;
//			j = i;
//		}
//	}
//	return j;
//}
//
//vector<double> mean(vector<vector<int>> asd)
//{
//	verify = false;
//	vector<double> c(2);
//	if (asd.size() > 0)
//	{
//		for (int i = 0; i < asd.size(); i++)
//		{
//			c[0] += asd[i][0];
//			c[1] += asd[i][1];
//		}
//		c[0] = c[0] / asd.size();
//		c[1] = c[1] / asd.size();
//	}
//	else
//		verify = true;
//	return c;
//}
//
//vector<vector<double>> kmeans(int k, double epsilon)
//{
//	vector<vector<double>> centroids(k, vector<double>(2));
//	generate(centroids);
//	vector<vector<double>> c_old(k, vector<double>(2));
//	vector<double> norm = dist_method(centroids, c_old);
//	int iterations = 0;
//	while (check(norm,epsilon))
//	{
//		iterations += 1;
//		vector<vector<vector<int>>> assigned(k);
//		for (int i = 0; i < coord.size(); i++)
//		{
//			int j = argminD(coord[i][0], coord[i][1], centroids);
//			assigned[j].resize(assigned[j].size()+1);
//			assigned[j][assigned[j].size() - 1].push_back(coord[i][0]);
//			assigned[j][assigned[j].size() - 1].push_back(coord[i][1]);
//		}
//		c_old = centroids;
//		for (int i = 0; i < k; i++)
//		{
//			centroids[i] = mean(assigned[i]);
//			if (verify)
//				centroids[i] = c_old[i];
//		}
//		norm = dist_method(centroids, c_old);
//	}
//	return centroids;
//}
//int main()
//{
//	ifstream  fin("mask_1.csv");
//	string value;
//	bool kek = true;
//	while (getline(fin, value))
//		convert(value);
//	size_x += 20, size_y += 20;
//	size_x = size_y = max(size_x, size_y);
//	vector<vector<double>> centroids = kmeans(2, 0);
//	system("pause");
//	return 0;
//}
//#include "opencv2/highgui.hpp"
//#include "opencv2/core.hpp"
//#include "opencv2/imgproc.hpp"
//#include <iostream>
//
//using namespace cv;
//using namespace std;

// static void help()
// {
//     cout << "\nThis program demonstrates kmeans clustering.\n"
//             "It generates an image with random points, then assigns a random number of cluster\n"
//             "centers and uses kmeans to move those cluster centers to their representitive location\n"
//             "Call\n"
//             "./kmeans\n" << endl;
// }
//
//int main(int /*argc*/, char** /*argv*/)
//{
//	const int MAX_CLUSTERS = 5;
//	Scalar colorTab[] =
//	{
//		Scalar(0, 0, 255),
//		Scalar(0,255,0),
//		Scalar(255,100,100),
//		Scalar(255,0,255),
//		Scalar(0,255,255)
//	};
//
//	Mat img(500, 500, CV_8UC3);
//	RNG rng(12345);
//
//	for (;;)
//	{
//		int k, clusterCount = rng.uniform(2, MAX_CLUSTERS + 1);
//		int i, sampleCount = rng.uniform(1, 1001);
//		Mat points(sampleCount, 1, CV_32FC2), labels;
//
//		clusterCount = MIN(clusterCount, sampleCount);
//		Mat centers;
//
//		/* generate random sample from multigaussian distribution */
//		for (k = 0; k < clusterCount; k++)
//		{
//			Point center;
//			center.x = rng.uniform(0, img.cols);
//			center.y = rng.uniform(0, img.rows);
//			Mat pointChunk = points.rowRange(k*sampleCount / clusterCount,k == clusterCount - 1 ? sampleCount : (k + 1)*sampleCount / clusterCount);
//			rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols*0.05, img.rows*0.05));
//		}
//
//		randShuffle(points, 1, &rng);
//
//		kmeans(points, clusterCount, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),3, KMEANS_PP_CENTERS, centers);
//
//		img = Scalar::all(0);
//
//		for (i = 0; i < sampleCount; i++)
//		{
//			int clusterIdx = labels.at<int>(i);
//			Point ipt = points.at<Point2f>(i);
//			circle(img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA);
//		}
//
//		imshow("clusters", img);
//
//		char key = (char)waitKey();
//		if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
//			break;
//	}
//
//	return 0;
//}

//
// пример использования функции cvFloodFill()
// для заливки области
// начальный пиксель области выбирается по клику мышкой
//



//TRANSPARENCY

//#include<opencv2/opencv.hpp>
//
//#include<iostream>
//#include<vector>
//#include<stdint.h>
//#include<conio.h>
//#include<math.h>
//#include<algorithm>
//#include<fstream>
//#include<windows.h>
//#include<string>
//using namespace std;
//using namespace cv;
//pair<double, double> rotate(double x, double y, double a)
//{
//	pair<double, double> coord;
//	//coord.first= x*cos(a) + y*sin(a);
//	//coord.second = -x*sin(a) + y*cos(a);
//	coord.first = x*cos(a) - y*sin(a);
//	coord.second = x*sin(a) + y*cos(a);
//	return coord;
//}
//float rad(float angle)
//{
//	float pi = acos(-1);
//	return pi*angle / 180;
//}
//int main(int argc, char* argv[])
//{
//	Scalar colorTab[] =
//	{
//
//		Scalar(0, 0, 255),
//		Scalar(0,255,0),
//		Scalar(255,100,100),
//		Scalar(255,0,255),
//		Scalar(0,255,255)
//	};
//	Mat asdasdasd;
//	if (countNonZero(asdasdasd) < 1)
//	{
//		cout << "Eye contact occurs in this frame" << endl;
//	}
//	Mat kak/* = cv::Mat(200, 200, CV_8UC3, cv::Scalar(255, 0, 0));*/;
//	imshow("kak", kak);
//	waitKey(0);
//	Mat output = imread("0.jpg"), overlay = imread("0.jpg");
//	rectangle(overlay, Point(output.cols / 2, output.rows / 2), Point(output.cols, output.rows), Scalar(0, 0, 255), -1);
//	float alpha = 0.5;
//	addWeighted(overlay, alpha, output, 1 - alpha, 0, output);
//	imshow("output", output);
//	Mat img = imread("0.jpg");
//	Point v[4];
//	//v[0] = Point(img.cols / 4., img.rows / 4.);
//	//v[1] = Point(3 * img.cols / 4., img.rows / 4.);
//	//v[3] = Point(img.cols / 4., 3 * img.rows / 4.);
//	//v[2] = Point(3 * img.cols / 4., 3 * img.rows / 4.);
//
//	float angle = rad(70);
//	vector<pair<float, float>> coords, rot, pop;
//	//pop.push_back(make_pair<float>(img.cols / 4., img.rows / 4.));
//	//pop.push_back(make_pair<float>(3 * img.cols / 4., img.rows / 4.));
//	//pop.push_back(make_pair<float>(img.cols / 4., 3 * img.rows / 4.));
//	//pop.push_back(make_pair<float>(3 * img.cols / 4., 3 * img.rows / 4.));
//	pop.push_back(make_pair<float>(img.cols / 8., img.rows / 8.));
//	pop.push_back(make_pair<float>(3 * img.cols / 4., img.rows / 8.));
//	pop.push_back(make_pair<float>(img.cols / 8., 3 * img.rows / 4.));
//	pop.push_back(make_pair<float>(3 * img.cols / 4., 3 * img.rows / 4.));
//	float c_row = pop[3].second - pop[0].second;
//	float c_col = pop[3].first - pop[0].first;
//	rot.push_back(rotate(img.cols / 8. - c_col, img.rows / 8. - c_row, -angle));
//	rot.push_back(rotate(3 * img.cols / 4. - c_col, img.rows / 8. - c_row, -angle));
//	rot.push_back(rotate(img.cols / 8. - c_col, 3 * img.rows / 4. - c_row, -angle));
//	rot.push_back(rotate(3 * img.cols / 4. - c_col, 3 * img.rows / 4. - c_row, -angle));
//	v[0] = Point(rot[0].first + c_col, rot[0].second + c_row);
//	v[1] = Point(rot[1].first + c_col, rot[1].second + c_row);
//	v[2] = Point(rot[3].first + c_col, rot[3].second + c_row);
//	v[3] = Point(rot[2].first + c_col, rot[2].second + c_row);
//	circle(img, v[2], 10, colorTab[1], FILLED, LINE_AA);
//
//	const char* folder[] = { "gradient" };
//	fillConvexPoly(img, v, 4, Scalar(0, 0, 255));
//	imshow("img", img);
//
//		// Failed to create directory.
//		//imwrite(folder+"\\"+ "img.jpg", img);
//	waitKey(0);
//}
#pragma warning(disable: 4244)
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include<iostream>
#include<vector>
#include<stdint.h>
#include<conio.h>
#include<math.h>
#include<algorithm>
#include<random>
#include<fstream>
#include<windows.h>
#include<string>
#include<memory>
#define pi acos(-1)
using namespace std;
using namespace cv;
//pair<double, double> rotate(double x, double y, double a)
//{
//	pair<double, double> coord;
//	coord.first = x*cos(a) - y*sin(a);
//	coord.second = x*sin(a) + y*cos(a);
//	return coord;
//}
//double to_rad(double a)
//{
//	return a*pi / 180.;
//}

//class A
//{
//public: 
//	mutable Mat img; 
//	Mat& get_img() const
//	{
//		return img;
//	}
//	void set_img( A &value) 
//	{
//		img = value.get_img();
//	}
//	void print() const
//	{
//		cout << (int)img.at<uchar>(100, 100)<<endl;
//	}
//};
//
//#include<utility>
//#include<unordered_map>
//#include<random>
//std::vector<cv::Point>  generate_rectangle(std::vector<cv::Point> set, Mat &img)
//{
//	if (set.size() < 4)
//		return{ Point(1,1) };
//	std::random_device rd;
//	/* Random number generator */
//	std::default_random_engine generator(rd());
//	/* Distribution on which to apply the generator */
//	std::uniform_int_distribution<long long unsigned> distribution(0, set.size()-1);
//	int n = distribution(generator);
//	int asd = distribution(generator);
//	vector<int> indices = { n,asd };
//	cv::Point v1 = set[indices[0]];
//	cv::Point v2 = set[indices[0] != indices[1] ? indices[1] : (indices[1] + 1) % set.size()];
//	std::unordered_map<int, std::unordered_map<int, bool>> in_map;
//	in_map.reserve(set.size());
//
//	clock_t begin = clock();
//	for (int i = 0; i < set.size(); i++)
//		in_map[set[i].x][set[i].y] = true;
//	clock_t end = clock();
//	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//	cout << elapsed_secs<<" in map time"<<endl;
//	//y = kx+b 
//
//	//float k = float(v1.y - v2.y) / (v1.x - v2.x);
//	float k = float(v2.y - v1.y) / (v2.x - v1.x);
//
//	if (k == 0)
//		return{ Point(0,0) };
//	
//	//perpendicular to y k1 = -1/k 
//	// y = -1/k * x + b
//	float k1 = -1 / k;
//	float b1 = v1.y - k1*v1.x;
//	float b2 = v2.y - k1*v2.x;
//
//	std::unordered_map<int, std::unordered_map<int, bool>> in_line1, in_line2;
//	std::vector<cv::Point> line, line1, line2, p_line;
//
//	//for (int i = 0; i < set.size(); i++)
//	//{
//	//	if (set[i].y == (int)(k1*set[i].x + b1))
//	//	{
//	//		if (!in_line1[set[i].x][set[i].y])
//	//			line1.push_back(set[i]), in_line1[set[i].x][set[i].y] = true;
//	//	}
//	//	if (set[i].y == (int)(k1*set[i].x + b2))
//	//	{
//	//		if (!in_line2[set[i].x][set[i].y])
//	//			line2.push_back(set[i]), in_line2[set[i].x][set[i].y] = true;
//	//	}
//	//}
//	for (int x = 0; x < img.cols; x++)
//	{
//		int y1 = (int)(k1*x + b1);
//		int y2 = (int)(k1*x + b2);
//		if(in_map[x][y1])
//			if (!in_line1[x][y1])
//				line1.push_back(Point(x,y1)), in_line1[x][y1] = true;
//		if (in_map[x][y2])
//			if (!in_line2[x][y2])
//				line2.push_back(Point(x, y2)), in_line2[x][y2] = true;
//	}
//
//	for (int i = 0; i < line1.size(); i++)
//	{
//		float b = line1[i].y - k*line1[i].x;
//		float x1 = (b - b2) / (k1 - k);
//		int y = (int)(k1*x1 + b2);
//		int x = (int)x1;
//		if (in_line2[x][y])
//			line.push_back(cv::Point(line1[i].x, line1[i].y)),
//			p_line.push_back(cv::Point(x, y));
//	}
//
//	if (line.size() < 4)
//		return{ Point(0,0) };
//
//	cv::Point v3, v4;
//	int index = rand() % line.size();
//	v3 = line[index];
//	v4 = p_line[index];
//	return{ v1,v2,v3,v4 };
//}
//typedef std::vector< float > Genome;
//void rotation(cv::Point2f& shape, const float angle) 
//{
//	Point2f tmp;
//	tmp.x = shape.x * cos(angle) - shape.y * sin(angle);
//	tmp.y = shape.x * sin(angle) + shape.y * cos(angle);
//	shape = tmp;
//}
//Genome calculate_genetic_code(std::vector<cv::Point> v, Mat& picture)
//{
//	///let's take with rotation for now
//	Genome parameters(7);
//	auto distance = [](cv::Point a, cv::Point b)->double
//	{
//		return cv::sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
//	};
//
//	int width = picture.rows;
//	int height = picture.cols;
//
//	vector<Point2f> rectangle(4);
//	vector<Point2f> tmp(4);
//
//	for (unsigned int i = 0; i < 4; i++)
//		rectangle[i].x = v[i].x, rectangle[i].y = v[i].y;
//
//	float c_x = (rectangle[0].x + rectangle[3].x) / 2.f,
//		c_y = (rectangle[3].y + rectangle[0].y) / 2.f;
//
//	///let's find the angle
//
//		std::vector<float> vector = { (float)c_x -(rectangle[0].x + rectangle[2].x) / 2.f ,
//			(float)c_y -(rectangle[0].y + rectangle[2].y) / 2.f  };
//
//
//		Point asd((rectangle[0].x + rectangle[2].x) / 2, (rectangle[0].y + rectangle[2].y) / 2);
//
//		circle(picture, asd, 2, Scalar(238, 10, 255),2);
//
//		float tan = (float)vector[1]/vector[0];
//		float angle = atan(tan);
//
//	///rotate rectangle to get the corner coordinates
//	for (unsigned int i = 0; i < 4; i++)
//	{
//		//moving to the first vertex to the origin
//		tmp[i].x = rectangle[i].x - c_x;
//		tmp[i].y = rectangle[i].y - c_y;
//		//rotate on angle
//		rotation(tmp[i], -angle);
//		// move to the initial position
//		tmp[i].x += c_x;
//		tmp[i].y += c_y;
//	}
//	///parameters 5 and 6 = 0, beacuse we don't need heatmap
//	///and unexplored genes
//	bool check = true;
//	for (auto kek : tmp)
//		if (kek.x<0 || kek.y<0 || kek.x>width || kek.y>height)
//			check = false;
//	if (check)
//	{
//		for (int i =0; i < tmp.size();  i++)
//		{
//			if (i == 0 || i == 1)
//				circle(picture, tmp[i], 2, Scalar(130, 0, 75),2);
//			else
//				circle(picture, tmp[i], 2, Scalar(0, 0, 0), 2);
//		}
//	}
//	parameters[4] = angle * 180 / pi
//		, parameters[5] = 0, parameters[6] = 0;
//
//	parameters[0] = (float)tmp[0].x / width;
//	parameters[1] = (float)tmp[0].y / height;
//	auto side1 = distance(v[0], v[1]);
//	///it's not diagonal
//	auto side2 = distance(v[0], v[2]);
//	auto length = width>height? width:height;
//	parameters[2] = (float)side1 / length;
//	parameters[3] = (float)side2 / length;
//	return parameters;
//}
//
//int main()
//{
//
//	//mean_scaled.convertTo(mean_scaled, CV_8UC1, 255);
//	Mat src, src_gray, dst;
//	int kernel_size = 3;
//	int scale = 1;
//	int delta = 0;
//	int ddepth = CV_16S;
//	char* window_name = "Laplace Demo";
//
//	int c;
//
//	/// Load an image
//	src = imread("apple.jpg");
//
//	if (!src.data)
//	{
//		return -1;
//	}
//
//	/// Remove noise by blurring with a Gaussian filter
//	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
//
//	/// Convert the image to grayscale
//	cvtColor(src, src_gray, CV_BGR2GRAY);
//
//	/// Create window
//	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
//
//	/// Apply Laplace function
//	Mat abs_dst;
//
//	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
//	//Sobel(src_gray, dst, ddepth, 0,1,3, scale, delta, BORDER_DEFAULT);
//
//	convertScaleAbs(dst, abs_dst);
//
//	/// Show what you got
//	imshow(window_name, abs_dst);
//	imwrite("apple_gradient.jpg", abs_dst);
//	waitKey(0);
//
//	return 0;
//
//	//cv::Mat heatmap = imread("DKuk2ZKVoAA-8QC.jpg");
//	//std::vector<std::unordered_map<std::string,
//	//	std::pair<Point, Point >>> lol(3);
//	//lol[0]["left"] = make_pair(Point(0, 0), Point(20, 20));
//	//lol[2]["right"] = make_pair(Point(0, 0), Point(20, 2));
//	//std::array< cv::Point2f, 3 > from, to;
//	//from[0] = Point2f(0, 0);
//	//from[1] = Point2f(heatmap.size().width, 0);
//	//from[2] = Point2f(heatmap.size().width, heatmap.size().height);
//	//573 9 33 32
//	//573 9
//	//606 9
//	//606 41
//	//573 41
//
//	//573 -11
//	//606 -11
//	//606 41
//	//to[0] = Point2f(573, 9);
//	//to[1] = Point2f(606, 9);
//	//to[2] = Point2f(606, 41);
//	//to[0] = Point2f(573, -11);
//	//to[1] = Point2f(606, -11);
//	//to[2] = Point2f(606, 41);
//	//to[0] = Point2f(0, heatmap.size().height / 2);
//	//to[1] = Point2f(heatmap.size().width / 2, heatmap.size().height/2);
//	//to[2] = Point2f(heatmap.size().width / 2, heatmap.size().height);
//
//	//const auto transform = cv::getAffineTransform(
//	//	from.data(),
//	//	to.data());
//	//cv::warpAffine(heatmap, lol,
//	//	transform, cv::Size(
//	//		static_cast< int >(heatmap.rows),
//	//		static_cast< int >(heatmap.cols)),
//	//	/*don't invert*/ cv::WARP_INVERSE_MAP,
//	//	cv::BORDER_CONSTANT,
//	//	heatmap.at< cv::Vec3b >(cv::Point(0, 0)));
//	//cout << heatmap.size() << endl;
//	//cv::Mat show = heatmap(Rect(Point(573, 9), Size(33, 32)));
//	//imshow("lol", lol);
//	//imshow("org", heatmap);
//	//imshow("logo", show);
//	//cout << heatmap.size()<<endl;
//	//{
//	//	clock_t begin = clock();
//	//	int max_i = 0;
//	//	int min_i = 255;
//	//	//for (int i = 0; i < heatmap.rows; i++)
//	//	//{
//	//	//	for (int j = 0; j < heatmap.cols; j++)
//	//	//	{
//	//	//		if (max_i < (int)heatmap.at<uint8_t>(i, j))
//	//	//			max_i = (int)heatmap.at<uint8_t>(i, j);
//	//	//		if (min_i > (int)heatmap.at<uint8_t>(i, j))
//	//	//			min_i = (int)heatmap.at<uint8_t>(i, j);
//	//	//	}
//	//	//}
//	//	int n = heatmap.rows;
//	//	int m = heatmap.cols;
//	//	for (int i = 0; i < n; i++)
//	//	{
//	//		const uint8_t* p = heatmap.ptr<uint8_t>(i);
//	//		for (int j = 0; j < m; j++)
//	//		{
//	//			if (max_i < (int)*(p + j))
//	//				max_i = (int)*(p+j);
//	//			if (min_i > (int)*(p + j))
//	//				min_i = (int)*(p + j);
//	//		}
//	//	}
//	//	clock_t end = clock();
//	//	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//	//	cout << elapsed_secs << " time for my max" << endl;
//	//}
//	//{
//	//	clock_t begin = clock();
//	//	double min, max;
//	//	cv::minMaxLoc(heatmap, &min, &max);
//	//	clock_t end = clock();
//	//	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//	//	cout << elapsed_secs << " time cv's max" << endl;
//	//}
//
//	//cv::Mat display;
//	//const auto colormap = cv::COLORMAP_JET;
//	//cv::applyColorMap(heatmap, display, colormap);
//	//imwrite("heatmap.png", display);
//	//heatmap.convertTo(heatmap, CV_32FC1,1/255.f);
//
//	//circle(display, Point(160, 135), 2, Scalar(255, 255, 255), 2);
//	//circle(display, Point(59,135), 2, Scalar(255, 255, 255), 2);
//	//circle(display, Point(161, 12), 2, Scalar(255, 255, 255), 2);
//	//circle(display, Point(61, 12), 2, Scalar(255, 255, 255), 2);
//
//	//circle(display, Point(140, 135), 2, Scalar(0, 0, 0), 2);
//	//circle(display, Point(44, 117), 2, Scalar(0, 0, 0), 2);
//	//circle(display, Point(178, 30), 2, Scalar(0, 0, 0), 2);
//	//circle(display, Point(82, 0), 2, Scalar(0, 0, 0), 2);
//
//	//circle(display, Point(46 ,119), 2, Scalar(0, 255, 0), 2);
//	//circle(display, Point(53, 19), 2, Scalar(0, 255, 0), 2);
//	//circle(display, Point(177, 28), 2, Scalar(0, 255, 0), 2);
//	//circle(display, Point(169, 128), 2, Scalar(0, 255, 0), 2);
//	//imshow("xd", display);
//	//waitKey(0);
//
//	//std::unordered_map<float, std::vector<cv::Point>> set;
//	//std::vector<float> keys;
//	//{
//	//	clock_t begin = clock();
//	//	for (int i = 0; i < heatmap.rows; i++)
//	//	{
//	//		for (int j = 0; j < heatmap.cols; j++)
//	//		{
//
//	//			if ((float)heatmap.at<float>(i, j) >= (float)0.2)
//	//			{
//	//				if (set[heatmap.at<float>(i, j)].size() == 0)
//	//					keys.push_back(heatmap.at<float>(i, j));
//	//				set[heatmap.at<float>(i, j)].push_back(cv::Point(j, i));
//	//			}
//
//	//		}
//	//	}
//	//	clock_t end = clock();
//	//	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//	//	cout << elapsed_secs << " time in main" << endl;
//	//}
//
//	//int aaaa = 0;
//	//for (auto key : keys)
//	//{ 
//
//	//	auto lol = generate_rectangle(set[key], display);
//	//	if (lol.size() == 4)
//	//	{
//	//		auto gene = calculate_genetic_code(lol, display);
//	//		aaaa++;
//	//		for (int i = 0; i < lol.size(); i++)
//	//		{
//	//			if (i == 0 || i == 1)
//	//				circle(display, lol[i], 2, Scalar(0, 255, 0), 2);
//	//			else
//	//				circle(display, lol[i], 2, Scalar(255, 255, 255), 2);
//	//		}
//	//		//imshow("rectangle"+to_string(aaaa), display);
//	//		//waitKey(0);
//	//	}
//
//	//}
//
//	//imshow("rectangle", display);
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//int main()
//{
//	unordered_map<int, unordered_map<int, bool>> z;
//	z[1][2] = true;
//	cout << z[1][2]<<" "<<z[2][2]<<endl;
//	//Mat kek = Mat(Size(100,100), CV_8UC3);
//	//for (int i = 0; i < 100; i++)
//	//	for (int j = 0; j < 100; j++)
//	//		kek.at<cv::Vec3b>(i, j)[0] = 0,
//	//		kek.at<cv::Vec3b>(i, j)[1] = 0,
//	//		kek.at<cv::Vec3b>(i, j)[2] = 255;
//	//imshow("kek", kek);
//	//Point lol;
//	//cout << lol.x;
//	//cv::Mat source_image = cv::imread("suit.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//	//cout << source_image.type()<<endl;
//	//Point v[4];
//	//v[0] = Point(source_image.cols / 4., source_image.rows / 4.);
//	//v[1] = Point(3 * source_image.cols / 4., source_image.rows / 4.);
//	//v[3] = Point(source_image.cols / 4., 3 * source_image.rows / 4.);
//	//v[2] = Point(3 * source_image.cols / 4., 3 * source_image.rows / 4.);
//	//Mat overlay = Mat::zeros(source_image.size(), source_image.type());
//	//imshow("ad", overlay);
//	//fillConvexPoly(overlay, v, 4, 255);
//
//	//imshow("a", overlay);
//
//	//uint8_t cost = 122;
//	//for (int i = 0; i < overlay.rows; i++)
//	//{
//	//	for (int j = 0; j < overlay.cols; j++)
//	//	{
//	//		if (overlay.at<uint8_t>(i, j) == 255)
//	//		{
//	//			if (source_image.at<uint8_t>(i, j) < cost)
//	//				source_image.at<uint8_t>(i, j) = cost;
//	//		}
//	//	}
//	//}
//	//imshow("asd", source_image);
//	////Mat asd = imread("suit.jpg");
//	////Mat crop = asd(Rect(Point(45, 1), Size(29, 1)));
//	////imshow("org", asd);
//	////imshow("cropped", crop);
//	////cv::resizeWindow("cropped", Size(600, 600));
//	waitKey(0);
//	system("pause");
//	return 0;
//	//	MyClass<10, 11, 12, 13, 14> x;
//	//	x.ftest();
//	//	system("pause");
//	//	return 0;
////	int z = 10;
////	int &x = z;
////	int l = 20;
////	A* a = new A();
////	if (a->a->empty())
////	{
////		Mat kek =Mat::zeros(200,200,0);
////		a->a = &kek;
////	}
////	if (countNonZero(*a->a) < 1)
////	{
////		Mat kek = Mat(300, 300, 0, Scalar(128));
////		a->a = &kek;
////		imshow("kek", *a->a);
////	}
//	//Mat kek = imread("0.jpg", CV_LOAD_IMAGE_UNCHANGED);
//	//cout << (int)kek.at<Vec3b>(100, 100)[1]<<endl;
//
//	//kek.convertTo(kek, CV_32FC3);
//	//Mat lol = Mat(200, 200, CV_32FC1, Scalar_<float>(0.6));
//	//cout << lol.at<float>(100.100)<<endl;
//	//cvtColor(lol, lol, CV_GRAY2BGR);
//	//cout << lol.type() << endl;
//	//cout << lol.at<Vec3f>(100, 100)[0] << " " << lol.at<Vec3f>(100, 100)[1] << " " << lol.at<Vec3f>(100, 100)[2] << endl;
//	//cout << kek.at<cv::Vec3f>(100, 100)[1] << endl;
//	//cout << kek.channels() << endl;
//	//cvtColor(kek, kek, CV_BGR2BGRA);
//	//for (int i = 0; i < kek.rows; i++)
//	//{
//	//	for (int j = 0; j < kek.cols; j++) 
//	//	{
//	//		kek.at<Vec4b>(i, j)[3]=120;
//	//	}
//	//}
//	//cout << kek.channels() << endl;
//	//imshow("", kek);
//	//Mat img = Mat::zeros(400, 400, CV_8UC1);
//	//cout << img.channels() << endl;
//	//vector<pair<float, float>> pop;
//	//pop.push_back(rotate(img.cols / 8.f, img.rows / 8.f,to_rad(5)));
//	//pop.push_back(rotate(3 * img.cols / 4.f, img.rows / 8.f, to_rad(5)));
//	//pop.push_back(rotate(3 * img.cols / 4.f, 3 * img.rows / 4.f, to_rad(5)));
//	//pop.push_back(rotate(img.cols / 8.f, 3 * img.rows / 4.f, to_rad(5)));
//	//Point v[4];
//	//for (int i = 0; i < 4; i++)
//	//{
//	//	v[i] = Point(pop[i].first, pop[i].second);
//	//}
//	//fillConvexPoly(img, v, 4, Scalar(100),8,0);
//	//Mat dst;
//	//applyColorMap(img, dst, COLORMAP_JET);
//	//cvtColor(dst, dst, CV_BGR2BGRA);
//	//for (int i = 0; i < kek.rows; i++)
//	//{
//	//	for (int j = 0; j < kek.cols; j++)
//	//	{
//	//		kek.at<Vec4b>(i, j)[3] = 120;
//	//	}
//	//}
//	//cout << dst.type()<<endl;
//	//cout << dst.channels()<<endl;
//	//img.convertTo(img, CV_8UC1,255);
//	//imshow("IMG", img);
//	//imwrite("kek.jpg", img);
//	//Mat dst = imread("kek.jpg", CV_LOAD_IMAGE_UNCHANGED);
//	//dst.convertTo(dst, CV_32FC1,1/255.f);
//	//imshow("dst", dst);
//	//for (int i = 0; i < dst.rows; i++)
//	//{
//	//	for (int j = 0; j < dst.cols; j++)
//	//	{
//	//		int x = dst.at<uchar>(i, j);
//	//		cout << x << " ";
//	//	}
//	//	cout << endl;
//	//}
//	//cout << dst.elemSize1() << endl;
//	//cv::Mat sum = cv::Mat(200, 200, CV_32FC1,Scalar(0));
//	//cout << sum.at<float>(sum.rows / 2, sum.cols / 2)<<endl;
//	//Mat kek = Mat::zeros(200, 200, CV_32FC1);
//	//Mat count = Mat::zeros(200, 200, CV_8UC1);
//	//Scalar_<float> value = Scalar_<float>(0.5);
//	//vector<pair<float, float>> pop;
//	//pop.push_back(make_pair<float>(sum.cols / 8.f, sum.rows / 8.f));
//	//pop.push_back(make_pair<float>(3 * sum.cols / 4.f, sum.rows / 8.f));
//	//pop.push_back(make_pair<float>(3 * sum.cols / 4.f, 3 * sum.rows / 4.f));
//	//pop.push_back(make_pair<float>(sum.cols / 8.f, 3 * sum.rows / 4.f));
//	//for (int i = 0; i < sum.rows; i++)
//	//{
//	//	for (int j = 0; j < sum.cols; j++)
//	//	{
//	//		sum.at<float>(i, j) = rand()%120/255.f;
//	//	}
//	//}
//	//cv::Point v[4];
//	//for (int i = 0; i < 4; i++)
//	//	v[i] = Point((int)pop[i].first, (int)pop[i].second);
//	//fillConvexPoly(kek, v, 4, value);
//	//cout << kek.at<float>(sum.rows / 2, sum.cols / 2)<<endl;
//	//cout << sum.at<float>(sum.rows / 2, sum.cols / 2) << endl;
//	//addWeighted(sum, 1, kek, 1,0, kek);
//	//cout << kek.at<float>(sum.rows / 2, sum.cols / 2) << endl;
//	//imshow("kek", kek);
//	//waitKey(0);
//	//Mat dst;
//	//for (int i = 0; i < sum.rows; i++)
//	//{
//	//	for (int j = 0; j < sum.cols; j++)
//	//	{
//	//		count.at<uchar>(i, j) = (int)255 * sum.at<float>(i, j);
//	//	}
//	//}
//	//applyColorMap(count, dst, COLORMAP_JET);
//	//imshow("sum", sum);
//}




#include<opencv2/opencv.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <math.h>
using namespace cv;
using namespace std;

// h/w
const float ideal_ratio = 0.7;

//void f()
//{
//  for (int k = 0; k < current.rows; k++)
//  {
//    for (int l = 0; l < current.cols; l++)
//    {
//      for (int z = 0; z < current.channels(); z++)
//      {
//        new_current.at<cv::Vec3b>(k, l)[z] = current.at<cv::Vec3b>(k, l)[z];
//      }
//    }
//  }
//
//  for (int k = 0; k <image1.rows; k++)
//  {
//    for (int l = 0; l < image1.cols; l++)
//    {
//      for (int z = 0; z < current.channels(); z++)
//      {
//        new_current.at<cv::Vec3b>(k + current.rows, l)[z] = image1.at<cv::Vec3b>(k, l)[z];
//      }
//    }
//  }
//
//  for (int k = 0; k <image2.rows; k++)
//  {
//    for (int l = 0; l < image2.cols; l++)
//    {
//      for (int z = 0; z < current.channels(); z++)
//      {
//        new_current.at<cv::Vec3b>(k + current.rows, image1.cols + l)[z] = image1.at<cv::Vec3b>(k, l)[z];
//      }
//    }
//  }
//}

Size2f F2_up(int i, int j, vector<float> k, Size2f size)
{
  int w = size.width;
  float x = k[i] * w / (k[i] + k[j]);
  float y = k[j] * x;
  return Size2f(w, size.height + y);
}
Mat Mat2_up(int i, int j, vector<float> k, vector<Mat> image, Mat current)
{
  int w = current.cols;
  float x = k[i] * w / (k[i] + k[j]);
  float y = k[j] * x;

  auto image_i = image[i];
  auto image_j = image[j];
  resize(image_i, image_i, Size(x, y));
  resize(image_j, image_j, Size(w - x, y));
  Mat output(Size(w, current.rows + y), current.type());

  for (int k = 0; k < current.rows; k++)
  {
    for (int l = 0; l < current.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k, l)[z] = current.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  for (int k = 0; k <image_i.rows; k++)
  {
    for (int l = 0; l < image_i.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k + current.rows, l)[z] = image_i.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  for (int k = 0; k <image_j.rows; k++)
  {
    for (int l = 0; l < image_j.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k + current.rows, image_i.cols + l)[z] = image_j.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  return output;
}

Size2f F2_side(int i, int j, vector<float> k, Size2f size)
{
  return Size2f(size.width + size.height / (k[i] + k[j]), size.height);
}

Mat Mat2_side(int i, int j, vector<float> k, vector<Mat> image, Mat current)
{
  int h = current.rows;
  float y = h / (k[i] * (1 / k[j] + 1 / k[i]));
  float x = h / (k[i] + k[j]);

  auto image_i = image[i];
  auto image_j = image[j];
  resize(image_j, image_j, Size(x, y));
  resize(image_i, image_i, Size(x, h - y));

  Mat output(Size(current.cols + x, h), current.type());

  for (int k = 0; k < current.rows; k++)
  {
    for (int l = 0; l < current.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k, l)[z] = current.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  for (int k = 0; k <image_i.rows; k++)
  {
    for (int l = 0; l < image_i.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k, l+current.cols)[z] = image_i.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  for (int k = 0; k <image_j.rows; k++)
  {
    for (int l = 0; l < image_j.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k + image_i.rows, current.cols + l)[z] = image_j.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  return output;
}

Size2f F1_up(int i, vector<float> k, Size size)
{
  return Size2f(size.width, k[i] * size.width + size.height);
}

Mat Mat1_up(int i, vector<float> k, vector<Mat> image, Mat current)
{
  int w = current.cols;
  int y = w*k[i];
  auto image_i = image[i];
  resize(image_i, image_i, Size(w, y));

  Mat output(Size(w, current.rows + y), current.type());

  for (int k = 0; k < current.rows; k++)
  {
    for (int l = 0; l < current.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k, l)[z] = current.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  for (int k = 0; k <image_i.rows; k++)
  {
    for (int l = 0; l < image_i.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k + current.rows, l)[z] = image_i.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  return output;
}

Size2f F1_side(int i, vector<float> k, Size2f size)
{
  return Size2f(size.width + size.height / k[i], size.height);
}

Mat Mat1_side(int i, vector<float> k, vector<Mat> image, Mat current)
{
  int h= current.rows;
  int x = h/k[i];
  auto image_i = image[i];
  resize(image_i, image_i, Size(x, h));

  Mat output(Size(current.cols + x, h), current.type());

  for (int k = 0; k < current.rows; k++)
  {
    for (int l = 0; l < current.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k, l)[z] = current.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  for (int k = 0; k <image_i.rows; k++)
  {
    for (int l = 0; l < image_i.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k , l + current.cols)[z] = image_i.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  return output;
}

vector<Mat> er(vector<Mat> images, int i, int j = -1)
{
  images.erase(images.begin() + i);
  if (j != -1)
    images.erase(images.begin() + j - 1);
  return images;
}
vector<float> er_k(vector<float> k, int i, int j = -1)
{
  k.erase(k.begin() + i);
  if (j != -1)
    k.erase(k.begin() + j - 1);
  return k;
}

struct info
{
  vector<int> indexes;
  bool side;
};

pair<float, vector<info>> arrange(vector<Mat> images, vector<float> k, Size2f current)
{
  vector<float> ratios;
  vector<vector<info>> inf;
  vector<info> infos;
  if (images.size() == 0)
  {
    info s;
    infos.push_back(s);
    auto lol = make_pair(current.height / current.width, infos);
    return lol;
  }

  for (int i = 0; i < images.size(); i++)
  {
    for (int j = i; j < images.size(); j++)
    {
      if (j == i)
      {
        info a, b;

        auto c = arrange(er(images, i), er_k(k, i), F1_up(i, k, current));
        ratios.push_back(c.first);
        inf.push_back(c.second);
        a.side = 0;
        a.indexes.push_back(i);

        c = arrange(er(images, i), er_k(k, i), F1_side(i, k, current));
        ratios.push_back(c.first);
        inf.push_back(c.second);
        b.side = 1;
        b.indexes.push_back(i);

        infos.push_back(a);
        infos.push_back(b);
        continue;
      }
      info a, b;

      auto c = arrange(er(images, i, j), er_k(k, i, j), F2_up(i, j, k, current));
      ratios.push_back(c.first);
      inf.push_back(c.second);
      a.side = 0;
      a.indexes.push_back(i);
      a.indexes.push_back(j);
      infos.push_back(a);

      c = arrange(er(images, i, j), er_k(k, i, j), F2_side(i, j, k, current));
      ratios.push_back(c.first);
      inf.push_back(c.second);
      b.side = 1;
      b.indexes.push_back(i);
      b.indexes.push_back(j);
      infos.push_back(b);
    }
  }

  float min = 100000000000;
  int index = 0;
  for (int i = 0; i < ratios.size(); i++)
  {
    if (abs(ratios[i] - ideal_ratio) < min)
    {
      min = abs(ratios[i] - ideal_ratio), index = i;
    }
  }
  inf[index].push_back(infos[index]);
  return make_pair(ratios[index], inf[index]);
}

Mat decode(vector<info> v, vector<float> k, vector<Mat> images, Mat image)
{
  for (int i = 0; i < v.size(); i++)
  {
    if (v[i].indexes.size() == 1)
    {
      if (v[i].side)
      {
        image = Mat1_side(v[i].indexes[0], k, images, image);
        //imshow("img", image);
        //waitKey(0);
        images.erase(images.begin() + v[i].indexes[0]);
        k.erase(k.begin() + v[i].indexes[0]);
      }
      if (!v[i].side)
      {
        image = Mat1_up(v[i].indexes[0], k, images, image);
        //imshow("img", image);
        //waitKey(0);
        images.erase(images.begin() + v[i].indexes[0]);
        k.erase(k.begin() + v[i].indexes[0]);
      }
    }
    if (v[i].indexes.size() == 2)
    {
      if (v[i].side)
      {
        image = Mat2_side(v[i].indexes[0], v[i].indexes[1], k, images, image);
        //imshow("img", image);
        //waitKey(0);
        images.erase(images.begin() + v[i].indexes[0]);
        images.erase(images.begin() + v[i].indexes[1] - 1);
        k.erase(k.begin() + v[i].indexes[0]);
        k.erase(k.begin() + v[i].indexes[1] - 1);
      }
      if (!v[i].side)
      {
        image = Mat2_up(v[i].indexes[0], v[i].indexes[1], k, images, image);
        //imshow("img", image);
        //waitKey(0);
        images.erase(images.begin() + v[i].indexes[0]);
        images.erase(images.begin() + v[i].indexes[1] - 1);
        k.erase(k.begin() + v[i].indexes[0]);
        k.erase(k.begin() + v[i].indexes[1] - 1);
      }
    }
  }

  return image;
}

int main()
{
  vector<Mat> images;
  for (int i = 0; i < 7; i++)
  {
    string filename = "image_" + to_string(i) + ".jpg";
    Mat read = cv::imread(filename);
    images.push_back(read);
  }

  vector<float> k;
  for (int i = 0; i < images.size(); i++)
  {
    k.push_back((float)images[i].rows / images[i].cols);
    resize(images[i], images[i], Size(100, k[i] * 100));
  }

  auto current = images[0];
  images.erase(images.begin() + 0);
  k.erase(k.begin() + 0);
  auto as = arrange(images, k, current.size());
  cout << as.first << endl;
  auto v = as.second;
  v.erase(v.begin());
  std::reverse(v.begin(), v.end());
  auto output = decode(v,k, images, current);
  imwrite("collge_07f.jpg",output);
  imshow("output", output);
  waitKey(0);
  system("pause");
}
