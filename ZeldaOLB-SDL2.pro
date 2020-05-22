CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_gfx

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
    src/Carte.cpp \
    src/Encyclopedie.cpp \
    src/Ennemi.cpp \
    src/Generique.cpp \
    src/Jeu.cpp \
    src/Joueur.cpp \
    src/Keyboard.cpp \
    src/Listable.cpp \
    src/Menu.cpp \
    src/Monde.cpp \
    src/Objet.cpp \
    src/Personnage.cpp \
    src/Pnj.cpp \
    src/Projectile.cpp \
    src/Snipe.cpp \
    src/Statut.cpp \
    src/Texte.cpp \
    src/ZoneRect.cpp \
    src/main.cpp
