#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qstring.h>
int window_width = 850;
int window_height = 500;
int square_width = window_width / 4;
int square_height = window_height / 3;
int agent_col = 0;
int agent_row = 2;

string my_move;

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

    unsigned int microsecends = 300000;
    usleep(microsecends);
    draw_map();
    agent_move();



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


    //map draw starts


    QColor path_good_color(0,255,0);
    QColor path_bad_color(255,0,0);
    QPen path_pen(path_good_color);
    path_pen.setWidth(4);

    QColor grid_color(0,0,255);
    QColor wall_color(0,0,0);
    QColor goal_color(255,215,0);
    QColor pit_color(255,0,0);
    QColor text_color(0,0,0);

    QPen grid_pen(grid_color);
    QPen wall_pen(wall_color);
    QPen goal_pen(goal_color);
    QPen pit_pen(pit_color);
    QPen text_pen(text_color);
    grid_pen.setWidth(4);


    //    state_action[0][0].left = -0.8;
    //    state_action[0][0].up = -0.6;
    //    state_action[0][0].right = -0.4;
    //    state_action[0][0].down = -0.2;

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
                if(state_action[col][row].left >= 0){
                    p.setOpacity(state_action[col][row].left);
                    p.fillPath(left,path_good_color);
                }
                else{
                    p.setOpacity(-state_action[col][row].left);
                    p.fillPath(left,path_bad_color);
                }
                p.drawPath(left);
                p.setOpacity(1.0);
                p.setPen(text_pen);
                QString left_value = QString::number(state_action[col][row].left);
                p.drawText(start_x+20,start_y + square_height/2,left_value);


                p.setPen(path_pen);
                QPainterPath up;
                up.moveTo(start_x,start_y);
                up.lineTo(start_x+square_width/2,start_y+square_height/2);
                up.lineTo(start_x + square_width,start_y);
                up.lineTo(start_x,start_y);
                if(state_action[col][row].up >= 0){
                    p.setOpacity(state_action[col][row].up);
                    p.fillPath(up,path_good_color);
                }
                else{
                    p.setOpacity(-state_action[col][row].up);
                    p.fillPath(up,path_bad_color);
                }
                p.drawPath(up);
                p.setOpacity(1.0);
                p.setPen(text_pen);
                QString up_value = QString::number(state_action[col][row].up);
                p.drawText(start_x+(square_width/2) - 10,start_y+20,up_value);


                p.setPen(path_pen);
                QPainterPath right;
                right.moveTo(start_x + square_width,start_y);
                right.lineTo(start_x+square_width/2,start_y+square_height/2);
                right.lineTo(start_x + square_width,start_y + square_height);
                right.lineTo(start_x + square_width,start_y);
                if(state_action[col][row].right >= 0){
                    p.setOpacity(state_action[col][row].right);
                    p.fillPath(right,path_good_color);
                }
                else{
                    p.setOpacity(-state_action[col][row].right);
                    p.fillPath(right,path_bad_color);
                }


                p.drawPath(right);
                p.setOpacity(1.0);
                p.setPen(text_pen);
                QString right_value = QString::number(state_action[col][row].right);
                p.drawText(start_x+square_width - 30,start_y+square_height/2,right_value);


                p.setPen(path_pen);
                QPainterPath down;
                down.moveTo(start_x+square_width/2,start_y+square_height/2);
                down.lineTo(start_x+square_width,start_y+square_height);
                down.lineTo(start_x,start_y + square_height);
                down.lineTo(start_x+square_width/2,start_y+square_height/2);
                if(state_action[col][row].down >= 0){
                    p.setOpacity(state_action[col][row].down);
                    p.fillPath(down,path_good_color);
                }
                else{
                    p.setOpacity(-state_action[col][row].down);
                    p.fillPath(down,path_bad_color);
                }

                p.drawPath(down);
                p.setOpacity(1.0);
                p.setPen(text_pen);
                QString down_value = QString::number(state_action[col][row].down);
                p.drawText(start_x+(square_width/2) - 10,start_y+square_height-10,down_value);

            }
        }
    }


    p.drawPixmap( (agent_col * square_width)+(square_width/2)-15  , (agent_row * square_height)+(square_height/2) - 15,agent);


    p.end();

    ui->map->setPixmap(px);

}
void MainWindow::agent_move(){
    double alpha_cmp = rand()%100;
    alpha_cmp = alpha_cmp/100.0;
    if(alpha_cmp <= alpha){
        best_move();
    }
    else{
        rand_move();
    }
    double reward = get_cur_state_reward();

    if(agent_row == 1 && agent_col == 1){

        if(my_move == "UP"){
            agent_row++;
        }
        if(my_move == "RIGHT"){
            agent_col--;
        }
        if(my_move == "DOWN"){
            agent_row--;
        }
        if(my_move == "LEFT"){
            agent_col++;
        }
        if(reward == 0){
            reward+= m_gamma * get_state_best_value();
        }
        if(my_move == "UP"){
            state_action[agent_row][agent_col].up = reward;//max(reward,state_action[agent_row+1][agent_col].up);
        }
        if(my_move == "RIGHT"){
            state_action[agent_row][agent_col].right = reward;//max(reward,state_action[agent_row+1][agent_col].right);
        }
        if(my_move == "DOWN"){
            state_action[agent_row][agent_col].down=reward;//max(reward,state_action[agent_row+1][agent_col].down);
        }
        if(my_move == "LEFT"){
            state_action[agent_row][agent_col].left=reward;//max(reward,state_action[agent_row+1][agent_col].left);
        }
    }
    else{
        if(reward == 0){
            reward+= m_gamma * get_state_best_value();
        }
        if(my_move == "UP"){
            state_action[agent_row+1][agent_col].up = reward;//max(reward,state_action[agent_row+1][agent_col].up);
        }
        if(my_move == "RIGHT"){
            state_action[agent_row][agent_col-1].right = reward;//max(reward,state_action[agent_row+1][agent_col].right);
        }
        if(my_move == "DOWN"){
            state_action[agent_row-1][agent_col].down=reward;//max(reward,state_action[agent_row+1][agent_col].down);
        }
        if(my_move == "LEFT"){
            state_action[agent_row][agent_col+1].left=reward;//max(reward,state_action[agent_row+1][agent_col].left);
        }
    }

    if(agent_col < 0 || agent_col > 3){
        agent_col = 0;
        agent_row = 2;
    }
    if(agent_row < 0 || agent_row > 2){
        agent_col = 0;
        agent_row = 2;
    }
    if(agent_row == 0 && agent_col == 3){
        agent_col = 0;
        agent_row = 2;
    }
    if(agent_row == 1 && agent_col == 3){
        agent_col = 0;
        agent_row = 2;
    }







}
void MainWindow::rand_move(){
    int rand_side = rand()%4;
    if(rand_side == 0){
        //up
        my_move = "UP";
        agent_row--;
    }
    if(rand_side == 1){
        my_move = "RIGHT";
        agent_col++;
        //right
    }
    if(rand_side == 2){
        my_move = "DOWN";
        agent_row++;
        //down
    }
    if(rand_side == 3){
        my_move = "LEFT";
        agent_col--;
        //left
    }
}
void MainWindow::best_move(){
    double max_value = std::max(state_action[agent_row][agent_col].up , state_action[agent_row][agent_col].right);
    max_value = std::max(max_value , state_action[agent_row][agent_col].down);
    max_value = std::max(max_value , state_action[agent_row][agent_col].left);

    vector<int> candidates;
    candidates.clear();
    if(max_value == state_action[agent_row][agent_col].up){
        candidates.push_back(0);
    }
    if(max_value == state_action[agent_row][agent_col].right){
        candidates.push_back(1);
    }
    if(max_value == state_action[agent_row][agent_col].down){
        candidates.push_back(2);
    }
    if(max_value == state_action[agent_row][agent_col].left){
        candidates.push_back(3);
    }

    int rand_index = rand()%candidates.size();
    int chosen_move = candidates.at(rand_index);
    if(chosen_move == 0){
        //up
        my_move = "UP";
        agent_row--;
    }
    if(chosen_move == 1){
        //right
        my_move = "RIGHT";
        agent_col++;
    }
    if(chosen_move == 2){
        //down
        my_move = "DOWN";
        agent_row++;
    }
    if(chosen_move == 3){
        //left
        my_move = "LEFT";
        agent_col--;
    }

}
double MainWindow::get_cur_state_reward(){
    if(agent_row > 2){
        return -1.0;
    }
    if(agent_col > 3){
        return -1.0;
    }
    if(agent_row < 0){
        return -1.0;
    }
    if(agent_col < 0){
        return -1.0;
    }
    if(agent_row == 0 && agent_col == 3){
        return +1.0;
    }
    if(agent_row == 1 && agent_col == 3){
        return -1.0;
    }
    return 0.0;
}
double MainWindow::get_state_best_value(){
    double max_value = std::max(state_action[agent_row][agent_col].up , state_action[agent_row][agent_col].right);
    max_value = std::max(max_value , state_action[agent_row][agent_col].down);
    max_value = std::max(max_value , state_action[agent_row][agent_col].left);
    return max_value;
}




















