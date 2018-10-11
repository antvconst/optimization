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
public:
    static Point get(size_t);  
};

class BoxUniformDistribution {
    using Interval = std::pair<double, double>;

public:
    static Point get(const AABoxRegion& box);
};