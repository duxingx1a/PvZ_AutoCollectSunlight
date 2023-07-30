#include <OperationThread.h>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <atomic>
using namespace cv;
using namespace std;
OperationThread::OperationThread()
{
    this->runing=false;
}

void OperationThread::setRuning(bool runing)
{
    qDebug()<<"threadset runing1111"<<runing;
    this->runing = runing;

}

void Mouse_Move(int x, int y)
{
    double fScreenWidth = (::GetSystemMetrics(SM_CXSCREEN) - 1) * 1.25;
    double fScreenHeight = (::GetSystemMetrics(SM_CYSCREEN) - 1) * 1.25;
    double fx = x * (65535.0f / fScreenWidth);
    double fy = y * (65535.0f / fScreenHeight);
    mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, fx, fy, 0, 0);
}
void LeftClick()
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//鼠标左键按下
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//鼠标左键抬起
}
void OperationThread::run()
{
    //qDebug()<<"thread start";
    //INPUT input
    Mat sun=imread("sun.png",1);
    HWND targetWindow = FindWindow(NULL, L"植物大战僵尸中文版");
    while(1)
    {
        if(runing)
        {
            Mat screenshot;
            HDC hDC = GetDC(targetWindow);
            HDC hCaptureDC = CreateCompatibleDC(hDC);
            RECT windowRect;
            RECT rr;
            GetWindowRect(targetWindow, &rr);
            GetClientRect(targetWindow, &windowRect);
            int width = windowRect.right - windowRect.left;
            int height = windowRect.bottom - windowRect.top -80;
            screenshot.create(height, width, CV_8UC3);
            HBITMAP hBitmap = CreateCompatibleBitmap(hDC, width, height);
            SelectObject(hCaptureDC, hBitmap);
            BitBlt(hCaptureDC, 0, 0, width, height, hDC, 0, 80, SRCCOPY);
            BITMAPINFO bi;
            memset(&bi, 0, sizeof(bi));
            bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bi.bmiHeader.biWidth = width;
            bi.bmiHeader.biHeight = -height; // 负值表示图像是自顶向下的
            bi.bmiHeader.biPlanes = 1;
            bi.bmiHeader.biBitCount = 24; // 这里假设是24位真彩色图像，如果你的窗口是其他位数，需要调整此值
            bi.bmiHeader.biCompression = BI_RGB;
            bi.bmiHeader.biSizeImage = 0;
            GetDIBits(hCaptureDC, hBitmap, 0, height, screenshot.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
            // 释放资源
            DeleteDC(hCaptureDC);
            ReleaseDC(targetWindow, hDC);
            DeleteObject(hBitmap);
            Mat result;
            matchTemplate(screenshot, sun, result, TM_CCORR_NORMED);
            Point minLoc;
            Point maxLoc;
            Point matchLoc;
            double minVal = -1;
            double maxVal;
            minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
            matchLoc = maxLoc;
            Mat mask = screenshot.clone();
            rectangle(mask, Point(matchLoc.x, matchLoc.y), Point(matchLoc.x + sun.cols, matchLoc.y + sun.rows), (170, 234, 242), 4, 0);
            imshow("mask", mask);
            int x = rr.left*1.25 + matchLoc.x*1.25 +35;
            int y = rr.top*1.25 + matchLoc.y*1.25 +160;
            //qDebug()<<x<<","<<y;
            Mouse_Move(x, y);
            LeftClick();
            waitKey(20);
        }
        else
            continue;
    }
}
