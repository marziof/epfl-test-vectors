QT += core gui opengl widgets
QMAKE_CXXFLAGS += -std=c++11

win32:LIBS += -lopengl32


TARGET = P10_gl

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
		GlSphere.cc\
    main_qt_gl.cc \
		GlWidget.cc \
		Vue_OpenGl.cc

HEADERS += \
		GlSphere.h \
		GlWidget.h \
    vertex_shader.h \
		Vue_OpenGl.h \
		../general/Dessinable.h \
		../general/SupportADessin.h \

RESOURCES += \
    resource.qrc
