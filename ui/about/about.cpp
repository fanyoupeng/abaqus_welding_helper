#include "about.h"
#include <QDebug>

About::About(QWidget *parent) :
    QDialog(parent){
    lb_1=new QLabel(this);
    lb_2=new QLabel(this);
    lb_3=new QLabel(this);
    lb_4=new QLabel(this);
    bt_1=new QPushButton(this);
    guiInit();
}

About::~About(){
    delete lb_1;
    delete lb_2;
    delete lb_3;
    delete lb_4;
    delete bt_1;

}

void About::guiInit(){
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->resize(300, 180);
    this->setMinimumSize(QSize(300, 180));
    this->setMaximumSize(QSize(300, 180));
    this->setStyleSheet(QStringLiteral("color:#ffffff;background-color: #50585a;"));

    lb_1->setGeometry(QRect(20, 20, 50, 50));
    lb_1->setStyleSheet(QStringLiteral("background-image: url(:/image/mylogo.png);"));

    lb_2->setGeometry(QRect(70, 20, 230, 50));
    lb_2->setAlignment(Qt::AlignCenter);
    lb_2->setText("Abaqus焊接助手V1.0");
    lb_2->setStyleSheet(QStringLiteral("font-size:22px;"));

    lb_3->setGeometry(QRect(40,70, 260, 40));
    lb_3->setText("作者：樊友鹏\n邮箱：ycsfyp@gmail.com");
    lb_3->setStyleSheet(QStringLiteral("font-size:15px;"));

    lb_4->setGeometry(QRect(40,110, 260, 20));
    lb_4->setText("<a style='color: #c2f0ec;'href=\"https://ycs_fyp.gitee.io/\">了解更多");
    lb_4->setStyleSheet(QStringLiteral("font-size:15px;border-style:none;"));

    bt_1->setGeometry(QRect(0, 130, 300, 50));
    bt_1->setStyleSheet(QStringLiteral("background-color: #383e41;font-size:20px;"));
    bt_1->setText("确定");

    connect(this->bt_1,SIGNAL(clicked(bool)),this,SLOT(btQuit()));
    connect(this->lb_4, SIGNAL(linkActivated(QString)), this, SLOT(openUrl(QString)));
}

void About::btQuit(){
    this->close();
}

void About::openUrl(QString url){
    QDesktopServices::openUrl(QUrl(url));
}
