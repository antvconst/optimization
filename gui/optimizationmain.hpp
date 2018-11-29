#ifndef OPTIMIZATIONMAIN_H
#define OPTIMIZATIONMAIN_H

#include <QMainWindow>

namespace Ui {
class OptimizationMain;
}

class OptimizationMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit OptimizationMain(QWidget *parent = nullptr);
    void setup();
    ~OptimizationMain();

private:
    Ui::OptimizationMain *ui;
};

#endif // OPTIMIZATIONMAIN_H
