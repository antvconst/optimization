#pragma once

#include "basic/point.hpp"
#include "basic/region.hpp"
#include "stopping_criteria.hpp"

#include <utility>
#include <vector>
#include <functional>

using MultivariateFunction = std::function<double(const Point&)>;
using OptimizationPath = std::vector<std::pair<Point, double>>;

/**
 * @brief Abstract class for any optimization method
 * 
 */
class Optimizer {
public:
    /**
     * @brief Minimize given function using current implementation
     * 
     * @param f Target function
     * @param D Optimization region
     * @param x_0 Initial approximation
     * @param stopping_criteria Stopping criteria
     * @return OptimizationPath Sequence of optimization steps along with function values,
     * the last point is detected optimum
     */
    OptimizationPath minimize(const MultivariateFunction& f, const Region& D,
                              const Point& x_0,
                              const StoppingCriteria& stopping_criteria);

    /**
     * @brief Minimize given function using current implementation
     * 
     * @param f Target function
     * @param D Optimization region
     * @param x_0 Initial approximation
     * @param stopping_criteria Stopping criteria
     * @return OptimizationPath Sequence of optimization step along with function values,
     * the last point is detected optimum
     */
    OptimizationPath maximize(const MultivariateFunction& f, const Region& D,
                              const Point& x_0,
                              const StoppingCriteria& stopping_criteria);

    virtual ~Optimizer();

protected:
    /**
     * @brief Intrinsic minimization implementation to overload in descendant classes
     * 
     * @return OptimizationPath 
     */
    virtual OptimizationPath minimize_impl(const MultivariateFunction&,
                                           const Region&,
                                           const Point&,
                                           const StoppingCriteria&);
};