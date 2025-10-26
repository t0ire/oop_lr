#pragma once

#include <iostream>
#include <string>
#include <initializer_list>

#include "figure.h"  

namespace figures {

class Array {
private:
    size_t capacity_;          
    Figure** data_;        

public:

    Array();  
    Array(const size_t& n, Figure* value = nullptr);  
    Array(const std::initializer_list<Figure*>& list);  
    Array(const Array& other);  
    Array(Array&& other) noexcept;  
    
    virtual ~Array() noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    
    size_t capacity() const { return capacity_; }
    size_t size() const { return capacity_; }
    Figure*& operator[](size_t index);  
    Figure* operator[](size_t index) const;  
    
    void resize(size_t new_size);  
    void clear();  
};

}
