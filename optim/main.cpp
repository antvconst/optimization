#include "basic/point.hpp"
#include "basic/aaboxregion.hpp"
#include "optimization/stochastic_search.hpp"
#include "optimization/gradient_descent.hpp"
#include "optimization/stopping_criteria.hpp"
#include <cmath>
#include <iostream>
#include <functional>
using namespace std;

enum Method {
    GD = 0,
    SS
};

int main(int, char**) {
    cout << "************** Optimization **************\n" << endl;

    auto f_2 = [](const Point& v) {
        return (1 - v[0])*(1 - v[0]) + 100 * (v[1] - v[0]*v[0])*(v[1] - v[0]*v[0]);
    };

    auto f_3 = [](const Point& v) {
        return v[0]*v[0] + v[1]*v[1] + (1-v[2])*(1-v[2]) + v[0]*v[1];
    };

    auto f_4 = [](const Point& v) {
        return v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3];
    };

    function<double(const Point& v)> f;
    size_t dim;
    Method method;
    vector<pair<double, double>> bounds;
    vector<double> point;

    cout << "Dimensionality (2, 3 or 4): ";
    
    while(true) {
        cin >> dim;
        if (dim == 2) {
            f = f_2;
            break;
        }
        else if (dim == 3) {
            f = f_3;
            break;
        }
        else if (dim == 4) {
            f = f_4;
            break;
        } else {
            cout << "Invalid dimensionality, try again";
        }
    }

    cout << "Method (0 = gradient descent, 1 = stochastic search): ";
    {
        bool b;
        cin >> b;
        method = b ? SS : GD;
    }

    cout << "Optimization box bounds:" << endl;
    for (size_t i = 0; i < dim; ++i) {
        cout << "(*)  ";
        pair<double, double> p;
        cin >> p.first;
        cin >> p.second;

        bounds.push_back(p);
    }

    cout << "Initial approximation: ";
    for (size_t i = 0; i < dim; ++i) {
        double x;
        cin >> x;

        point.push_back(x);
    }

    StoppingCriteria sc;
    cout << "\nHalting criteria\n" << endl;
    cout << "* Maximum iterations: ";
    {
        bool add;
        cin >> add;

        if (add) {
            size_t k;
            cin >> k;
            sc.add<MaxIterations>(k);
        }
    }
    cout << "* Maximum failed iterations: ";
    {
        bool add;
        cin >> add;

        if (add) {
            size_t k;
            cin >> k;
            sc.add<MaxFailedIterations>(k);
        }
    }
    cout << "* Point proximity threshold: ";
    {
        bool add;
        cin >> add;

        if (add) {
            double t;
            cin >> t;
            sc.add<PointProximity>(t);
        }
    }
    cout << "* Function value proximity threshold: ";
    {
        bool add;
        cin >> add;

        if (add) {
            double t;
            cin >> t;
            sc.add<ValueProximity>(t);
        }
    }

    unique_ptr<Optimizer> optimizer;
    if (method == GD) 
        optimizer.reset(new GradientDescent(1e-6));
    else
        optimizer.reset(new StochasticSearch(0.5));

    AABoxRegion region(bounds);
    Point x0(point);

    auto path = optimizer->minimize(f, region, x0, sc);

    cout << "Halted in " << path.size() << " iterations" << endl;
    cout << path.back().first << " -> " << path.back().second << endl;

    return 0;
}