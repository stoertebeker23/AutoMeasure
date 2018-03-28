TEMPLATE = app
TARGET = AutoMeasure

#CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
#QT += gui core
QT += widgets
QT += gui

INCLUDEPATH += "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\TekVISA\Bin"

LIBS += "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\TekVISA\Bin\Visa32.dll"

SOURCES += \
    $$PWD\src\main.cpp \
    $$PWD\src\fileio.cpp \
    $$PWD\src\measurementsession.cpp \
    $$PWD\src\uart.cpp \
    $$PWD\src\visadevice.cpp \
    $$PWD\src\visaoscilloscope.cpp \
    $$PWD\src\visawaveformgenerator.cpp \
    $$PWD\src\device.cpp \
    $$PWD\src\algorythms.cpp \
    $$PWD\src\asic.cpp \
    $$PWD\src\visamultimeter.cpp

HEADERS += \
    $$PWD\include\measurementsession.h \
    $$PWD\include\fileio.h \
    $$PWD\include\device.h \
    $$PWD\include\algorythms.h \
    $$PWD\include\asic.h

DISTFILES += \
    stuff \
    sadasd
