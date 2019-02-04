#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <qpainter.h>
#include <qpicture.h>
#include <random>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    //QLabel agent_label;
    //agent_label.setPixmap(agent);
    //agent_label.setGeometry(10,10,10,10);
    //agent_label.show();



    return a.exec();
}






