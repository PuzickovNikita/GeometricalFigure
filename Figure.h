//
// Created by n.puzikov on 13.10.2022.
//

#ifndef TEST_FIGURE_H
#define TEST_FIGURE_H
#include "Drawer.h"

#include <string>
#include <vector>

//TODO:проверка выхода за пределы окна
//TODO:добавить цвет
//TODO:добавить фон
//TODO:описать ошибки

enum class TopFigureType{
    NullFigure, Rectangel, Circle, Triangle, Polygon
};

class TopFigure{
private:
    virtual void drawDrawer(Drawer *drawer) = 0;
protected:
    TopFigureType type;
public:
    DrawerColor color;

    TopFigure(TopFigureType type, const DrawerColor &color): color(color){
        this->type = type;
    }
    virtual ~TopFigure() = default;

    void draw(Drawer *drawer){
        drawer->setColor(color);
        drawDrawer(drawer);
    }

    TopFigureType getFigureType() {
        return type;
    }
};

class TopRectangle: public TopFigure{
    TopPoint pointTopLeft;
    int width,height;


    void drawDrawer(Drawer *drawer) override;
public:
    TopRectangle(const int &x1, const int &y1, const int &width, const int &height,
                 const DrawerColor &color = DrawerColor()):
            TopFigure(TopFigureType::Rectangel, color), pointTopLeft(x1, y1){
        if ((width <= 0) || (height <= 0)){
            throw "Ошибка: Прямоугольник: неправильная длина стороны";
        }
        this->width = width;
        this->height = height;
    }

};
class TopCircle: public TopFigure{
    TopPoint pointCenter;
    int R;

    void drawDrawer(Drawer *drawer) override;
public:
    TopCircle(const int &x0,const int &y0, const int &R,
              const DrawerColor &color = DrawerColor()):
              TopFigure(TopFigureType::Circle, color), pointCenter(x0, y0){
        if (R <= 0){
            throw "Неверный радиус круга:" + std::to_string(R);
        }
        this->R = R;
    }
};

class TopIterableFigure: public TopFigure{
protected:
    std::vector<TopPoint> points;
public:
    TopIterableFigure(TopFigureType type, const DrawerColor &color): TopFigure(type, color){
    }
};

class TopTriangle: public TopIterableFigure{

    void drawDrawer(Drawer *drawer) override;
public:
    TopTriangle(const int &x1, const int &y1, const int &x2, const int &y2,
                const int &x3, const int &y3, const DrawerColor &color = DrawerColor()):
                TopIterableFigure(TopFigureType::Triangle, color){
        points.emplace_back(x1,y1);
        points.emplace_back(x2,y2);
        points.emplace_back(x3,y3);
    }
};

class TopPolygon: public TopIterableFigure{
    void drawDrawer(Drawer *drawer) override;
public:
    TopPolygon(const std::vector<TopPoint> &points, const DrawerColor &color = DrawerColor()):
            TopIterableFigure(TopFigureType::Polygon, color){
        this->points = points;
    }
    TopPolygon(std::vector<TopPoint> &&points, const DrawerColor &color = DrawerColor()):
            TopIterableFigure(TopFigureType::Polygon, color){
        this->points = points;
    }

};

#endif //TEST_FIGURE_H
