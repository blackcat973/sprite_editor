#include "mainwindow.h"
#include "colorpalette.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    ColorPalette color;
    ModelController model;
    MainWindow w(model,color);
    w.show();
    return a.exec();
}
