TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    ShannonGraph.cpp \
    ShannonGraphBuilder.cpp

HEADERS += \
    ShannonGraph.h \
    GraphNode.h \
    QuantifiedNode.h \
    ShannonGraphBuilder.h \
    LiteralNode.h \
    TerminalNode.h

LIBS += -L/usr/local/LIBS -lz3
