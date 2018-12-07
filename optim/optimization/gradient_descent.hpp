#pragma once

#include "optimizer.hpp"

/**
 * @brief Gradient descent optimizer implementation
 * 
 */
class GradientDescent : public Optimizer {
public:
    GradientDescent(double rate)
        : rate_(rate) {}

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
    OptimizationPath minimize_impl(const MultivariateFunction& f,
                                   const Region& D,
                                   const Point& x_0,
                                   const StoppingCriteria& stopping_criteria) override;

private:
    double rate_;

    /**
     * @brief Single gradient descent step
     * 
     * @param f Target function
     * @param D Optimization region
     * @param x Current point
     * @param grad Target function's gradient at point x
     * @return Point New point
     */
    Point make_step(const MultivariateFunction& f,
                    const Region& D,
                    const Point& x,
                    const Point& grad);
};