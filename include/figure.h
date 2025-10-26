#pragma once

#include <iostream>
#include <cmath> 

namespace figures {

class Point {
public:
    double x, y;  
    Point(double x = 0, double y = 0) : x(x), y(y) {}  

    bool operator==(const Point& other) const {
        return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
    }   
    
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Point& point) {
        is >> point.x >> point.y;
        return is;
    }   
};

class Figure {
public:
    virtual ~Figure() = default; 
    
    virtual Point geometricCenter() const = 0;  // центр
    virtual double area() const = 0; // площадь
    virtual void printVertices(std::ostream& os) const = 0; // вывод
    virtual void readFromStream(std::istream& is) = 0;// ввод
    
    virtual Figure* clone() const = 0;//копия
    virtual bool operator==(const Figure& other) const = 0;//сравнение
    
    operator double() const { return area(); }//double для площади

    friend std::ostream& operator<<(std::ostream& os, const Figure& figure);
    friend std::istream& operator>>(std::istream& is, Figure& figure);
};

}
