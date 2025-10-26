#include <sstream>
#include <cmath>

#include <gtest/gtest.h>

#include "figure.h"
#include "rectangle.h"
#include "rhombus.h"
#include "trapezoid.h"
#include "array.h"
#include "figure_array.h"

using namespace figures;

// Тесты для Point
TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point p(3.5, -2.1);
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, -2.1);
}

// Тесты для Rectangle
TEST(RectangleTest, DefaultConstructor) {
    Rectangle rect;
    
    Point center = rect.geometricCenter();
    EXPECT_NEAR(center.x, 0.0, 1e-9);
    EXPECT_NEAR(center.y, 0.0, 1e-9);
    
    EXPECT_NEAR(rect.area(), 4.0, 1e-9);
}

TEST(RectangleTest, ParameterizedConstructor) {
    Point p1(0, 0), p2(4, 0), p3(4, 3), p4(0, 3);
    Rectangle rect(p1, p2, p3, p4);
    
    Point center = rect.geometricCenter();
    EXPECT_NEAR(center.x, 2.0, 1e-9);
    EXPECT_NEAR(center.y, 1.5, 1e-9);
    
    EXPECT_NEAR(rect.area(), 12.0, 1e-9);
}

TEST(RectangleTest, CopyConstructor) {
    Rectangle rect1;
    Rectangle rect2(rect1);
    
    EXPECT_TRUE(rect1 == static_cast<const Figure&>(rect2));
    EXPECT_NEAR(rect1.area(), rect2.area(), 1e-9);
}

TEST(RectangleTest, MoveConstructor) {
    Rectangle rect1;
    double original_area = rect1.area();
    Rectangle rect2(std::move(rect1));
    
    EXPECT_NEAR(rect2.area(), original_area, 1e-9);
    EXPECT_NO_THROW(rect2.geometricCenter());
}

TEST(RectangleTest, AssignmentOperator) {
    Rectangle rect1;
    Point p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    Rectangle rect2(p1, p2, p3, p4);
    
    rect1 = rect2;

    EXPECT_TRUE(rect1 == static_cast<const Figure&>(rect2));
    EXPECT_NEAR(rect1.area(), rect2.area(), 1e-9);
}

TEST(RectangleTest, EqualityOperator) {
    Rectangle rect1;
    Rectangle rect2;
    
    EXPECT_TRUE(rect1 == static_cast<const Figure&>(rect2));
    
    Point p1(0, 0), p2(3, 0), p3(3, 2), p4(0, 2);
    Rectangle rect3(p1, p2, p3, p4);
    EXPECT_FALSE(rect1 == static_cast<const Figure&>(rect3));
}

TEST(RectangleTest, Clone) {
    Rectangle rect;
    Figure* clone = rect.clone();
    
    EXPECT_TRUE(rect == *clone);
    EXPECT_NE(&rect, clone);
    EXPECT_NEAR(rect.area(), clone->area(), 1e-9);
    
    delete clone;
}

TEST(RectangleTest, StreamOutput) {
    Rectangle rect;
    std::stringstream ss;
    rect.printVertices(ss);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("rectangle:") != std::string::npos);
}

TEST(RectangleTest, StreamInput) {
    Rectangle rect;
    std::stringstream ss("0 0 4 0 4 3 0 3");
    rect.readFromStream(ss);
    
    EXPECT_NEAR(rect.area(), 12.0, 1e-9);
    
    Point center = rect.geometricCenter();
    EXPECT_NEAR(center.x, 2.0, 1e-9);
    EXPECT_NEAR(center.y, 1.5, 1e-9);
}

TEST(RectangleTest, OperatorDouble) {
    Rectangle rect;
    double area = static_cast<double>(rect); 
    
    EXPECT_NEAR(area, 4.0, 1e-9);
}

// Тесты для Rhombus
TEST(RhombusTest, DefaultConstructor) {
    Rhombus rhomb;
    
    Point center = rhomb.geometricCenter();
    EXPECT_NEAR(center.x, 0.0, 1e-9);
    EXPECT_NEAR(center.y, 0.0, 1e-9);
    
    EXPECT_GT(rhomb.area(), 0.0);
}

