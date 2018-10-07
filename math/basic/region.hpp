#pragma once

#include "basic/point.hpp"
#include <limits>
#include <algorithm>
#include <array>
#include <utility>
#include <initializer_list>

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
};

using Interval = std::pair<double, double>;

class AABoxRegion : public Region {
public:
    using Bounds = std::vector<Interval>;

    AABoxRegion(std::initializer_list<Interval> bounds)
        : Region(bounds.size()), bounds_(bounds) {
        assert(N_ != 0);
    }

    inline double lower(size_t i) const {
        return bounds_[i].first;
    }

    inline double upper(size_t i) const {
        return bounds_[i].second;
    }

    bool lies_within(const Point& p) const {
        assert(p.dim() == N_);

        for (size_t i = 0; i < N_; ++i) {
            if (!(lower(i) < p[i] && p[i] < upper(i)))
                return false;
        }

        return true;
    }

    Point fit_to_bound(const Point& p, const Point& dir) const {
        assert(p.dim() == dir.dim() && p.dim() == N_);

        double t_star = std::numeric_limits<double>::infinity();

        for (size_t i = 0; i < N_; ++i) {
            double t_1 = (lower(i) - p[i])/dir[i];
            double t_2 = (upper(i) - p[i])/dir[i];

            if (t_1 > 0)
                t_star = std::min(t_star, t_1);

            if (t_2 > 0)
                t_star = std::min(t_star, t_2);
        }

        return p + 0.5 * t_star * dir; // this way we will stay inside
    }

private:
    Bounds bounds_;
};