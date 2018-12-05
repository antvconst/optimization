#pragma once

#include "optimizer.hpp"
#include "random/random.hpp"

/**
 * @brief Stochastic search optimizer implementation
 * 
 */
class StochasticSearch : public Optimizer {
public:
    StochasticSearch(double p)
        : random_decision_(p)
    {}

protected:
    /**
     * @brief Optimizer interface implementation
     * 
     * @param f Target function
     * @param D Optimization region
     * @param x_0 Initial approximation
     * @param stopping_criteria Stopping criteria
     * @return OptimizationPath Sequence of optimization steps along with function values,
     * the last point is detected optimum
     */
    virtual OptimizationPath minimize_impl(const MultivariateFunction& f,
                                           const Region& D,
                                           const Point& x_0,
                                           const StoppingCriteria& stopping_criteria) override;

private:
    RandomDecision random_decision_;

    Point random_step(const Region& D, const Point& x, size_t iter);
};