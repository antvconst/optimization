#pragma once

#include "point.hpp"

template <typename T>
double derivative(T&& f, const Point& x, size_t i, double h = 10e-4) {
    assert(i < x.dim());

    auto unit = Point::unit(x.dim(), i);

    return 0.5 * (f(x + h*unit) - f(x - h*unit)) / h;
}

template <typename T>
Point gradient(T&& f, const Point& x, double h = 10e-5) {
    Point grad(x.dim());

    for (size_t i = 0; i < x.dim(); ++i) {
        grad[i] = derivative(f, x, i, h);
    }

    return grad;
}