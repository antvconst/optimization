#pragma once

#include "point.hpp"
#include "region.hpp"
#include "random/random.hpp"

#include <vector>
#include <utility>
#include <initializer_list>

using Interval = std::pair<double, double>;

/**
 * @brief Axis Aligned Box optimization region
 * 
 */
class AABoxRegion : public Region {
public:
    using Bounds = std::vector<Interval>;

    AABoxRegion(const Bounds& bounds);
    AABoxRegion(std::initializer_list<Interval> bounds);

    /**
     * @brief Lower bound for specified coordinate
     * 
     * @param i Coordinate
     * @return double Lower bound on i-th coordinate
     */
    inline double lower(size_t i) const {
        return bounds_[i].first;
    }

    /**
     * @brief Upper bound for specified coordinate
     * 
     * @param i Coordinate
     * @return double Upper bound on i-th coordinate
     */
    inline double upper(size_t i) const {
        return bounds_[i].second;
    }

    /**
     * @brief Return bounds for all coordinates
     * 
     * @return const std::vector<Interval>& bounds
     */
    inline const std::vector<Interval>& bounds() const {
        return bounds_;
    }

    bool lies_within(const Point& p) const override;
    Point fit_to_bound(const Point& p, const Point& dir) const override;
    Point random_point() const override;

private:
    Bounds bounds_;
};