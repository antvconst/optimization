#pragma once

#include "optimizer.hpp"

class GradientDescent : public Optimizer {
protected:
    OptimizationPath minimize_impl(const MultivariateFunction& f,
                                   const Region& D,
                                   const Point& x_0,
                                   const StoppingCriteria& stopping_criteria) override;

private:
    Point make_step(const MultivariateFunction& f,
                    const Region& D,
                    const Point& x,
                    const Point& grad);
};