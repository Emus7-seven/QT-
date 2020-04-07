#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QQueue>
//#include <QGlobal>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    QLabel * PicLabel = new QLabel[300]();
    int Snake_xy[300][2];
    int pos,i,length=3,pos_food;
    int decoration=0;
    int Score=0;
    QLabel * label_Sore = new QLabel(this);
    QTimer * timer = new QTimer(this);
    QPixmap pix = QPixmap(":/bg.jpg");
    QPixmap pix_head = QPixmap(":/right.png");
    QPixmap pix_head_buttom = QPixmap(":/buttom.png");
    QPixmap pix_head_left = QPixmap(":/left.png");
    QPixmap pix_head_up = QPixmap(":/up.png");
    QPixmap pix_food = QPixmap(":/food.png");
    ~MainWindow();
public:
    void aotuMove();   //移动
    void keyPressEvent(QKeyEvent *event);   //键盘事件
    void createUI();   //画背景
    void Snake_Head();  //随机取蛇头
    void createFood();  //随机生成食物
    void EatFoodBeLong();  //吃到食物后变长
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
