#pragma once

#include "constraints.hpp"
#include "point.hpp"
#include "diff.hpp"
#include "stopping_criteria.hpp"
#include "ext/brent.hpp"

#include <utility>
#include <vector>

class GradientDescent {
public:
    using OptimizationPath = std::vector<std::pair<Point, double>>;

    template <typename T>
    OptimizationPath minimize(T&& f,
                              const OptimizationConstraint& D,
                              const Point& x_0,
                              const StoppingCriteria& stopping_criteria) {
        assert(D.dim() == x_0.dim());

        OptimizationPath path;

        Point x = x_0;
        double value = f(x_0);
        path.push_back({x, value});

        size_t iter = 0; 
        Point x_prev = x_0;
        do {
            x_prev = x;
            x = make_step(f, D, x, gradient(f, x));
            value = f(x);
            path.push_back({x, value});
            ++iter;
        } while (!stopping_criteria.stop(x, value, iter, path));

        return path;
    }

private:
    template <typename T>
    Point make_step(T&& f,
                    const OptimizationConstraint& D,
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
};