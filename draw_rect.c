#include <cv.h>
#include <highgui.h>
#include <core.hpp>
#include <stdio.h>
#include <math.h>

int n = 4;
int flag = 0;
void my_mouse_callback(int event,int x,int y,int flags,void* param);

CvRect box;
CvPoint p1,p2;
int r = 0;
bool flag_line = false;
bool drawing_box = false;
bool drawing_line1 = false;
bool drawing_line2 = false;
bool drawing_circle = false;
bool drawing_ellipse = false;

void draw_box(IplImage* img,CvRect rect)
{
    cvRectangle(img,cvPoint(box.x,box.y),cvPoint(box.x + box.width,box.y + box.height),cvScalar(0x00,0x00,0xff));

}
void draw_line(IplImage* img,CvPoint p1,CvPoint p2)
{
    cvLine(img,p1,p2,cvScalar(0xff,0x00,0x00),1,8);
}
void draw_circle(IplImage* img,CvPoint p1, int r){
    cvCircle(img,p1,r,cvScalar(0x00,0x00,0xff),1,8);
}
void draw_ellipse(IplImage* img,CvBox2D box){
    cvEllipseBox(img,box,cvScalar(0x00,0x00,0xff),1,8,0);

}

int main(int argc,char **argv)
{
    box = cvRect(-1,-1,0,0);
    box2 = CvBox2D()
    IplImage * image = cvCreateImage(cvSize(1200,1200),IPL_DEPTH_8U,3);
    cvZero(image);
    cvNot(image,image);
    IplImage* temp = cvCloneImage(image);
    cvNamedWindow("Example");
    cvSetMouseCallback("Example",my_mouse_callback,(void *)  image);
    CvFont font;
    cvInitFont(&font,CV_FONT_HERSHEY_COMPLEX,0.5,0.5,0,1,8);
    while(1)
    {
        cvCopy(image,temp);
        switch(flag)
        {
        case 0:
        {
            cvPutText(temp,"rect",cvPoint(10,10),&font,cvScalar(0xff,0x00,0x00));
            if(drawing_box) draw_box(temp,box);

        }
        break;
        case 1:
        {
            cvPutText(temp,"curl line",cvPoint(10,10),&font,cvScalar(0xff,0x00,0x00));
            if(drawing_line1) draw_line(temp,p1,p2);

        }
        break;
        case 2:
        {   cvPutText(temp,"straight line",cvPoint(10,10),&font,cvScalar(0xff,0x00,0x00));
            if(drawing_line2) draw_line(temp,p1,p2);

        }
        break;
        case 3:
        {   cvPutText(temp,"circle",cvPoint(10,10),&font,cvScalar(0xff,0x00,0x00));
            if(drawing_circle) draw_circle(temp,p1,r);

        }
        break;
        case 4:
        {   cvPutText(temp,"circle",cvPoint(10,10),&font,cvScalar(0xff,0x00,0x00));
            if(drawing_ellipse) draw_ellipse(temp,box);

        }
        break;
        }
        cvShowImage("Example",temp);

        if(cvWaitKey(15) == 27) break;

    }
    cvReleaseImage(&image);
    cvReleaseImage(&temp);
    cvDestroyWindow("Example");
}
void my_mouse_callback(int event,int x,int y,int flags,void* param)
{
    IplImage * image = (IplImage*) param;
    switch(flag)
    {
    case 0:
    {
        //rect
        switch(event)
        {
        case CV_EVENT_LBUTTONDBLCLK:
        {
            if (flag >= n )
            {
                flag = 0;
            }
            else
                flag ++;
        }
        break;
        case CV_EVENT_MOUSEMOVE:
        {
            if(drawing_box)
            {
                box.width = x - box.x;
                box.height = y - box.y;
            }
        }
        break;
        case CV_EVENT_LBUTTONDOWN:
        {
            drawing_box= true;
            box = cvRect(x,y,0,0);
        }
        break;
        case CV_EVENT_LBUTTONUP:
        {
            drawing_box = false;
            if(box.width < 0)
            {
                box.x += box.width;
                box.width *= -1;
            }
            if(box.height < 0)
            {
                box.y += box.height;
                box.height *= -1;
            }
            draw_box(image,box);
        }
        break;
        }
    }
    break;
    case 1:
    {
        //curl
        switch(event)
        {
        case CV_EVENT_LBUTTONDBLCLK:
        {
            if (flag >= n )
            {
                flag = 0;
            }
            else
                flag ++;
        }
        break;
        case CV_EVENT_MOUSEMOVE:
        {
            if(drawing_line1)
            {
                p1.x = p2.x;
                p1.y = p2.y;
                p2.x= x;
                p2.y = y;
            }
            draw_line(image,p1,p2);
        }
        break;
        case CV_EVENT_LBUTTONDOWN:
        {
            drawing_line1= true;
            if(flag_line)
            {
                p1.x = p2.x;
                p1.y = p2.y;
                p2.x= x;
                p2.y = y;
            }
            else
            {
                p2.x = x;
                p2.y = y;
                p1.x = x;
                p1.y = y;
                flag_line = true;
            }
        }
        break;
        case CV_EVENT_LBUTTONUP:
        {
            draw_line(image,p1,p2);
        }

        break;
        case CV_EVENT_RBUTTONDOWN:
        {
            drawing_line1= false;
            flag_line = false;
        }
        break;
        }
    }
    break;
    case 2:
    {
        //line
        switch(event)
        {
        case CV_EVENT_LBUTTONDBLCLK:
        {
            if (flag >= n )
            {
                flag = 0;
            }
            else
                flag ++;
        }
        break;
        case CV_EVENT_MOUSEMOVE:
        {
            if(drawing_line2)
            {
                p2.x= x;
                p2.y = y;
            }
        }
        break;
        case CV_EVENT_LBUTTONDOWN:
        {
            drawing_line2= true;

            p2.x = x;
            p2.y = y;
            p1.x = x;
            p1.y = y;

        }
        break;
        case CV_EVENT_LBUTTONUP:
        {
            drawing_line2 = false;
            draw_line(image,p1,p2);
        }

        break;
        case CV_EVENT_RBUTTONDOWN:
        {
            drawing_line2= false;
        }
        break;
        }
    }
    break;
    case 3:{
        //circle
        switch(event)
        {
        case CV_EVENT_LBUTTONDBLCLK:
        {
            if (flag >= n )
            {
                flag = 0;
            }
            else
                flag ++;
        }
        break;
        case CV_EVENT_MOUSEMOVE:
        {
            if(drawing_circle)
            {
                r = (int)sqrt((p1.x - x)*(p1.x - x) + (p1.y - y)*(p1.y - y));
            }
        }
        break;
        case CV_EVENT_LBUTTONDOWN:
        {
            drawing_circle= true;
            p1.x = x;
            p1.y = y;
        }
        break;
        case CV_EVENT_LBUTTONUP:
        {
            drawing_circle = false;
            draw_circle(image,p1,r);
        }
        break;
        }
        case 4:{

        break;
        }
    }
    }

}




