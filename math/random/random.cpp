#include "random.hpp"

#include <random>
#include "prng.hpp"
#include "basic/aaboxregion.hpp"

bool RandomDecision::get() {
    return dist_(SingletonGenerator::get_mt());
}
 
static std::normal_distribution<double> normal_dist_;
static std::uniform_real_distribution<double> uniform_dist_;

Point BallUniformDistribution::get(size_t dim) {
    Point p(dim);

    // Get a normal vector
    for (size_t i = 0; i < dim; ++i) {
        p[i] = normal_dist_(SingletonGenerator::get_mt());
    }

    // Simulate polar radius
    double alpha = uniform_dist_(SingletonGenerator::get_mt());
    double r = pow(alpha, 1./dim);

    return r * (p / p.len());
}

Point BallUniformDistribution::get(const Point& c, double r) {
    return c + r * BallUniformDistribution::get(c.dim());
}

Point BoxUniformDistribution::get(const AABoxRegion& region) {
    assert(region.dim());

    size_t dim = region.dim();
    const auto& bounds = region.bounds();

    Point p(dim);
    for (size_t i = 0; i < dim; ++i) {
        double a = bounds[i].first;
        double b = bounds[i].second;
        
        p[i] = std::uniform_real_distribution<double>(a, b)(SingletonGenerator::get_mt());
    }

    return p;
}