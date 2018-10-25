#include "point.hpp"

#include <cmath>
#include <cstdarg>
#include <iostream>
#include <vector>
#include <initializer_list>
#include <assert.h>

Point::Point(size_t N) : N_(N), data_(N_) {}

Point::Point(const std::vector<double>& data) 
    : N_(data.size()), data_(data) {}

Point::Point(std::initializer_list<double> values)
    : N_(values.size()), data_(values) {}

size_t Point::dim() const {
    return N_;
}

double Point::len() const {
    double s = 0;
    for (size_t i = 0; i < N_; ++i) {
        s += data_[i]*data_[i];
    }

    return sqrt(s);
}

Point Point::unit(size_t N, size_t i) {
    Point u(N);
    u[i] = 1.0;

    return u;
}

double Point::operator[](size_t i) const {
    return data_[i];
}

double& Point::operator[](size_t i) {
    return data_[i];
}

Point& Point::operator= (const Point& other) {
    assert(N_ == other.N_);

    data_ = other.data_;        
    return *this;
}

bool operator==(const Point& lhs, const Point& rhs) {
    return (lhs - rhs).len() < EPS;
}

bool operator!= (const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

Point operator-(const Point& vec) {
    Point r(vec.N_);
    for (size_t i = 0; i < vec.N_; ++i)
        r.data_[i] = -vec.data_[i];

    return r;
}

Point operator+(const Point& lhs, const Point& rhs) {
    assert(lhs.N_ == rhs.N_);

    Point r(lhs.N_);
    for (size_t i = 0; i < lhs.N_; ++i)
        r.data_[i] = lhs.data_[i] + rhs.data_[i];

    return r;
}

Point operator-(const Point& lhs, const Point& rhs) {
    assert(lhs.N_ == rhs.N_);

    Point r(lhs.N_);
    for (size_t i = 0; i < lhs.N_; ++i)
        r.data_[i] = lhs.data_[i] - rhs.data_[i];

    return r;
}

Point operator*(const Point& lhs, const Point& rhs) {
    assert(lhs.N_ == rhs.N_);

    Point r(lhs.N_);
    for (size_t i = 0; i < lhs.N_; ++i)
        r.data_[i] = lhs.data_[i] * rhs.data_[i];

    return r;
}

Point operator*(const Point& vec, double alpha) {
    Point r(vec.N_);
    for (size_t i = 0; i < vec.N_; ++i)
        r.data_[i] = alpha * vec.data_[i];

    return r;
}

Point operator*(double alpha, const Point& vec) {
    return vec * alpha;
}

Point operator/(const Point& vec, double alpha) {
    Point r(vec.N_);
    for (size_t i = 0; i < vec.N_; ++i)
        r.data_[i] = vec.data_[i] / alpha;

    return r;
}

std::ostream& operator << (std::ostream& os, const Point& p) {
    os << "Point(";
    for (size_t i = 0; i < p.N_-1; ++i)
        os << p.data_[i] << ", ";
    os << p.data_[p.N_-1] << ")";

    return os;
}