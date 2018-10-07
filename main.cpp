#include "math/basic/point.hpp"
#include "math/optim.hpp"
#include "stopping_criteria.hpp"
#include <cmath>

#include <iostream>

int main() {
    auto f = [](const Point& v) {
       return (1 - v[0])*(1 - v[0]) + 100*(v[1] - v[0]*v[0])*(v[1] - v[0]*v[0]);
    };

    auto box = AABBConstraint{{-0.1, 10.0}, {-0.1, 20.0}};

    GradientDescent gd;

    StoppingCriteria sc;
    sc.add<MaxIterations>(100000);
    sc.add<PointProximity>(1e-6);

    auto path = gd.minimize(f, box, {10, 20}, sc);

    std::cout << "Optimization finished:" << std::endl;
    std::cout << "Steps: " << path.size() - 1 << std::endl;
    std::cout << "Final point: " << path.back().first << std::endl;
    std::cout << "Value: " << path.back().second << std::endl;

    return 0;
}