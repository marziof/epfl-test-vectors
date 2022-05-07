QT -= core gui
TEMPLATE = app
CONFIG += consoleQMAKE_CXXFLAGS += -std=c++11

TARGET = P10_Gnu

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
		main_gnu.cc \
		GNU_Graphe.cc

HEADERS += \
		GNU_Graphe.h\
