QT       += core gui widgets

CONFIG   += c++17

TARGET   = cestionaire
TEMPLATE = app

# Dossier racine du projet (relatif à build/)
ROOT = ..

INCLUDEPATH += $$ROOT/src \
               $$ROOT/json

SOURCES += \
    $$ROOT/main.cpp \
    $$ROOT/src/app.cpp \
    $$ROOT/src/crypto.cpp \
    $$ROOT/src/jsonGestioner.cpp \
    $$ROOT/src/passgen.cpp \
    $$ROOT/src/qtWindow/mainwindow.cpp

HEADERS += \
    $$ROOT/src/App.hpp \
    $$ROOT/src/Crypto.hpp \
    $$ROOT/src/JsonGestioner.hpp \
    $$ROOT/src/Passgen.hpp \
    $$ROOT/src/qtWindow/mainwindow.h
