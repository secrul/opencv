#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
    IplImage* img = cvLoadImage("/home/secrul/opencv_project/lena.jpeg");
    cvNamedWindow("lena");
    cvNamedWindow("out");
    cvShowImage("lena",img);
    IplImage* out = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,3);//分配空间，8位宽，3个管道

    cvSmooth(img,out,CV_GAUSSIAN,5,5);//高斯平滑，3X3模板

    cvShowImage("out",out);
    cvWaitKey(0);
    cvReleaseImage(&out);
    cvReleaseImage(&img);
    cvDestroyWindow("lena");
    cvDestroyWindow("out");
    return 0;
}
