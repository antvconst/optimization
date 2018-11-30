#pragma once

#include "basic/point.hpp"
#include <cassert>

/**
 * @brief Abstact class for optimization region
 * 
 */
class Region {
protected:
    size_t N_;

public:
    Region() = delete;
    /**
     * @brief Construct a new Region object
     * 
     * @param N Dimensionality of region
     */
    Region(size_t N) : N_(N) {}

    /**
     * @brief Returns dimensionality
     * 
     * @return size_t Dimensionality
     */
    size_t dim() const {
        return N_;
    }

    /**
     * @brief Check if point lies within region
     * 
     * @param p Point
     * @return true p lies in region
     * @return false otherwise
     */
    virtual bool lies_within(const Point& p) const = 0;

    /**
     * @brief Projects p into region along direction dir
     * 
     * @param p Point
     * @param dir Direction
     * @return Point Projection
     */
    virtual Point fit_to_bound(const Point& p, const Point& dir) const = 0;

    /**
     * @brief Returns a uniformely distributed independent random points inside region
     * 
     * @return Point Random point
     */
    virtual Point random_point() const = 0;
};
