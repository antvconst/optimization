#pragma once

#include "basic/point.hpp"
#include <vector>
#include <initializer_list>
#include <memory>
#include <cmath>

class StoppingCriterion {
public:
    virtual bool stop(const Point&, double, size_t, size_t,
                      const std::vector<std::pair<Point, double>>&) const {
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

    bool stop(const Point& x, double val, size_t iter, size_t fails,
              const std::vector<std::pair<Point, double>>& path) const {
        for (auto& criterion : criteria_) {
            if (criterion->stop(x, val, iter, fails, path)) {
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

    bool stop(const Point&, double, size_t iter, size_t,
              const std::vector<std::pair<Point, double>>&) const override {
        return iter >= max_iterations_;
    }
};

class MaxFailedIterations : public StoppingCriterion {
    size_t max_fails_;

public:
    MaxFailedIterations(size_t n) : max_fails_(n) {}

    bool stop(const Point&, double, size_t, size_t fails,
              const std::vector<std::pair<Point, double>>&) const override {
        return fails >= max_fails_;
    }
};

class PointProximity : public StoppingCriterion {
    double eps_;

public:
    PointProximity(double eps) : eps_(eps) {}

    bool stop(const Point& x, double, size_t iter, size_t,
              const std::vector<std::pair<Point, double>>& path) const override {
        return (x - path[iter-1].first).len() < eps_;
    }
};

class ValueProximity : public StoppingCriterion {
    double eps_;

public:
    ValueProximity(double eps) : eps_(eps) {}

    bool stop(const Point&, double val, size_t iter, size_t,
              const std::vector<std::pair<Point, double>>& path) const override {
        return fabs((val - path[iter-2].second)/val) < eps_;
    } 
};