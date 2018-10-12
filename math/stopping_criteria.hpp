#pragma once

#include "basic/point.hpp"
#include <vector>
#include <initializer_list>
#include <memory>
#include <cmath>

class StoppingCriterion {
public:
    virtual bool stop(const Point&, double, 
                      const Point&, double,
                      size_t, size_t) const {
        assert(false);
        return true;
    }
};

class StoppingCriteria {
    std::vector<std::unique_ptr<StoppingCriterion>> criteria_;

public:
    StoppingCriteria() {};

    template <typename T, typename... Args>
    void add(Args&&... args) {
        criteria_.emplace_back(new T(std::forward<Args>(args)...));
    }

    bool stop(const Point& x, double val,
              const Point& x_prev, double val_prev,
              size_t iter, size_t fails) const {
        for (auto& criterion : criteria_) {
            if (criterion->stop(x, val, x_prev, val_prev, iter, fails)) {
                return true;
            }
        }
        return false;
    }
};

class MaxIterations : public StoppingCriterion {
    size_t max_iterations_;

public:
    MaxIterations(size_t n) : max_iterations_(n) {}

    bool stop(const Point&, double,
              const Point&, double,
              size_t iter, size_t) const override {
        return iter >= max_iterations_;
    }
};

class MaxFailedIterations : public StoppingCriterion {
    size_t max_fails_;

public:
    MaxFailedIterations(size_t n) : max_fails_(n) {}

    bool stop(const Point&, double,
              const Point&, double,
              size_t, size_t fails) const override {
        return fails >= max_fails_;
    }
};

class PointProximity : public StoppingCriterion {
    double eps_;

public:
    PointProximity(double eps) : eps_(eps) {}

    bool stop(const Point& x, double,
              const Point& x_prev, double,
              size_t, size_t) const override {
        return (x - x_prev).len() < eps_;
    }
};

class ValueProximity : public StoppingCriterion {
    double eps_;

public:
    ValueProximity(double eps) : eps_(eps) {}

    bool stop(const Point&, double val,
              const Point&, double val_prev,
              size_t, size_t) const override {
        return fabs((val - val_prev)/val) < eps_;
    } 
};