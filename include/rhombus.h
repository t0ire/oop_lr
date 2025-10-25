#pragma once

#include "figure.h"  

namespace figures {

class Rhombus : public Figure {
private:
    Point vertices[4]; //вершины - лн пн пв лн
    
public:
    Rhombus();  
    Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Rhombus(const Rhombus& other);  //копия
    Rhombus(Rhombus&& other) noexcept;  //перемещ
    
    Rhombus& operator=(const Rhombus& other); //присваивание копиров
    Rhombus& operator=(Rhombus&& other) noexcept;  //присваивание пермещ
    
    bool operator==(const Figure& other) const override;  
    
    Point geometricCenter() const override; //центр
    double area() const override; //площадь

    void printVertices(std::ostream& os) const override; 
    void readFromStream(std::istream& is) override;    
    
    Figure* clone() const override;  
};

}