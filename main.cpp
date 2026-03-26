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

/*
 * Compilation
 *
 * /Pass : make && ./cestionaire
 *
 * /build : qmake cestionaire.pro && make && ./cestionaire
 *
*/
