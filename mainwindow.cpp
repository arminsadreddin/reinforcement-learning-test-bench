#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qstring.h>
int window_width = 850;
int window_height = 500;
int square_width = window_width / 4;
int square_height = window_height / 3;
int agent_col = 0;
int agent_row = 2;

bool isStochastic = false;
double noise_per = 0;
double obey_per = 100.0;

double step_value = -0.1;
string my_move;
enum mode{
    start,
    stop
};
enum view{
    value,
    policy
};

mode cur_mode = stop;
view cur_view = policy;

struct action{
    double up;
    double right;
    double down;
    double left;
};

action state_action[3][4];
string m_map[3][4] = {
    {" "," "," ","G1"},
    {" ","W"," ","P1"},
    {" "," "," "," "}
};

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


    get_ui_data();

    draw_map();
    if(cur_mode == start){
        agent_move();
    }


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

            int start_y = col * square_height;
            int start_x = row * square_width;

            if(cur_view == value){
                p.setOpacity(1.0);
                bool special_obj = false;
                p.setPen(wall_pen);

                QRect square(start_x , start_y , square_width , square_height);
                if(m_map[col][row] == "G1" || m_map[col][row] == "G2" || m_map[col][row] == "G3"){
                    if(m_map[col][row] == "G1"){
                        p.setOpacity(0.4);
                    }
                    if(m_map[col][row] == "G2"){
                        p.setOpacity(0.65);
                    }
                    if(m_map[col][row] == "G3"){
                        p.setOpacity(1.0);
                    }

                    special_obj = true;
                    p.fillRect(square,goal_color);
                    p.setPen(goal_pen);
                }
                if(m_map[col][row] == "P1" || m_map[col][row] == "P2" || m_map[col][row] == "P3"){
                    if(m_map[col][row] == "P1"){
                        p.setOpacity(0.4);
                    }
                    if(m_map[col][row] == "P2"){
                        p.setOpacity(0.65);
                    }
                    if(m_map[col][row] == "P3"){
                        p.setOpacity(1.0);
                    }
                    special_obj = true;
                    p.fillRect(square,pit_color);
                    p.setPen(pit_pen);
                }
                if(m_map[col][row] == "W"){
                    special_obj = true;
                    p.fillRect(square,wall_color);
                    p.setPen(wall_pen);
                }

                if(!special_obj){
                    p.setPen(wall_pen);
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


                    p.setPen(wall_pen);
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


                    p.setPen(wall_pen);
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


                    p.setPen(wall_pen);
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

                p.setPen(wall_pen);
                p.drawRect(square);
            }
            else{
                int start_y = col * square_height;
                int start_x = row * square_width;
                QRect square(start_x , start_y , square_width , square_height);


                if(m_map[col][row] == "G1" || m_map[col][row] == "G2" || m_map[col][row] == "G3"){
                    if(m_map[col][row] == "G1"){
                        p.setOpacity(0.4);
                    }
                    if(m_map[col][row] == "G2"){
                        p.setOpacity(0.65);
                    }
                    if(m_map[col][row] == "G3"){
                        p.setOpacity(1.0);
                    }
                    p.fillRect(square,goal_color);
                    p.setPen(goal_pen);
                }
                else if(m_map[col][row] == "P1" || m_map[col][row] == "P2" || m_map[col][row] == "P3"){
                    if(m_map[col][row] == "P1"){
                        p.setOpacity(0.4);
                    }
                    if(m_map[col][row] == "P2"){
                        p.setOpacity(0.65);
                    }
                    if(m_map[col][row] == "P3"){
                        p.setOpacity(1.0);
                    }

                    p.fillRect(square,pit_color);
                    p.setPen(pit_pen);
                }
                else if(m_map[col][row] == "W"){

                    p.fillRect(square,wall_color);
                    p.setPen(wall_pen);
                }
                else{
                    double state_max_value = std::max(state_action[col][row].up,state_action[col][row].right);
                    state_max_value = std::max(state_max_value , state_action[col][row].down);
                    state_max_value = std::max(state_max_value,state_action[col][row].left);

                    QColor arrow_color(0,0,255);
                    QPen arrow_pen(arrow_color);
                    arrow_pen.setWidth(4);
                    p.setPen(arrow_pen);
                    p.setOpacity(1.0);

                    if(state_action[col][row].up == state_max_value){
                        QPainterPath up_arrow;
                        up_arrow.moveTo(start_x+square_width/2,start_y+square_height-10);
                        up_arrow.lineTo(start_x+square_width/2,start_y+10);
                        up_arrow.lineTo(start_x+square_width/2+15,start_y+25);
                        up_arrow.lineTo(start_x+square_width/2,start_y+10);
                        up_arrow.lineTo(start_x+square_width/2-15,start_y+25);
                        p.drawPath(up_arrow);
                    }
                    if(state_action[col][row].right == state_max_value){
                        QPainterPath right_arrow;
                        right_arrow.moveTo(start_x+20,start_y+square_height/2);
                        right_arrow.lineTo(start_x+square_width - 20,start_y+square_height/2);
                        right_arrow.lineTo(start_x+square_width - 40,start_y+square_height/2+15);
                        right_arrow.lineTo(start_x+square_width - 20,start_y+square_height/2);
                        right_arrow.lineTo(start_x+square_width - 40,start_y+square_height/2-15);
                        p.drawPath(right_arrow);
                    }
                    if(state_action[col][row].down == state_max_value){
                        QPainterPath down_arrow;
                        down_arrow.moveTo(start_x+square_width/2,start_y+10);
                        down_arrow.lineTo(start_x+square_width/2,start_y+square_height-10);
                        down_arrow.lineTo(start_x+square_width/2 +15,start_y+square_height-25);
                        down_arrow.lineTo(start_x+square_width/2,start_y+square_height-10);
                        down_arrow.lineTo(start_x+square_width/2 -15,start_y+square_height-25);
                        p.drawPath(down_arrow);
                    }
                    if(state_action[col][row].left == state_max_value){
                        QPainterPath left_arrow;
                        left_arrow.moveTo(start_x+square_width - 20,start_y+square_height/2);
                        left_arrow.lineTo(start_x+20,start_y+square_height/2);
                        left_arrow.lineTo(start_x+40,start_y+square_height/2-15);
                        left_arrow.lineTo(start_x+20,start_y+square_height/2);
                        left_arrow.lineTo(start_x+40,start_y+square_height/2+15);
                        p.drawPath(left_arrow);
                    }


                }


                p.setPen(wall_pen);
                p.drawRect(square);
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

    if((agent_col > 3 || agent_col < 0 || agent_row > 2 || agent_row < 0) || m_map[agent_row][agent_col] == "W"){

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
        cout << "col : "<<agent_col<<endl;
        cout<< "row :"<<agent_row<<endl;

        reward+= m_gamma * get_state_best_value();



        reward+=step_value;

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
        reward+= m_gamma * get_state_best_value();
        reward+=step_value;
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
    if(m_map[agent_row][agent_col] == "G1"){
        agent_col = 0;
        agent_row = 2;
    }
    if(m_map[agent_row][agent_col] == "G2"){
        agent_col = 0;
        agent_row = 2;
    }
    if(m_map[agent_row][agent_col] == "G3"){
        agent_col = 0;
        agent_row = 2;
    }
    if(m_map[agent_row][agent_col] == "P1"){
        agent_col = 0;
        agent_row = 2;
    }
    if(m_map[agent_row][agent_col] == "P2"){
        agent_col = 0;
        agent_row = 2;
    }
    if(m_map[agent_row][agent_col] == "P3"){
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
        return 0.0;
    }
    if(agent_col > 3){
        return 0.0;
    }
    if(agent_row < 0){
        return 0.0;
    }
    if(agent_col < 0){
        return 0.0;
    }

    if(m_map[agent_row][agent_col] == "G1"){
        return +1.0;
    }
    if(m_map[agent_row][agent_col] == "G2"){
        return +2.0;
    }
    if(m_map[agent_row][agent_col] == "G3"){
        return +3.0;
    }
    if(m_map[agent_row][agent_col] == "P1"){
        return -1.0;
    }
    if(m_map[agent_row][agent_col] == "P2"){
        return -2.0;
    }
    if(m_map[agent_row][agent_col] == "P3"){
        return -3.0;
    }
    return 0.0;
}
double MainWindow::get_state_best_value(){
    double max_value = std::max(state_action[agent_row][agent_col].up , state_action[agent_row][agent_col].right);
    max_value = std::max(max_value , state_action[agent_row][agent_col].down);
    max_value = std::max(max_value , state_action[agent_row][agent_col].left);
    return max_value;
}
void MainWindow::on_start_b_clicked()
{
    //cout << "start clicked !"<<endl;
    cur_mode = start;
}

void MainWindow::on_stop_b_clicked()
{
    cur_mode = stop;
}

void MainWindow::on_reset_b_clicked()
{
    cur_mode = stop;
    for(int row = 0 ; row < 3 ; row++){
        for(int col = 0 ; col < 4 ; col++){
            state_action[row][col].up = 0.0;
            state_action[row][col].right = 0.0;
            state_action[row][col].down = 0.0;
            state_action[row][col].left = 0.0;
        }
    }
    agent_row = 2;
    agent_col = 0;
}

void MainWindow::on_change_map_b_clicked()
{
    //cout << "map change click"<<endl;
    QString col_str = ui->x_b->currentText();
    QString row_str = ui->y_b->currentText();
    int col = col_str.toInt();
    int row = row_str.toInt();
    //cout << ui->item_b->currentText().toStdString() << endl;
    if(ui->item_b->currentText() == "empty"){
        m_map[row][col] = " ";
    }
    if(ui->item_b->currentText() == "wall"){
        //cout << "WALL CHANGE REQ"<<endl;
        m_map[row][col] = "W";
    }
    if(ui->item_b->currentText() == "goal +1"){
        m_map[row][col] = "G1";
    }
    if(ui->item_b->currentText() == "goal +2"){
        m_map[row][col] = "G2";
    }
    if(ui->item_b->currentText() == "goal +3"){
        m_map[row][col] = "G3";
    }
    if(ui->item_b->currentText() == "pit -1"){
        m_map[row][col] = "P1";
    }
    if(ui->item_b->currentText() == "pit -2"){
        m_map[row][col] = "P2";
    }
    if(ui->item_b->currentText() == "pit -3"){
        m_map[row][col] = "P3";
    }

    //m_map[row][col]

}
void MainWindow::get_ui_data(){


    alpha = ui->alpha_le->text().toDouble();
    m_gamma = ui->gamma_le->text().toDouble();
    step_value = ui->step_le->text().toDouble();

    ui->s_act_te->setText(QString::fromStdString(my_move));
    ui->r_act_te->setText(QString::fromStdString(my_move));

    if(isStochastic){
        noise_per = ui->slip_per->text().toDouble();
        obey_per = 100.0 - (2 * noise_per);
    }

    if(ui->view_b->currentText() == "VALUE_VIEW"){
        cur_view = value;
    }
    if(ui->view_b->currentText() == "POLICY_VIEW"){
        cur_view = policy;
    }



}



void MainWindow::on_slip_b_clicked()
{
    isStochastic = !isStochastic;
}




































