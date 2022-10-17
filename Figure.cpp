//
// Created by n.puzikov on 13.10.2022.
//

#include "Figure.h"

void TopRectangle::drawDrawer(Drawer *drawer) {
    drawer->drawRectangle(pointTopLeft, width, height);
}

void TopCircle::drawDrawer(Drawer *drawer) {
    drawer->drawCircle(pointCenter, R);
}

void TopTriangle::drawDrawer(Drawer *drawer) {
    drawer->drawLine(points[0],points[1]);
    drawer->drawLine(points[0],points[2]);
    drawer->drawLine(points[2],points[1]);
}

void TopPolygon::drawDrawer(Drawer *drawer) {
    auto it = points.begin(), prevIt = it++;
    drawer->drawLine(*prevIt,points.back());
    for(;it != points.end(); ++it, ++prevIt){
        drawer->drawLine(*it,*prevIt);
    }
}
