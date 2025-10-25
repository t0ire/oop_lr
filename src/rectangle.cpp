#include <cmath>  

#include "rectangle.h" 

namespace figures {

Rectangle::Rectangle() {
    vertices[0] = Point(-1, -1);  // лн
    vertices[1] = Point(1, -1);   // пн
    vertices[2] = Point(1, 1);    // пв
    vertices[3] = Point(-1, 1);   // лв
}

Rectangle::Rectangle(const Point& p1, const Point& p2, const Point& p3, const Point& p4) { 
    vertices[0] = p1;  // лн
    vertices[1] = p2;  // пн
    vertices[2] = p3;  // пв
    vertices[3] = p4;  // лв
}

Rectangle::Rectangle(const Rectangle& other) {
    for (int i = 0; i < 4; ++i) {
        vertices[i] = other.vertices[i];
    }
}

Rectangle::Rectangle(Rectangle&& other) noexcept {
    for (int i = 0; i < 4; ++i) {
        vertices[i] = std::move(other.vertices[i]);
    }
}

Rectangle& Rectangle::operator=(const Rectangle& other) { // = копия
    if (this != &other) {  
        for (int i = 0; i < 4; ++i) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;  
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept { // = перемещ
    if (this != &other) { 
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }
    return *this;  
}

bool Rectangle::operator==(const Figure& other) const {
    const Rectangle* rect = dynamic_cast<const Rectangle*>(&other);
    
    if (!rect) return false;
    
    for (int i = 0; i < 4; ++i) {
        //огрешность (1e-9) из-за погрешностей вычислений с double
        if (std::abs(vertices[i].x - rect->vertices[i].x) > 1e-9 ||
            std::abs(vertices[i].y - rect->vertices[i].y) > 1e-9) {
            return false;  //не совпадают
        }
    }
    return true;  //совпадают
}

Point Rectangle::geometricCenter() const {
    double centerX = 0, centerY = 0; 
    
    for (int i = 0; i < 4; ++i) {
        centerX += vertices[i].x;
        centerY += vertices[i].y;
    }
    
    return Point(centerX / 4.0, centerY / 4.0);
}

double Rectangle::area() const {
    //ширина между 0 и 1 верш
    double width = std::sqrt(std::pow(vertices[1].x - vertices[0].x, 2) + 
                            std::pow(vertices[1].y - vertices[0].y, 2));
    
    //высоты между 1 и 2 верш
    double height = std::sqrt(std::pow(vertices[2].x - vertices[1].x, 2) + 
                             std::pow(vertices[2].y - vertices[1].y, 2));
    
    return width * height;
}

void Rectangle::printVertices(std::ostream& os) const {
    os << "rectangle: ";  
    
    for (int i = 0; i < 4; ++i) {
        os << "(" << vertices[i].x << ", " << vertices[i].y << ")";
        if (i < 3) os << " ";  
    }
}

void Rectangle::readFromStream(std::istream& is) {
    for (int i = 0; i < 4; ++i) {
        is >> vertices[i].x >> vertices[i].y;
    }
}

Figure* Rectangle::clone() const {
    return new Rectangle(*this);
}

}
