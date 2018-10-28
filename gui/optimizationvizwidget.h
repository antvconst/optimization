#pragma once

#include <QLabel>

#include "heatmap.hpp"

class OptimizationVizWidget : public QLabel
{
public:
    OptimizationVizWidget(QWidget*);

    void paintEvent(QPaintEvent*);
};
