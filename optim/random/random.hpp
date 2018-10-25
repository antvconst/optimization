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

class BallUniformDistribution {
public:
    static Point get(size_t);
    static Point get(const Point& c, double r);
};

class BoxUniformDistribution {
public:
    static Point get(const AABoxRegion& box);
};