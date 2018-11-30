#pragma once

#include "basic/point.hpp"
#include "basic/region.hpp"

#include <random>

class AABoxRegion;

/**
 * @brief Bernoulli distribution wrapper
 * 
 */
class RandomDecision {
    std::bernoulli_distribution dist_;

public:
    /**
     * @brief Construct a new Random Decision object
     * 
     * @param p Probability of success
     */
    RandomDecision(double p) : dist_(p) {}

    /**
     * @brief Generate random variable
     * 
     * @return true if success was generated
     * @return false otherwise
     */
    bool get();
};

/**
 * @brief Uniform distribution in multidimensional ball with given center and radius
 * 
 */
class BallUniformDistribution {
public:
    /**
     * @brief Generate uniformly distributed in unit ball r.v.
     * 
     * @param dim Dimensionality
     * @return Point r.v.
     */
    static Point get(size_t dim);

    /**
     * @brief Generate uniformly distributed in ball with center c and radius r r.v.
     * 
     * @param c Center
     * @param r Radius
     * @return Point r.v.
     */
    static Point get(const Point& c, double r);
};

/**
 * @brief Uniform distribution in axis aligned box
 * 
 */
class BoxUniformDistribution {
public:
    /**
     * @brief Generates random point of a box
     * 
     * @param box Box to sample from
     * @return Point r.v.
     */
    static Point get(const AABoxRegion& box);
};