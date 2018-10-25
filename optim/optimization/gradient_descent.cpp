#include "gradient_descent.hpp"
#include "basic/diff.hpp"
#include "ext/brent.hpp"

OptimizationPath GradientDescent::minimize_impl(const MultivariateFunction& f,
                                                const Region& D,
                                                const Point& x_0,
                                                const StoppingCriteria& stopping_criteria) {
    OptimizationPath path;

    Point x = x_0;
    double value = f(x_0);
    path.push_back({x, value});

    size_t iter = 0; 
    Point x_prev = x_0;
    double val_prev = value;
    do {
        x_prev = x;
        val_prev = value;
        x = make_step(f, D, x, gradient(f, x));
        value = f(x);
        path.push_back({x, value});
        ++iter;
    } while (!stopping_criteria.stop(x, value, x_prev, val_prev, iter, 0));

    return path;
}

Point GradientDescent::make_step(const MultivariateFunction& f,
                                 const Region& D,
                                 const Point& x,
                                 const Point& grad) {
    auto f_dir = [&](double t) -> double {
        return f(x + t*grad);
    };

    double coef = brent::local_min(f_dir, 0.0, 1.0, 10e-6);

    auto p = x - coef * grad;

    if (!D.lies_within(p)) {
        p = D.fit_to_bound(x, -coef*grad);
    }

    return p;
}