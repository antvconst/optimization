#pragma once

#include "basic/point.hpp"
#include "basic/region.hpp"

#include <random>

class AABoxRegion;

class RandomDecision {
    std::bernoulli_distribution dist_;

public:
    RandomDecision(double p) : dist_(p) {}
    bool get();
};

class UnitBallUniformDistribution {
    size_t dim_;
    std::normal_distribution<double> normal_dist_;
    std::uniform_real_distribution<double> uniform_dist_;

public:
    UnitBallUniformDistribution(size_t dim) : dim_(dim) {}
    Point get();  
};

class BoxUniformDistribution {
    using Interval = std::pair<double, double>;

    size_t dim_;
    const std::vector<Interval>& bounds_;

public:
    BoxUniformDistribution(const AABoxRegion* box);
    Point get();
};