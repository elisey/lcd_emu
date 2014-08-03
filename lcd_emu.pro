#-------------------------------------------------
#
# Project created by QtCreator 2014-08-02T11:31:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lcd_emu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pixeldisplay.cpp \
    siGui/guiCore/guiCore.c \
    siGui/guiGraph/guiGraphPrimitives.c \
    siGui/guiHAL/guiLcdHAL.c \
    siGui/guiGraph/font_6x8_mono.c \
    siGui/guiGraph/font_h10.c \
    siGui/guiGraph/font_h10_bold.c \
    siGui/guiGraph/font_h12.c \
    siGui/guiGraph/font_h32.c \
    siGui/guiGraph/widget_images.c \
    siGui/guiCore/guiMsg.c \
    siGui/guiWidgets/guiWidgetText.c


HEADERS  += mainwindow.h \
    pixeldisplay.h \
    siGui/guiConfig.h \
    siGui/guiCore/guiCore.h \
    siGui/guiGraph/guiGraphPrimitives.h \
    siGui/guiHAL/guiLcdHAL.h \
    siGui/guiGraph/guiFonts.h \
    siGui/guiGraph/guiImages.h \
    siGui/guiWidgets/guiWidgets.h \
    siGui/guiCore/guiMsg.h \
    siGui/guiCore/guiEvent.h \
    siGui/guiWidgets/guiWidgetText.h

INCLUDEPATH += "./siGUI"
INCLUDEPATH += "./siGUI/guiCore"
INCLUDEPATH += "./siGUI/guiGraph"
INCLUDEPATH += "./siGUI/guiHAL"
INCLUDEPATH += "./siGUI/guiWidgets"
