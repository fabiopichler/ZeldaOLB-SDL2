
include(config.pri)

exists(config.local.pri) {
    include(config.local.pri)
}

CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += src

win32:LIBS += -lmingw32 -lSDL2main
LIBS += -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_gfx

contains(QMAKE_HOST.arch, x86_64) {

    win32:INCLUDEPATH += $${SDL2_INC_WIN64}
    win32:LIBS += -L$${SDL2_LIBPATH_WIN64}

} else {

    win32:INCLUDEPATH += $${SDL2_INC_WIN32}
    win32:LIBS += -L$${SDL2_LIBPATH_WIN32}

}

HEADERS += \
    src/Audio.h \
    src/Bouclier.h \
    src/Caisse.h \
    src/Carte.h \
    src/Common.h \
    src/Encyclopedie.h \
    src/Ennemi.h \
    src/Generique.h \
    src/Jeu.h \
    src/Joueur.h \
    src/Keyboard.h \
    src/Listable.h \
    src/Menu.h \
    src/Monde.h \
    src/Objet.h \
    src/Personnage.h \
    src/Pnj.h \
    src/Projectile.h \
    src/Snipe.h \
    src/Statut.h \
    src/Texte.h \
    src/ZoneRect.h

SOURCES += \
    src/Audio.cpp \
    src/Bouclier.cpp \
    src/Caisse.cpp \
    src/Ennemi.cpp \
    src/Jeu.cpp \
    src/Joueur.cpp \
    src/Keyboard.cpp \
    src/Listable.cpp \
    src/Monde.cpp \
    src/Objet.cpp \
    src/Personnage.cpp \
    src/Pnj.cpp \
    src/Projectile.cpp \
    src/Snipe.cpp \
    src/Statut.cpp \
    src/ZoneRect.cpp \
    src/main.cpp
