#include "aaboxregion.hpp"

#include <algorithm>

AABoxRegion::AABoxRegion(const Bounds& bounds)
    : Region(bounds.size()), bounds_(bounds) {
        assert(N_ != 0);
}

AABoxRegion::AABoxRegion(std::initializer_list<Interval> bounds)
    : Region(bounds.size()), bounds_(bounds) {
    assert(N_ != 0);
}

bool AABoxRegion::lies_within(const Point& p) const {
        assert(p.dim() == N_);

        for (size_t i = 0; i < N_; ++i) {
            if (!(lower(i) < p[i] && p[i] < upper(i)))
                return false;
        }

        return true;
}

Point AABoxRegion::fit_to_bound(const Point& p, const Point& dir) const {
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

Point AABoxRegion::random_point() const {
    return BoxUniformDistribution::get(*this);
}