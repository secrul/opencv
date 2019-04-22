#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace std;
using namespace cv;
/**
思路和展示图片一样，将视频的每一帧作为图片展示，问题是如何循环播放每一帧，以及如何退出
**/

int g_slider_pos = 0;
CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos){
    cvSetCaptureProperty(g_capture,CV_CAP_PROP_POS_FRAMES,pos);//CV_CAP_PROP_POS_FRAMES表示以帧数设置读入位置，CV_CAP_PROP_POS_AVI_RATIO表示视频比例确定位置
}

int main()
{
    cvNamedWindow("video",CV_WINDOW_AUTOSIZE);//创建窗口播放每一帧
    g_capture = cvCreateFileCapture("/home/secrul/opencv_project/test.mp4");//获取视频文件
    int frames = (int)cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);//获取视频的总帧数
    if(frames != 0){
        cvCreateTrackbar("position","video",&g_slider_pos,frames,onTrackbarSlide);
    }
    IplImage * frame;
    while(1){
        frame = cvQueryFrame(g_capture);//逐帧取出
        if(!frame) break;
        cvShowImage("video",frame);
        char c = cvWaitKey(33);
        g_slider_pos++;
        cvSetTrackbarPos("position","video",g_slider_pos);//总感觉会导致视频慢放
        if(c == 27) break;
        if(c == 32) cvWaitKey(0);//安空格键暂停
    }
    cvReleaseCapture(&g_capture);//释放文件
    cvDestroyWindow("video");//释放窗口
    return 0;
}
