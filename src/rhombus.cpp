#include <cmath> 
#include <initializer_list> 

#include "rhombus.h"  

namespace figures {

Rhombus::Rhombus() 
    : vertices{{-1, 0}, {0, -1}, {1, 0}, {0, 1}} {} 

Rhombus::Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4) 
    : vertices{p1, p2, p3, p4} {}

Rhombus::Rhombus(const Rhombus& other) {
    for (int i = 0; i < VERTICES_COUNT; ++i) {
        vertices[i] = other.vertices[i];
    }
}

Rhombus::Rhombus(Rhombus&& other) noexcept {
    for (int i = 0; i < VERTICES_COUNT; ++i) {
        vertices[i] = std::move(other.vertices[i]);
    }
}

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {  
        for (int i = 0; i < VERTICES_COUNT; ++i) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this; 
}

Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) { 
        for (int i = 0; i < VERTICES_COUNT; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }
    return *this; 
}

bool Rhombus::operator==(const Figure& other) const {

    const Rhombus* rhomb = dynamic_cast<const Rhombus*>(&other);
    
    if (!rhomb) return false;
    
    for (int i = 0; i < VERTICES_COUNT; ++i) {
        //погрешность (1e-9) из-за погрешностей вычислений с double
        if (!(vertices[i] == rhomb->vertices[i])) {
            return false;  //не совпадают
        }
    }
    return true;  //совпадают
}

Point Rhombus::geometricCenter() const {
    double centerX = 0, centerY = 0;  
    
    for (int i = 0; i < VERTICES_COUNT; ++i) {
        centerX += vertices[i].x;
        centerY += vertices[i].y;
    }
    
    return Point(centerX / VERTICES_COUNT, centerY / VERTICES_COUNT);
}

double Rhombus::area() const {
    // длина между 2 и 0
    double d1 = std::sqrt(std::pow(vertices[2].x - vertices[0].x, 2) + 
                         std::pow(vertices[2].y - vertices[0].y, 2));
    
    //длина между 1 и 3
    double d2 = std::sqrt(std::pow(vertices[1].x - vertices[3].x, 2) + 
                         std::pow(vertices[1].y - vertices[3].y, 2));
    
    return (d1 * d2) / 2.0;
}

void Rhombus::printVertices(std::ostream& os) const {
    os << "rhombus: ";  
    
    for (int i = 0; i < VERTICES_COUNT; ++i) {
        os << vertices[i];
        if (i < 3) os << " ";  
    }
}

void Rhombus::readFromStream(std::istream& is) {
    for (int i = 0; i < VERTICES_COUNT; ++i) {
        is >> vertices[i];
    }
}

Figure* Rhombus::clone() const {
    return new Rhombus(*this);
}

}