QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OptimizationGUI
TEMPLATE = app

CONFIG += c++14

SOURCES += \
    main.cpp \
    optimizationmain.cpp \
    exprtk/exprtk_wrapper.cpp \
    optimizationvizwidget.cpp \
    global.cpp

HEADERS += \
    optimizationmain.hpp \
    exprtk/exprtk_wrapper.hpp \
    optimizationvizwidget.h \
    global.hpp

FORMS += \
    optimizationmain.ui

LIBS += -L$$PWD/../optim-build -loptim
INCLUDEPATH += $$PWD/../optim/
DEPENDPATH += $$PWD/../optim/
