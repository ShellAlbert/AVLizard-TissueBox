#ifndef _CSK_TRACKER_H_
#define  _CSK_TRACKER_H_
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;

class CSK_Tracker
{
	
public:
	CSK_Tracker();
	~CSK_Tracker();

	void hann2d(Mat& m);
	Mat dense_guess_kernel(double digma, Mat x, Mat y);
	Mat dense_guess_kernel(double digma, Mat x);
	Mat get_subwindow(Mat im, Point pos, int* sz, Mat cos_window);
	bool tracker_update(Mat frame, Point &pos, Size target_sz);
	bool tracker_init(Mat frame, Point pos, Size target_sz);
	void tracke_one(ifstream &infile, Point pos_first, int frame_count, Size target_sz);
	
	Mat conj(Mat a);
	Mat c_div(Mat a, Mat b);//a./b
	Mat c_mul(Mat a, Mat b);//a.*b
	Mat fft2d(Mat src);

	void print_mat(Mat a, string file_name);//��ӡ����debug��
	void print_img(Mat a, string file_name);//��ӡͼƬ�Ҷ�ֵ

private:
	static const double padding;
	static const double output_sigma_factor;
	static const double sigma;
	static const double lambda;
	static const double interp_factor;
	
	Mat m_init_yf;
	Mat m_init_cos_window;
	Mat m_update_z;
	Mat m_update_alphaf;

	
};

#endif
