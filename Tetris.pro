TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Pieces.cpp \
        main.cpp

INCLUDEPATH += D:/Workspace/extlib/SDL2-2.0.10/include

LIBS += -LD:/Workspace/extlib/SDL2-2.0.10/lib/x64 \
          -lSDL2       \
          -lSDL2main   \

HEADERS += \
    Pieces.h
