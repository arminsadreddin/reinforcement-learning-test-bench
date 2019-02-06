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

    double alpha = 0.7;
    double m_gamma = 0.9;

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

private slots:
    void on_start_b_clicked();
    void on_stop_b_clicked();
    void on_reset_b_clicked();
    void on_change_map_b_clicked();
    void on_alpha_t_sliderMoved(int position);
    void on_gamma_t_sliderMoved(int position);
    void on_step_t_sliderMoved(int position);
};


#endif // MAINWINDOW_H
