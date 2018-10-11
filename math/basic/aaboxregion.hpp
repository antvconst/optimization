#pragma once

#include "point.hpp"
#include "region.hpp"
#include "random/random.hpp"

#include <vector>
#include <utility>
#include <initializer_list>

using Interval = std::pair<double, double>;

class AABoxRegion : public Region {
public:
    using Bounds = std::vector<Interval>;

    AABoxRegion(std::initializer_list<Interval> bounds);

    inline double lower(size_t i) const {
        return bounds_[i].first;
    }

    inline double upper(size_t i) const {
        return bounds_[i].second;
    }

    inline const std::vector<Interval>& bounds() const {
        return bounds_;
    }

    bool lies_within(const Point& p) const override;
    Point fit_to_bound(const Point& p, const Point& dir) const override;
    Point random_point() const override;

private:
    Bounds bounds_;
    BoxUniformDistribution dist_;
};