#pragma once

#include "basic/point.hpp"
#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <cmath>

/**
 * @brief Single stopping criterion abstract class
 * 
 */
class StoppingCriterion {
public:
    /**
     * @brief Checks if the stopping condition is satisfied
     * 
     * @return true if condition is satisfied
     * @return false otherwise
     */
    virtual bool stop(const Point&, double, 
                      const Point&, double,
                      size_t, size_t) const {
        assert(false);
        return true;
    }

    /**
     * @brief Name of current criterion to use in stopping cause log line
     * 
     * @return const char* Criterion name
     */
    virtual const char* name() {
        return "";
    }
};

/**
 * @brief Convenient container for a set of stopping criteria
 * 
 */
class StoppingCriteria {
    /**
     * @brief Underlying criteria
     * 
     */
    std::vector<std::unique_ptr<StoppingCriterion>> criteria_;

public:
    StoppingCriteria() {};

    /**
     * @brief Add new criterion (created in-place)
     * 
     * @tparam T Criterion type
     * @tparam Args Argument types of criterion constructor
     * @param args Arguments to pass to criterion constructor
     */
    template <typename T, typename... Args>
    void add(Args&&... args) {
        criteria_.emplace_back(new T(std::forward<Args>(args)...));
    }

    /**
     * @brief Checks if any stopping criterion is satisfied
     * 
     * @param x Current point
     * @param val Current function value
     * @param x_prev Previous point
     * @param val_prev Previous value
     * @param iter Current iteration number
     * @param fails Current number of failed iterations in a row
     * @return true if at least one criterion is satisfied
     * @return false otherwise
     */
    bool stop(const Point& x, double val,
              const Point& x_prev, double val_prev,
              size_t iter, size_t fails) const {
        for (auto& criterion : criteria_) {
            if (criterion->stop(x, val, x_prev, val_prev, iter, fails)) {
                std::cout << "Stopping cause: " << criterion->name() << std::endl;
                return true;
            }
        }
        return false;
    }
};

/**
 * @brief Maximum iteration count stopping criterion
 * 
 */
class MaxIterations : public StoppingCriterion {
    size_t max_iterations_;

public:
    /**
     * @brief Construct a new Max Iterations object
     * 
     * @param n Maximum iteration count
     */
    MaxIterations(size_t n) : max_iterations_(n) {}

    bool stop(const Point&, double,
              const Point&, double,
              size_t iter, size_t) const override {
        return iter >= max_iterations_;
    }

    virtual const char* name() {
        return "MaxIterations";
    }
};

/**
 * @brief Maximum failed iterations if a row stopping criterion
 * 
 */
class MaxFailedIterations : public StoppingCriterion {
    size_t max_fails_;

public:
    /**
     * @brief Construct a new Max Failed Iterations object
     * 
     * @param n Maximum failed iteration count
     */
    MaxFailedIterations(size_t n) : max_fails_(n) {}

    bool stop(const Point&, double,
              const Point&, double,
              size_t, size_t fails) const override {
        return fails >= max_fails_;
    }
    
    virtual const char* name() {
        return "MaxFailedIterations";
    }
};

/**
 * @brief Point proximity stopping criterion. Stops if |x - x_prev| < eps_
 * 
 */
class PointProximity : public StoppingCriterion {
    double eps_;

public:
    /**
     * @brief Construct a new Point Proximity object
     * 
     * @param eps Threshold
     */
    PointProximity(double eps) : eps_(eps) {}

    bool stop(const Point& x, double,
              const Point& x_prev, double,
              size_t, size_t) const override {
        return (x - x_prev).len() < eps_;
    }

    virtual const char* name() {
        return "PointProximity";
    }
};

/**
 * @brief Function value proximity stopping criterion. Stops if |(val - val_prev)/val| < eps.
 * 
 */
class ValueProximity : public StoppingCriterion {
    double eps_;

public:
    /**
     * @brief Construct a new Value Proximity object
     * 
     * @param eps Threshold
     */
    ValueProximity(double eps) : eps_(eps) {}

    bool stop(const Point&, double val,
              const Point&, double val_prev,
              size_t, size_t) const override {
        return fabs((val - val_prev)/val) < eps_;
    } 

    virtual const char* name() {
        return "ValueProximity";
    }
};