#pragma once

#include <cmath>
#include <cstdarg>
#include <iostream>
#include <vector>
#include <initializer_list>
#include <assert.h>

const double EPS = 10e-9;

class Point
{
    const size_t N_;
    std::vector<double> data_;

public:
    Point() = delete;

    Point(size_t N) : N_(N), data_(N_) {}

    Point(const std::vector<double>& data) 
        : N_(data.size()), data_(data) {}

    Point(std::initializer_list<double> values)
        : N_(values.size()), data_(values) {}

    Point(const Point& other) = default;
    Point(Point&& other) = default;
    ~Point() = default;

    size_t dim() const {
        return N_;
    }

    double operator[](size_t i) const {
        return data_[i];
    }

    double& operator[](size_t i) {
        return data_[i];
    }

    double len() const {
        double s = 0;
        for (size_t i = 0; i < N_; ++i) {
            s += data_[i]*data_[i];
        }

        return sqrt(s);
    }

    Point& operator= (const Point& other) {
        data_ = other.data_;
        
        return *this;
    }

    friend bool operator== (const Point& lhs, const Point& rhs);
    friend bool operator!= (const Point& lhs, const Point& rhs);
    friend Point operator- (const Point& vec);
    friend Point operator+ (const Point& lhs, const Point& rhs);
    friend Point operator- (const Point& lhs, const Point& rhs);
    friend Point operator* (const Point& lhs, const Point& rhs);
    friend Point operator* (const Point& vec, double alpha);
    friend Point operator* (double alpha, const Point& vec);
    friend Point operator/ (const Point& vec, double alpha);

    static Point unit(size_t N, size_t i) {
        Point u(N);
        u[i] = 1.0;

        return u;
    }

    void print() const {
        for (size_t i = 0; i < N_; ++i)
            std::cout << data_[i] << " ";
        std::cout << std::endl;
    }
};

// EQUALITY
bool operator==(const Point& lhs, const Point& rhs) {
    return (lhs - rhs).len() < EPS;
}

bool operator!= (const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

// UNARY MINUS
Point operator-(const Point& vec) {
    Point r(vec.N_);
    for (size_t i = 0; i < vec.N_; ++i)
        r.data_[i] = -vec.data_[i];
    
    return r;
}

// ADDITION_
Point operator+(const Point& lhs, const Point& rhs) {
    assert(lhs.N_ == rhs.N_);

    Point r(lhs.N_);
    for (size_t i = 0; i < lhs.N_; ++i)
        r.data_[i] = lhs.data_[i] + rhs.data_[i];

    return r;
}

// SUBTRACTION
Point operator-(const Point& lhs, const Point& rhs) {
    assert(lhs.N_ == rhs.N_);

    Point r(lhs.N_);
    for (size_t i = 0; i < lhs.N_; ++i)
        r.data_[i] = lhs.data_[i] - rhs.data_[i];

    return r;
}

// COMPONENT-WISE MULTIPLICATION
Point operator*(const Point& lhs, const Point& rhs) {
    assert(lhs.N_ == rhs.N_);

    Point r(lhs.N_);
    for (size_t i = 0; i < lhs.N_; ++i)
        r.data_[i] = lhs.data_[i] * rhs.data_[i];

    return r;
}

// SCALAR MULTIPLICATION
Point operator*(const Point& vec, double alpha) {
    Point r(vec.N_);
    for (size_t i = 0; i < vec.N_; ++i)
        r.data_[i] = alpha * vec.data_[i];

    return r;
}

// SCALAR MULTIPLICATION
Point operator*(double alpha, const Point& vec) {
    return vec * alpha;
}

// SCALAR DIVISION
Point operator/(const Point& vec, double alpha) {
    Point r(vec.N_);
    for (size_t i = 0; i < vec.N_; ++i)
        r.data_[i] = vec.data_[i] / alpha;

    return r;
}
