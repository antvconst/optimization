#pragma once

#include "basic/point.hpp"
#include <cassert>

class Region {
protected:
    size_t N_;

public:
    Region() = delete;
    Region(size_t N) : N_(N) {}

    size_t dim() const {
        return N_;
    }

    virtual bool lies_within(const Point& p) const = 0;
    virtual Point fit_to_bound(const Point& p, const Point& dir) const = 0;
    virtual Point random_point() const = 0;
};
