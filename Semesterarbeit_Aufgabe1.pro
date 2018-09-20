TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    parsercsv.cpp \
    parserxml.cpp

HEADERS += \
    main.h \
    parsercsv.h \
    parserxml.h
