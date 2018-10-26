#ifndef HEATMAP_H
#define HEATMAP_H

#include <QImage>
#include <QColor>
#include <optimization/optimizer.hpp>

class Heatmap
{
public:
    struct Settings {
        int w;
        int h;
        int x_min;
        int x_max;
        int y_min;
        int y_max;
        double discretization_coeff;
        double scale_coeff;
        QColor color_low;
        QColor color_high;
    };

    Heatmap(const MultivariateFunction& f);
    QImage render(Settings settings);

private:
    MultivariateFunction f_;
};

#endif // HEATMAP_H
