#include "mainwindow.h"
#include "ui_mainwindow.h"
int window_width = 850;
int window_height = 500;
int square_width = window_width / 4;
int square_height = window_height / 3;
int agent_col = 0;
int agent_row = 2;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *e){




    double value_map[105][68] = {0};

    //load image
    QPixmap px;
    QPixmap agent;
    px.load("/home/arminsadreddin/maze_runner/background.png");
    agent.load("/home/arminsadreddin/maze_runner/agent.png");

    QPainter p(&px);
    p.drawPixmap( (agent_col * square_width)+(square_width/2)-15  , (agent_row * square_height)+(square_height/2) - 15,agent);

    //map draw starts

    QColor grid_color(0,0,255);
    QColor wall_color(0,0,0);
    QColor goal_color(0,255,0);
    QColor pit_color(255,0,0);
    QPen grid_pen(grid_color);
    QPen wall_pen(wall_color);
    QPen goal_pen(goal_color);
    QPen pit_pen(pit_color);
    grid_pen.setWidth(4);


    for(int row = 0 ; row <= 3 ; row++){
        for(int col = 0 ; col <= 2 ; col++){
            p.setPen(grid_pen);
            int start_y = col * square_height;
            int start_x = row * square_width;
            QRect square(start_x , start_y , square_width , square_height);
            if(row == 3 && col == 0){
                p.fillRect(square,goal_color);
                p.setPen(goal_pen);
            }
            if(row == 3 && col == 1){
                p.fillRect(square,pit_color);
                p.setPen(pit_pen);
            }
            if(row == 1 && col == 1){
                p.fillRect(square,wall_color);
                p.setPen(wall_pen);
            }
            p.drawRect(square);
        }
    }
    //map draw ends





    p.end();
//    QLabel map_label;
//    map_label.setPixmap(px);
//    map_label.setGeometry(QRect(0, 0, window_width, window_height));
//    map_label.show();

    ui->map->setPixmap(px);


}

