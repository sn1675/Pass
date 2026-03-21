/*
 * __Projet Cestionaire__
 *
 * Projet L3 informatique, INSA UPHF
 *
 * Tuteur de projet : Christophe Wilbaut
 *
 * Créateur : Nathan Courbet
 *
*/

#include <QApplication>
#include "src/qtWindow/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}


//g++ main.cpp src/*.cpp -o main && ./main
