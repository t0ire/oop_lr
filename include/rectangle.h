#pragma once

#include "figure.h"

namespace figures {

class Rectangle: public Figure {
private:
    static const int VERTICES_COUNT = 4;
    Point vertices[VERTICES_COUNT]; //вершины - лн пн пв лн

public:
    Rectangle();
    Rectangle(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Rectangle(const Rectangle& other); //копия
    Rectangle(Rectangle&& other) noexcept; //перемещ

    Rectangle& operator=(const Rectangle& other); //присваивание копиров
    Rectangle& operator=(Rectangle&& other) noexcept; //присваивание пермещ

    bool operator==(const Figure& other) const override;
    
    Point geometricCenter() const override;//центр
    double area() const override;//площадь

    void printVertices(std::ostream& os) const override;
    void readFromStream(std::istream& is) override;
    
    Figure* clone() const override;
};

}