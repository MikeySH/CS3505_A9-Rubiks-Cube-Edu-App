QT       += core gui widgets opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    faces.cpp \
    geometryengine.cpp \
    main.cpp \
    mainwidget.cpp \
    mainwindow.cpp \
    model.cpp \
    scenewidget.cpp

HEADERS += \
    faces.h \
    geometryengine.h \
    mainwidget.h \
    mainwindow.h \
    model.h \
    scenewidget.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc \
    shaders.qrc

macx|win32: LIBS += -L$$PWD/box2d/ -lbox2d

INCLUDEPATH += $$PWD/box2d/include
DEPENDPATH += $$PWD/box2d/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/box2d/box2d.lib
else:macx|win32-g++: PRE_TARGETDEPS += $$PWD/box2d/libbox2d.a
