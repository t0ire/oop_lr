#pragma once

#include "array.h"    
#include "figure.h"

namespace figures {

class FigureArray {
private:
    Array figures;    
    size_t count;     

public:
    FigureArray();
    FigureArray(const FigureArray& other);
    FigureArray(FigureArray&& other) noexcept;
    ~FigureArray();

    FigureArray& operator=(const FigureArray& other);
    FigureArray& operator=(FigureArray&& other) noexcept;

    void addFigure(Figure* figure);
    void removeFigure(size_t index);
    void printAllFigures(std::ostream& os) const;
    double totalArea() const;
    
    size_t size() const { return count; }
    
    Figure* operator[](size_t index);
    const Figure* operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const FigureArray& array);
};

}