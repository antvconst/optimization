#ifndef SETTINGS_H
#define SETTINGS_H

#include <QColor>
#include "optimization/optimizer.hpp"
#include "basic/aaboxregion.hpp"

class Global
{
public:
    struct Heatmap {
        double discretization_coeff;
        double scale_coeff;
        QColor color_low;
        QColor color_high;
    };

    struct OptimizationTarget {
        MultivariateFunction func;

        double x_min;
        double x_max;
        double y_min;
        double y_max;
    };

    struct OptimizationMethod {
        std::unique_ptr<Optimizer> optimizer;

        double local_search_prob;
    };

    Heatmap hm;
    OptimizationMethod om;
    OptimizationTarget ot;

    static const Global& get();
    static Global& get_mutable();

private:
    static Global* instance;
    Global();
};

#endif // SETTINGS_H
