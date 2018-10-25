#include "stochastic_search.hpp"

OptimizationPath StochasticSearch::minimize_impl(const MultivariateFunction& f,
                                                 const Region& D,
                                                 const Point& x_0,
                                                 const StoppingCriteria& stopping_criteria) {
    OptimizationPath path;

    Point x = x_0;
    double value = f(x_0);
    path.push_back({x, value});

    Point x_prev = x_0;
    double val_prev = value;

    size_t iter = 0; 
    size_t fails = 0;
    do {
        Point x_n = random_step(D, x, iter);
        double value_n = f(x_n);

        if (value_n < value) {
            x_prev = x;
            val_prev = value;
            x = x_n;
            value = value_n;
            path.push_back({x, value});
            fails = 0;
        } else {    
            ++fails;
        }
        ++iter;
    } while (!stopping_criteria.stop(x, value, x_prev, val_prev, iter, fails));

    return path;
}

Point StochasticSearch::random_step(const Region& D, const Point& x, size_t iter) {
    Point p(D.dim());

    if (random_decision_.get()) {
        p = D.random_point();
    } else {
        p = BallUniformDistribution::get(x, 1./sqrt(iter));
    }
    
    if (!D.lies_within(p)) {
        p = D.fit_to_bound(x, p-x);
    }

    return p;
}