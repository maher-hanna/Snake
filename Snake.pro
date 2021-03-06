TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    game.cpp \
    main.cpp \
    snake.cpp \
    grid.cpp

HEADERS += \
    snake.h \
    game.h \
    grid.h


win32 {

    INCLUDEPATH += "D:/dev/libs/SDL2-2.0.4/include"
    
    !contains(QMAKE_TARGET.arch, x86_64) {
        message("x86 build")

        LIBS += -L"D:/dev/libs/SDL2-2.0.4/lib/x86" -lSDL2 -lSDL2main  

    } else {
        message("x86_64 build")

        LIBS += -L"D:/dev/libs/SDL2-2.0.4/lib/x64" -lSDL2 -lSDL2main  
        

    }
}
unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += sdl2
}

