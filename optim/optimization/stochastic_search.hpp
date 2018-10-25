#pragma once

#include "optimizer.hpp"
#include "random/random.hpp"

class StochasticSearch : public Optimizer {
public:
    StochasticSearch(double p)
        : random_decision_(p)
    {}

protected:
    virtual OptimizationPath minimize_impl(const MultivariateFunction& f,
                                           const Region& D,
                                           const Point& x_0,
                                           const StoppingCriteria& stopping_criteria);

private:
    RandomDecision random_decision_;

    Point random_step(const Region& D, const Point& x, size_t iter);
};