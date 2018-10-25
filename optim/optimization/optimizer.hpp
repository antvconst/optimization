#pragma once

#include "basic/point.hpp"
#include "basic/region.hpp"
#include "stopping_criteria.hpp"

#include <utility>
#include <vector>
#include <functional>

using MultivariateFunction = std::function<double(const Point&)>;
using OptimizationPath = std::vector<std::pair<Point, double>>;

class Optimizer {
public:
    OptimizationPath minimize(const MultivariateFunction& f, const Region& D,
                              const Point& x_0,
                              const StoppingCriteria& stopping_criteria);

    OptimizationPath maximize(const MultivariateFunction& f, const Region& D,
                              const Point& x_0,
                              const StoppingCriteria& stopping_criteria);

protected:
    virtual OptimizationPath minimize_impl(const MultivariateFunction&,
                                           const Region&,
                                           const Point&,
                                           const StoppingCriteria&);
};