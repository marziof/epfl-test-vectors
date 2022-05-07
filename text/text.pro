QT -= core gui
TEMPLATE = app
CONFIG += console
QMAKE_CXXFLAGS += -std=c++11

TARGET = P10_text

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_text.cc \
		TextViewer.cc

HEADERS += \
		TextViewer.h\
