#include <algorithm>

#include "array.h"

namespace figures {

Array::Array() : capacity_(0), data_(nullptr) {}

Array::Array(const size_t& n, Figure* value) : capacity_(n), data_(new Figure*[n]) {
    for (size_t i = 0; i < capacity_; ++i) {
        data_[i] = value; 
    }
}

Array::Array(const std::initializer_list<Figure*>& list) 
    : capacity_(list.size()), data_(new Figure*[list.size()]) {
    std::copy(list.begin(), list.end(), data_);
}

Array::Array(const Array& other) 
    : capacity_(other.capacity_), data_(new Figure*[other.capacity_]) {
    std::copy(other.data_, other.data_ + capacity_, data_);
}

Array::Array(Array&& other) noexcept 
    : capacity_(other.capacity_), data_(other.data_) {
    other.capacity_ = 0;
    other.data_ = nullptr;
}

Array::~Array() noexcept {
    delete[] data_;  
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        delete[] data_;
        capacity_ = other.capacity_;
        data_ = new Figure*[capacity_];
        std::copy(other.data_, other.data_ + capacity_, data_);
    }
    return *this;
}

Array& Array::operator=(Array&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        capacity_ = other.capacity_;
        data_ = other.data_;
        other.capacity_ = 0;
        other.data_ = nullptr;
    }
    return *this;
}

Figure*& Array::operator[](size_t index) {
    if (index >= capacity_) {
        throw std::out_of_range("out of range");
    }
    return data_[index];
}

Figure* Array::operator[](size_t index) const {
    if (index >= capacity_) {
        throw std::out_of_range("out of range");
    }
    return data_[index];
}

void Array::resize(size_t new_size) {
    if (new_size == capacity_) return;
    
    Figure** new_data = new Figure*[new_size];
    
    size_t copy_size = std::min(capacity_, new_size);
    for (size_t i = 0; i < copy_size; ++i) {
        new_data[i] = data_[i];
    }
    
    for (size_t i = copy_size; i < new_size; ++i) {
        new_data[i] = nullptr;
    }
    
    delete[] data_;
    data_ = new_data;
    capacity_ = new_size;
}

void Array::clear() {
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
}

}