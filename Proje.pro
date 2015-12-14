#-------------------------------------------------
#
# Project created by QtCreator 2014-11-26T13:23:47
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Proje
TEMPLATE = app


SOURCES += main.cpp\
        interface.cpp \
    about.cpp \
    sound_treads.cpp \
    software/track_baget.cpp

HEADERS  += interface.h \
    about.h \
    sound_treads.h

FORMS    += interface.ui

INCLUDEPATH += F:/opencv/build/include/

    #debug libs
LIBS +=-LF:/opencv/build/x86/vc11/staticlib\
    #+=-LF:/opencv249/build/x86/vc11/lib\
    -lopencv_core249d\
    -lopencv_highgui249d\
    -lIlmImfd\
    -llibpngd\
    -llibjpegd\
    -llibjasperd\
    -lIlmImfd\     #'opencv_core249d.lib'
    -lzlibd


#INCLUDEPATH += F:/opencv
#LIBS += `pkg-config —libs opencv`
#CONFIG += link_pkgconfig

#INCLUDEPATH += F:/opencv/build/include \

#INCLUDEPATH += F:/opencv/sources/modules/core/include

#LIBS += -LF:/opencv/build/x64/vc12/bin
#LIBS += -lcv100 -lcvaux100
