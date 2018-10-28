#ifndef HEATMAP_H
#define HEATMAP_H

#include <QImage>
#include <QColor>
#include <optimization/optimizer.hpp>

class Heatmap
{
public:
    static QImage render(int w, int h);
};

#endif // HEATMAP_H
