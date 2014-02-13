#-------------------------------------------------
#
# Project created by QtCreator 2014-02-13T13:30:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2dmap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    importdialog.cpp \
    element.cpp \
    elementtemplate.cpp \
    elementtemplatemanager.cpp \
    filemanager.cpp \
    imgproc.cpp

HEADERS  += mainwindow.h \
    importdialog.h \
    element.h \
    elementtemplate.h \
    elementtemplatemanager.h \
    filemanager.h \
    imgproc.h

FORMS    += mainwindow.ui \
    importdialog.ui

unix {
INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib \
    -lopencv_core \
    -lopencv_imgproc \
    -lopencv_highgui \
    -lopencv_photo \
}

win32 {
INCLUDEPATH += C:\opencv248\build\install\include
LIBS += C:\\opencv248\\build\\lib\\libopencv_core248.dll.a \
    C:\\opencv248\\build\\lib\\libopencv_highgui248.dll.a \
    C:\\opencv248\\build\\lib\\libopencv_imgproc248.dll.a \
    C:\\opencv248\\build\\lib\\libopencv_photo248.dll.a
}

RESOURCES += \
    assets.qrc
