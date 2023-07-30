QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_MOC += D:\opencv_forQt\install\include\opencv2\core\mat.hpp
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
win32{
    LIBS+=-luser32
}
LIBS += -lgdi32
SOURCES += \
    KeyCapturer.cpp \
    KeyboardHook.cpp \
    OperationThread.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    KeyCapturer.h \
    KeyboardHook.h \
    OperationThread.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    auto_zh_CN.ts
    CONFIG += lrelease
    CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -LE:/XmpCache/opencv/build/x64/vc16/lib/ -lopencv_world480
else:win32:CONFIG(debug, debug|release): LIBS += -LE:/XmpCache/opencv/build/x64/vc16/lib/ -lopencv_world480d
else:unix: LIBS += -LE:/XmpCache/opencv/build/x64/vc16/lib/ -lopencv_world480

INCLUDEPATH += E:/XmpCache/opencv/build/x64/vc16/bin
INCLUDEPATH += E:/XmpCache/opencv/build/include
DEPENDPATH += E:/XmpCache/opencv/build/include

