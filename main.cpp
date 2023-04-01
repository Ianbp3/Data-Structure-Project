#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Visualizador de Listas - 1.0.4");
    w.show();

    return a.exec();
}
