#include "mainwindow.h"
#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MainWidget widget;
    widget.show();
    return a.exec();
}
