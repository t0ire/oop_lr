#pragma once

#include "figure.h"

namespace figures {

class Trapezoid: public Figure {
private:
    static const int VERTICES_COUNT = 4;
    Point vertices[VERTICES_COUNT]; //вершины - лн пн пв лн

public:
    Trapezoid();
    Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Trapezoid(const Trapezoid& other); //копия
    Trapezoid(Trapezoid&& other) noexcept; //перемещ

    Trapezoid& operator=(const Trapezoid& other); //присваивание копиров
    Trapezoid& operator=(Trapezoid&& other) noexcept; //присваивание пермещ

    bool operator==(const Figure& other) const override;
    
    Point geometricCenter() const override;//центр
    double area() const override;//площадь

    void printVertices(std::ostream& os) const override;
    void readFromStream(std::istream& is) override;
    
    Figure* clone() const override;
};

}