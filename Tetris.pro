TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Board.cpp \
        Game.cpp \
        Pieces.cpp \
        main.cpp

INCLUDEPATH += D:/Workspace/extlib/SDL2-2.0.10/include

LIBS += -LD:/Workspace/extlib/SDL2-2.0.10/lib/x64 \
          -lSDL2       \
          -lSDL2main   \

HEADERS += \
    Board.h \
    Game.h \
    Pieces.h
