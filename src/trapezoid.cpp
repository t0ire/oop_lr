#include <cmath>   

#include "trapezoid.h"

namespace figures {

Trapezoid::Trapezoid() {

    vertices[0] = Point(-1.5, -1);  //лн
    vertices[1] = Point(1.5, -1);   //пн
    vertices[2] = Point(1, 1);      //пв
    vertices[3] = Point(-1, 1);     //лв
}

Trapezoid::Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    vertices[0] = p1;  // лн
    vertices[1] = p2;  // пн
    vertices[2] = p3;  // пв
    vertices[3] = p4;  // лв
}

Trapezoid::Trapezoid(const Trapezoid& other) {
    for (int i = 0; i < 4; ++i) {
        vertices[i] = other.vertices[i];
    }
}

Trapezoid::Trapezoid(Trapezoid&& other) noexcept {
    for (int i = 0; i < 4; ++i) {
        vertices[i] = std::move(other.vertices[i]);
    }
}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {  
        for (int i = 0; i < 4; ++i) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this; 
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) { 
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }
    return *this; 
}

bool Trapezoid::operator==(const Figure& other) const {
    const Trapezoid* trap = dynamic_cast<const Trapezoid*>(&other);
    
    if (!trap) return false;
    
    for (int i = 0; i < 4; ++i) {
        // погрешность (1e-9) из-за погрешностей вычислений с double
        if (std::abs(vertices[i].x - trap->vertices[i].x) > 1e-9 ||
            std::abs(vertices[i].y - trap->vertices[i].y) > 1e-9) {
            return false;  //не совпадают
        }
    }
    return true;  //совпадают
}

Point Trapezoid::geometricCenter() const {
    double centerX = 0, centerY = 0;  
    
    for (int i = 0; i < 4; ++i) {
        centerX += vertices[i].x;
        centerY += vertices[i].y;
    }
    
    return Point(centerX / 4.0, centerY / 4.0);
}

double Trapezoid::area() const {
    // верх между 2 и 3 
    double topBase = std::sqrt(std::pow(vertices[3].x - vertices[2].x, 2) + 
                              std::pow(vertices[3].y - vertices[2].y, 2));
    
    // низ между 0 и 1
    double bottomBase = std::sqrt(std::pow(vertices[1].x - vertices[0].x, 2) + 
                                 std::pow(vertices[1].y - vertices[0].y, 2));
    
    // высота
    double height = std::abs(vertices[2].y - vertices[1].y);
    
    return (topBase + bottomBase) * height / 2.0;
}

void Trapezoid::printVertices(std::ostream& os) const {
    os << "trapezoid: ";  
    
    for (int i = 0; i < 4; ++i) {
        os << "(" << vertices[i].x << ", " << vertices[i].y << ")";
        if (i < 3) os << " ";  
    }
}

void Trapezoid::readFromStream(std::istream& is) {
    for (int i = 0; i < 4; ++i) {
        is >> vertices[i].x >> vertices[i].y;
    }
}

Figure* Trapezoid::clone() const {
    return new Trapezoid(*this);
}

}
