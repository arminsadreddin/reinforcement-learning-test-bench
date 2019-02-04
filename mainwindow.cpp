#include "mainwindow.h"
#include "ui_mainwindow.h"
int window_width = 850;
int window_height = 500;
int square_width = window_width / 4;
int square_height = window_height / 3;
int agent_col = 0;
int agent_row = 2;

struct action{
    double up;
    double right;
    double down;
    double left;
};

action state_action[3][4];

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

    draw_map();

//    if(agent_col == 0){
//        agent_col = 1;
//    }
//    else if(agent_col == 1){
//        agent_col = 0;
//    }

}
void QWidget::update(){
    cout << "update"<<endl;
}
void MainWindow::draw_map(){


    double value_map[105][68] = {0};

    //load image
    QPixmap px;
    QPixmap agent;
    px.load("/home/arminsadreddin/maze_runner/background.png");
    agent.load("/home/arminsadreddin/maze_runner/agent.png");

    QPainter p(&px);

    p.drawPixmap( (agent_col * square_width)+(square_width/2)-15  , (agent_row * square_height)+(square_height/2) - 15,agent);

    //map draw starts


    QColor path_color(0,255,0);
    QPen path_pen(path_color);
    path_pen.setWidth(4);

    QColor grid_color(0,0,255);
    QColor wall_color(0,0,0);
    QColor goal_color(255,215,0);
    QColor pit_color(255,0,0);

    QPen grid_pen(grid_color);
    QPen wall_pen(wall_color);
    QPen goal_pen(goal_color);
    QPen pit_pen(pit_color);
    grid_pen.setWidth(4);
    state_action[0][0].left = 0.8;
    state_action[0][0].up = 0.6;
    state_action[0][0].right = 0.4;
    state_action[0][0].down = 0.2;

    for(int row = 0 ; row <= 3 ; row++){
        for(int col = 0 ; col <= 2 ; col++){
            p.setOpacity(1.0);
            bool special_obj = false;
            p.setPen(grid_pen);
            int start_y = col * square_height;
            int start_x = row * square_width;
            QRect square(start_x , start_y , square_width , square_height);
            if(row == 3 && col == 0){
                special_obj = true;
                p.fillRect(square,goal_color);
                p.setPen(goal_pen);
            }
            if(row == 3 && col == 1){
                special_obj = true;
                p.fillRect(square,pit_color);
                p.setPen(pit_pen);
            }
            if(row == 1 && col == 1){
                special_obj = true;
                p.fillRect(square,wall_color);
                p.setPen(wall_pen);
            }
            p.drawRect(square);
            if(!special_obj){
                p.setPen(path_pen);
                QPainterPath left;
                left.moveTo(start_x,start_y);
                left.lineTo(start_x+square_width/2,start_y+square_height/2);
                left.lineTo(start_x,start_y + square_height);
                left.lineTo(start_x,start_y);
                p.setOpacity(state_action[col][row].left);
                p.fillPath(left,path_color);
//                const QString v = "value";
//                qreal x = start_x + 100;
//                qreal y = start_y + 100;
//                const QFont f;
//                left.addText(x,y,f,v);
                p.drawPath(left);


                QPainterPath up;
                up.moveTo(start_x,start_y);
                up.lineTo(start_x+square_width/2,start_y+square_height/2);
                up.lineTo(start_x + square_width,start_y);
                up.lineTo(start_x,start_y);
                p.setOpacity(state_action[col][row].up);
                p.fillPath(up,path_color);
                p.drawPath(up);

                QPainterPath right;
                right.moveTo(start_x + square_width,start_y);
                right.lineTo(start_x+square_width/2,start_y+square_height/2);
                right.lineTo(start_x + square_width,start_y + square_height);
                right.lineTo(start_x + square_width,start_y);
                p.setOpacity(state_action[col][row].right);
                p.fillPath(right,path_color);
                p.drawPath(right);

                QPainterPath down;
                down.moveTo(start_x+square_width/2,start_y+square_height/2);
                down.lineTo(start_x+square_width,start_y+square_height);
                down.lineTo(start_x,start_y + square_height);
                down.lineTo(start_x+square_width/2,start_y+square_height/2);
                p.setOpacity(state_action[col][row].down);
                p.fillPath(down,path_color);
                p.drawPath(down);
            }
        }
    }

    p.end();

    ui->map->setPixmap(px);

}


//QPainterPath path;
//      // Set pen to this point.
//      path.moveTo (startPointX1, startPointY1);
//      // Draw line from pen point to this point.
//      path.lineTo (endPointX1, endPointY1);

//      path.moveTo (endPointX1, endPointY1);
//      path.lineTo (endPointX2,   endPointY2);

//      path.moveTo (endPointX2,   endPointY2);
//      path.lineTo (startPointX1, startPointY1);

//      painter.setPen (Qt :: NoPen);
//      painter.fillPath (path, QBrush (QColor ("blue")));