TEST(RhombusTest, ParameterizedConstructor) {
    Point p1(0, -2), p2(2, 0), p3(0, 2), p4(-2, 0);
    Rhombus rhomb(p1, p2, p3, p4);
    
    Point center = rhomb.geometricCenter();
    EXPECT_NEAR(center.x, 0.0, 1e-9);
    EXPECT_NEAR(center.y, 0.0, 1e-9);
    
    EXPECT_NEAR(rhomb.area(), 8.0, 1e-9); 
}

TEST(RhombusTest, EqualityOperator) {
    Rhombus rhomb1;
    Rhombus rhomb2;
    
    EXPECT_TRUE(rhomb1 == static_cast<const Figure&>(rhomb2));
}

// Тесты для Trapezoid
TEST(TrapezoidTest, DefaultConstructor) {
    Trapezoid trap;
    
    Point center = trap.geometricCenter();
    EXPECT_NEAR(center.x, 0.0, 1e-9);
    EXPECT_NEAR(center.y, 0.0, 1e-9);
    
    EXPECT_GT(trap.area(), 0.0);
}

TEST(TrapezoidTest, ParameterizedConstructor) {
    Point p1(0, 0), p2(4, 0), p3(3, 2), p4(1, 2);
    Trapezoid trap(p1, p2, p3, p4);
    
    Point center = trap.geometricCenter();
    EXPECT_NEAR(center.x, 2.0, 1e-9);
    EXPECT_NEAR(center.y, 1.0, 1e-9);
    
    EXPECT_NEAR(trap.area(), 6.0, 1e-9);
}

// Тесты для Array
TEST(ArrayTest, DefaultConstructor) {
    Array arr;
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, ParameterizedConstructor) {
    Array arr(5, nullptr);
    EXPECT_EQ(arr.size(), 5);
    
    for (size_t i = 0; i < arr.size(); ++i) {
        EXPECT_EQ(arr[i], nullptr);
    }
}

TEST(ArrayTest, Resize) {
    Array arr(3, nullptr);
    
    arr.resize(5);
    EXPECT_EQ(arr.size(), 5);
    
    arr.resize(2);
    EXPECT_EQ(arr.size(), 2);
}

// Тесты для FigureArray
TEST(FigureArrayTest, DefaultConstructor) {
    FigureArray fa;
    EXPECT_EQ(fa.size(), 0);
}

TEST(FigureArrayTest, AddFigure) {
    FigureArray fa;
    Rectangle* rect = new Rectangle();
    
    fa.addFigure(rect);
    EXPECT_EQ(fa.size(), 1);
}

TEST(FigureArrayTest, RemoveFigure) {
    FigureArray fa;
    Rectangle* rect = new Rectangle();
    
    fa.addFigure(rect);
    EXPECT_EQ(fa.size(), 1);
    
    fa.removeFigure(0);
    EXPECT_EQ(fa.size(), 0);
}

TEST(FigureArrayTest, TotalArea) {
    FigureArray fa;
    fa.addFigure(new Rectangle());
    fa.addFigure(new Rhombus());
    
    double total = fa.totalArea();
    EXPECT_GT(total, 0.0);
}

// Тесты полиморфизма
TEST(PolymorphismTest, DifferentFiguresInArray) {
    FigureArray fa;
    
    fa.addFigure(new Rectangle());
    fa.addFigure(new Rhombus());
    fa.addFigure(new Trapezoid());
    
    EXPECT_EQ(fa.size(), 3);
    
    double total_area = fa.totalArea();
    EXPECT_GT(total_area, 0.0);
    
    for (size_t i = 0; i < fa.size(); ++i) {
        const Figure* fig = fa[i];
        EXPECT_NO_THROW(fig->area());
        EXPECT_NO_THROW(fig->geometricCenter());
        
        std::stringstream ss;
        EXPECT_NO_THROW(fig->printVertices(ss));
        EXPECT_FALSE(ss.str().empty());
    }
}

TEST(PolymorphismTest, FigureOutputOperator) {
    Rectangle rect;
    std::stringstream ss;
    
    ss << rect; 
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("rectangle:") != std::string::npos);
}
