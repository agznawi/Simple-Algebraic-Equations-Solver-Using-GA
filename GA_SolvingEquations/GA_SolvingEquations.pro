TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    evolution.cpp \
    population.cpp \
    individual.cpp

HEADERS += \
    evolution.h \
    population.h \
    individual.h \
    randengine.h

