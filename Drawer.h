//
// Created by n.puzikov on 14.10.2022.
//

#ifndef TEST_DRAWER_H
#define TEST_DRAWER_H

#include "TopPoint.h"

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

class DrawerColor{
public:
    unsigned char Alpha,R,G,B;
    DrawerColor(const unsigned char &Alpha = 255, const unsigned char &R = 0,
                const unsigned char &G = 0, const unsigned char &B = 0):Alpha(Alpha), R(R), G(G), B(B){}
};

class Drawer {
public:
    virtual void setColor(const DrawerColor &color) = 0;
    virtual void drawLine(const TopPoint &p1, const TopPoint &p2) = 0;
    virtual void drawRectangle(const TopPoint &pointTopRight, const int &width, const int &height) = 0;
    virtual void drawEllipse(const TopPoint &pointCenter, const int &horizontalAxis, const int &verticalAxis) = 0;
    virtual void drawCircle(const TopPoint &pointCenter, const int &R) = 0;
};

class gdiplusDrawer: public Drawer{
    Gdiplus::Graphics *g;
    Gdiplus::Pen *pen;
public:

    gdiplusDrawer(Gdiplus::Graphics *g){
        this->g = g;
        pen = new Gdiplus::Pen(Gdiplus::Color(255,0,0,0));
    }
    void setColor(const DrawerColor &color) override{
        pen->SetColor(Gdiplus::Color(color.Alpha, color.R, color.G, color.B));
    }

    void drawLine(const TopPoint &p1, const TopPoint &p2) override{
        g->DrawLine(pen, p1.x, p1.y, p2.x, p2.y);
    }
    void drawRectangle(const TopPoint &pointTopRight, const int &width, const int &height) override{
        g->DrawRectangle(pen, pointTopRight.x, pointTopRight.y, width, height);
    }
    void drawEllipse(const TopPoint &pointCenter, const int &horizontalSemiAxis, const int &verticalSemiAxis) override{
        g->DrawEllipse(pen, pointCenter.x - horizontalSemiAxis, pointCenter.y - verticalSemiAxis,
                      2* horizontalSemiAxis, 2*verticalSemiAxis);
    }
    void drawCircle(const TopPoint &pointCenter, const int &R) override{
        g->DrawEllipse(pen, pointCenter.x - R, pointCenter.y - R, 2*R, 2*R);
    }
};


#endif //TEST_DRAWER_H
