#include "mainwindow.h"
#include "importdialog.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImportDialog w;
    w.show();

    return a.exec();
}
