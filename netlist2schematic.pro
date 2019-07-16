#-------------------------------------------------
#
# Project created by QtCreator 2019-05-28T11:46:21
#
#-------------------------------------------------

QT       += core gui svg opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = netlist2schematic
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        netlist2schematic.cpp \
        src/error/parse_error.cpp \
        src/graph/edge.cpp \
        src/graph/graph.cpp \
        src/graph/layer.cpp \
        src/graph/node.cpp \
        src/graph/nvector.cpp \
        src/graph/port.cpp \
        src/graph/shape.cpp \
        src/graph/space.cpp \
        src/mainwindow.cpp \
        src/util/util_direction.cpp \
        src/util/util_porttype.cpp \
        src/util/util_side.cpp \
        src/util/util_string.cpp \
        src/xml/tinyxml2.cpp

HEADERS += \
        include/error/parse_error.h \
        include/graph/nvector.h \
        include/graph/direction.h \
        include/graph/port_type.h \
        include/graph/space.h \
        include/graph/side.h \
        include/graph/shape.h \
        include/graph/port.h \
        include/graph/edge.h \
        include/graph/node.h \
        include/graph/layer.h \
        include/graph/graph.h \
        include/mainwindow.h \
        include/xml/tinyxml2.h

FORMS += \
        ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    CMakeLists.txt \
    conf/default.svg \
    conf/gateDelays.delay \
    conf/rsfq.svg \
    input/FullAdder.v \
    input/FullAdder2.v \
    input/jand.v \
    input/jcb.v \
    input/jdff.v \
    input/jdrvPTL.v \
    input/jjtl.v \
    input/jndro.v \
    input/jnot.v \
    input/jptl.v \
    input/jrecPTL.v \
    input/jspl.v \
    input/jspl3.v \
    input/jxor.v \
    input/one_full_adder.v \
    output/elk_input.json \
    output/elk_output.json
