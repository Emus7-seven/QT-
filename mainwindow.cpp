#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
//#include <QGlobal>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusBar->addWidget(label_Sore);
    label_Sore->setText(QString("当前分数为：%1").arg(Score));
    this->setFixedSize(600,690);
    createUI();
    Snake_Head();
    createFood();
    connect(ui->actionkai,&QAction::triggered,[=](){
        timer->start(500);
    });
    connect(ui->actionzhant,&QAction::triggered,[=](){
        timer->stop();
    });
    connect(ui->actiontuichu,&QAction::triggered,[=](){
        this->close();
    });
    connect(timer,&QTimer::timeout,[=](){
        EatFoodBeLong();
        aotuMove();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_W :
        qDebug()<<"w";
        decoration = 2;
        break;
    case Qt::Key_A :
        qDebug()<<"a";
        decoration = 1;
        break;
    case Qt::Key_D :
        qDebug()<<"d";
        decoration = 0;
        break;
    case Qt::Key_S :
        qDebug()<<"s";
        decoration = 3;
        break;
    }
}

void MainWindow::createUI(){
    int t = 0;
    for(int i = 0;i<15;i++){
        for(int j=0;j<15;j++){
            PicLabel[t].setParent(this);
            PicLabel[t].setPixmap(pix);
            PicLabel[t].setGeometry(j*40,i*40+40,40,40);
            PicLabel[t].show();
            t++;
        }
    }
}

void MainWindow::Snake_Head(){
    qsrand(QTime(1,1,1).secsTo(QTime::currentTime()));
    pos = rand()%225;
    qDebug() << pos;
    PicLabel[pos].setPixmap(pix_head);
    PicLabel[pos-1].setPixmap(pix_food);
    PicLabel[pos-2].setPixmap(pix_food);
    Snake_xy[0][0] = pos;  //蛇头
    Snake_xy[1][0] = pos-1;  //蛇身
    Snake_xy[2][0] = pos-2;  //蛇尾
}

void MainWindow::aotuMove(){
    for(int j=0;j<length;j++){
        PicLabel[Snake_xy[j][0]].setPixmap(pix);
    }

    for(int j=length-1;j>0;j--){
        Snake_xy[j][0] = Snake_xy[j-1][0];

    }
    switch(decoration){
    case 0:         //向右
        PicLabel[Snake_xy[0][0]].setPixmap(pix_head);
        Snake_xy[0][0]+=1;
        break;
    case 1:           //向左
        PicLabel[Snake_xy[0][0]].setPixmap(pix_head_left);
        Snake_xy[0][0]-=1;
        break;
    case 2:            //向上
        PicLabel[Snake_xy[0][0]].setPixmap(pix_head_up);
        Snake_xy[0][0]-=15;
        break;
    case 3:         //向下
        PicLabel[Snake_xy[0][0]].setPixmap(pix_head_buttom);
        Snake_xy[0][0]+=15;
        break;
    }



    for(int j=0;j<length;j++){
        if(j==0){
            switch(decoration){
            case 0:         //向右
                PicLabel[Snake_xy[0][0]].setPixmap(pix_head);
                break;
            case 1:           //向左
                PicLabel[Snake_xy[0][0]].setPixmap(pix_head_left);
                break;
            case 2:            //向上
                PicLabel[Snake_xy[0][0]].setPixmap(pix_head_up);
                break;
            case 3:         //向下
                PicLabel[Snake_xy[0][0]].setPixmap(pix_head_buttom);
                break;
            }
        }else{
            PicLabel[Snake_xy[j][0]].setPixmap(pix_food);
        }

    }





}

void MainWindow::createFood(){
    qsrand(QTime(1,1,2).secsTo(QTime::currentTime()));
    pos_food = rand()%225;
    qDebug()<<pos_food;
    PicLabel[pos_food].setPixmap(pix_food);
}

void MainWindow::EatFoodBeLong(){
    if(Snake_xy[0][0]==pos_food){
        qDebug()<< "吃到了";
        Score++;
        Snake_xy[length][0]=pos_food;
        length++;
        createFood();
        label_Sore->setText(QString("当前分数为：%1").arg(Score));
    }
}
