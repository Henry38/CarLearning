#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow fen;
    fen.show();

//    //////////////////////////////////////////
//    QWidget window;
//    window.resize(300, 400);

//    QPushButton quit("quit", &window);
//    quit.setGeometry(30, 0, 100, 100);
//    QObject::connect(&quit, SIGNAL(clicked()), qApp, SLOT(quit()));

//    window.show();
//    //////////////////////////////////////////

    return app.exec();
}
