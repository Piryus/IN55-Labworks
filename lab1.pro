QT       += core gui widgets

TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwidget.cpp \
    src/geometryengine.cpp \
    src/quaternion.cpp \
    src/camera.cpp

HEADERS += \
    src/mainwidget.h \
    src/geometryengine.h \
    src/quaternion.h \
    src/camera.h

RESOURCES += \
    ressources/shaders.qrc \
