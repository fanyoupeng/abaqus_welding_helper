#include "ui/mainWindow/mainwindow.h"//程序主窗口
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
