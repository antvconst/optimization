#include "random.hpp"

#include <random>
#include "prng.hpp"
#include "basic/aaboxregion.hpp"

bool RandomDecision::get() {
    return dist_(SingletonGenerator::get_mt());
}

Point UnitBallUniformDistribution::get() {
    Point p(dim_);

    // Get a normal vector
    for (size_t i = 0; i < dim_; ++i) {
        p[i] = normal_dist_(SingletonGenerator::get_mt());
    }

    // Simulate polar radius
    double alpha = uniform_dist_(SingletonGenerator::get_mt());
    double r = pow(alpha, 1./dim_);

    return r * (p / p.len());
}

BoxUniformDistribution::BoxUniformDistribution(const AABoxRegion* box)
    : dim_(box->dim()), bounds_(box->bounds()) {
    assert(dim_ != 0);
}

Point BoxUniformDistribution::get() {
    Point p(dim_);
    for (size_t i = 0; i < dim_; ++i) {
        double a = bounds_[i].first;
        double b = bounds_[i].second;
        
        p[i] = std::uniform_real_distribution<double>(a, b)(SingletonGenerator::get_mt());
    }

    return p;
}    