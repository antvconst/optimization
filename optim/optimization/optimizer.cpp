#include "optimizer.hpp"

OptimizationPath Optimizer::minimize(const MultivariateFunction& f, const Region& D,
                                     const Point& x_0,
                                     const StoppingCriteria& stopping_criteria) {
    assert(D.dim() == x_0.dim());
    return minimize_impl(f, D, x_0, stopping_criteria);
}

OptimizationPath Optimizer::maximize(const MultivariateFunction& f, const Region& D,
                                     const Point& x_0,
                                     const StoppingCriteria& stopping_criteria) {
    assert(D.dim() == x_0.dim());
    auto path = minimize_impl(
        [&](const Point& x) {
            return -f(x);
        }, D, x_0, stopping_criteria);

    for (auto& p : path) {
        p.second = -p.second;
    }

    return path;
}

OptimizationPath Optimizer::minimize_impl(const MultivariateFunction&,
                                          const Region&,
                                          const Point&,
                                          const StoppingCriteria&) {
    assert(false);
    return {};
}

Optimizer::~Optimizer() {}