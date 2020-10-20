// opencv
#pragma warning(push)
#pragma warning ( disable : 4819 )
#include <opencv2/opencv.hpp>
#pragma warning(pop)

//
#include <Windows.h>

//
#include "putText_Jpn.h"

int main(int, char**)
{
	int result = -1;

	cv::Mat tmp_img(480, 450, CV_8UC3, cv::Scalar(64, 64, 64));

	if (!tmp_img.empty())
	{
		const TCHAR *p_ary_message[] = { TEXT("OpenCVÇ≈ì˙ñ{åÍï\é¶"), TEXT("ì˙ñ{åÍÇQ"), TEXT("∆Œ›∫ﬁ3"), TEXT("ÇdÇrÇbÇ≈èIóπ") };
		cv::Point ary_pos_org[4] = { cv::Point(10, 100), cv::Point(0, 150), cv::Point(100, 200), cv::Point(0, 300) };
		cv::Point pos_cv = cv::Point(320, 300);
		cv::Scalar font_color(255, 0, 255);
		double font_scale = 1.0;
		int thickness = 1;

		sc::myCV::putText_Jpn(tmp_img, p_ary_message[0], ary_pos_org[0], nullptr, font_scale, font_color, thickness);
		sc::myCV::putText_Jpn(tmp_img, p_ary_message[1], ary_pos_org[1], TEXT("ÇlÇr ÉSÉVÉbÉN"), font_scale, cv::Scalar(255, 0, 0), thickness);
		sc::myCV::putText_Jpn(tmp_img, p_ary_message[2], ary_pos_org[2], TEXT("ÇlÇr ÇoÉSÉVÉbÉN"), 1.5, cv::Scalar(0, 0, 255), thickness);
		sc::myCV::putText_Jpn(tmp_img, p_ary_message[3], ary_pos_org[3], TEXT("ÇlÇr ñæí©"), 2.0, cv::Scalar(255, 255, 0), thickness);

		cv::imshow("hoge", tmp_img);
		cv::waitKeyEx(0);

		cv::imwrite("opencv_nihongo.png", tmp_img);

		result = 0;
	}

	return result;
}
