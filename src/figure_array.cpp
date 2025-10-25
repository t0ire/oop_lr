#include <iostream>

#include "figure_array.h"

namespace figures {

FigureArray::FigureArray() : count(0) {
    figures = Array(10, nullptr);  
}

FigureArray::FigureArray(const FigureArray& other) : count(other.count) {
    figures = Array(other.count, nullptr);
    for (size_t i = 0; i < count; ++i) {
        figures[i] = other.figures[i]->clone();  
    }
}

FigureArray::FigureArray(FigureArray&& other) noexcept 
    : figures(std::move(other.figures)), count(other.count) {
    other.count = 0;
}

FigureArray::~FigureArray() {
    for (size_t i = 0; i < count; ++i) {
        delete figures[i];  
    }
}

FigureArray& FigureArray::operator=(const FigureArray& other) {
    if (this != &other) {
        for (size_t i = 0; i < count; ++i) {
            delete figures[i];
        }
        
        count = other.count;
        figures = Array(count, nullptr);
        for (size_t i = 0; i < count; ++i) {
            figures[i] = other.figures[i]->clone();
        }
    }
    return *this;
}

FigureArray& FigureArray::operator=(FigureArray&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < count; ++i) {
            delete figures[i];
        }
        
        figures = std::move(other.figures);
        count = other.count;
        other.count = 0;
    }
    return *this;
}

void FigureArray::addFigure(Figure* figure) {
    if (count >= figures.size()) {
        figures.resize(figures.size() * 2);  
    }
    figures[count] = figure;
    count++;
}

void FigureArray::removeFigure(size_t index) {
    if (index >= count) return;
    
    delete figures[index];  
    
    for (size_t i = index; i < count - 1; ++i) {
        figures[i] = figures[i + 1];
    }
    figures[count - 1] = nullptr;  
    count--;
}

void FigureArray::printAllFigures(std::ostream& os) const {
    for (size_t i = 0; i < count; ++i) {
        Figure* fig = figures[i];
        os << "Figure " << i << ": " << *fig << std::endl;  // Используем os вместо cout
        Point center = fig->geometricCenter();
        double area = fig->area();
        os << "Geometric center: (" << center.x << ", " << center.y << ")" << std::endl;
        os << "Area: " << area << std::endl;
        os << "---" << std::endl;
    }
}

double FigureArray::totalArea() const {
    double total = 0;
    for (size_t i = 0; i < count; ++i) {
        total += figures[i]->area();
    }
    return total;
}

Figure* FigureArray::operator[](size_t index) {
    return figures[index];
}

const Figure* FigureArray::operator[](size_t index) const {
    return figures[index];
}

std::ostream& operator<<(std::ostream& os, const FigureArray& array) {
    array.printAllFigures(os);
    return os;
}

}