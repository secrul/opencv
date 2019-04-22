#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

IplImage* doPyrDown(IplImage* in,int filter = CV_GAUSSIAN_5x5){//在这里用IPL_GAUSSIAN_5X5报错,X号小写
    assert(in->width%2 == 0 && in->height%2 == 0);
    IplImage* out = cvCreateImage(cvSize(in->width / 2, in->height / 2),in->depth,in->nChannels);
    cvPyrDown(in,out);//核心，金字塔分解法向下采样
    return out;
}

IplImage* doCanny(IplImage* in, double lowThresh,double highThresh,double aperture)
//边缘检测，只能适用于灰度图，所以打开图像时强制为灰度
//
{
    if(in->nChannels != 1) return 0;
    IplImage* out = cvCreateImage(cvGetSize(in),IPL_DEPTH_8U,1);

    cvCanny(in,out,lowThresh,highThresh,aperture);
    return out;
}

int main()
{
    IplImage* img = cvLoadImage("/home/secrul/opencv_project/lena.jpeg");
    cvNamedWindow("lena");
    cvNamedWindow("out1");
    cvShowImage("lena",img);
    IplImage* out1 = doPyrDown(img);//分配空间，8位宽，3个管道
    cvShowImage("out1",out1);
    cvWaitKey(0);
    cvReleaseImage(&out1);
    cvReleaseImage(&img);
    cvDestroyWindow("lena");
    cvDestroyWindow("out1");

    img = cvLoadImage("/home/secrul/opencv_project/lena.jpeg",0);
    cvNamedWindow("lena");
    cvNamedWindow("out2");
    cvShowImage("lena",img);
    IplImage* out2 = doCanny(img,10,100,3);
    cvShowImage("out2",out2);
    cvWaitKey(0);
    cvReleaseImage(&out2);
    cvReleaseImage(&img);
    cvDestroyWindow("lena");
    cvDestroyWindow("out2");
    return 0;
}
