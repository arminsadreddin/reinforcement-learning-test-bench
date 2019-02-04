#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <vector>
#include <iostream>
#include <QLabel>
#include <qpainter.h>
#include <qpicture.h>

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    void draw_map();
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent *e);

};


#endif // MAINWINDOW_H
