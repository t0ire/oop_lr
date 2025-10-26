#include <cmath>  
#include <initializer_list>

#include "rectangle.h" 

namespace figures {

Rectangle::Rectangle() 
    : vertices{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}} {}

Rectangle::Rectangle(const Point& p1, const Point& p2, const Point& p3, const Point& p4) 
    : vertices{p1, p2, p3, p4} {}

Rectangle::Rectangle(const Rectangle& other) {
    for (int i = 0; i < VERTICES_COUNT; ++i) {
        vertices[i] = other.vertices[i];
    }
}

Rectangle::Rectangle(Rectangle&& other) noexcept {
    for (int i = 0; i < VERTICES_COUNT; ++i) {
        vertices[i] = std::move(other.vertices[i]);
    }
}

Rectangle& Rectangle::operator=(const Rectangle& other) { // = копия
    if (this != &other) {  
        for (int i = 0; i < VERTICES_COUNT; ++i) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;  
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept { // = перемещ
    if (this != &other) { 
        for (int i = 0; i < VERTICES_COUNT; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }
    return *this;  
}

bool Rectangle::operator==(const Figure& other) const {
    const Rectangle* rect = dynamic_cast<const Rectangle*>(&other);
    
    if (!rect) return false;
    
    for (int i = 0; i < VERTICES_COUNT; ++i) {
        //огрешность (1e-9) из-за погрешностей вычислений с double
        if (!(vertices[i] == rect->vertices[i])) {
            return false;  //не совпадают
        }
    }
    return true;  //совпадают
}

Point Rectangle::geometricCenter() const {
    double centerX = 0, centerY = 0; 
    
    for (int i = 0; i < VERTICES_COUNT; ++i) {
        centerX += vertices[i].x;
        centerY += vertices[i].y;
    }
    
    return Point(centerX / VERTICES_COUNT, centerY / VERTICES_COUNT);
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
    
    for (int i = 0; i < VERTICES_COUNT; ++i) {
        os << vertices[i];
        if (i < 3) os << " ";  
    }
}

void Rectangle::readFromStream(std::istream& is) {
    for (int i = 0; i < VERTICES_COUNT; ++i) {
        is >> vertices[i];
    }
}

Figure* Rectangle::clone() const {
    return new Rectangle(*this);
}

}
