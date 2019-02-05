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
#include <unistd.h>
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
    void agent_move();

    void rand_move();
    void best_move();
    double get_cur_state_reward();
    double get_state_best_value();


    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent *e);

};


#endif // MAINWINDOW_H
