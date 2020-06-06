#include "create.h"

Create::Create(QWidget *parent) :
    QDialog(parent){
    guiInit();
}

Create::~Create(){
    delete lb;
    delete bt_simp;
    delete bt_real;
    delete bt_flux;
    delete bt_cancel;
}

void Create::guiInit(){
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->resize(240, 160);
    this->setMinimumSize(QSize(240, 160));
    this->setMaximumSize(QSize(240, 160));
    this->setStyleSheet(QStringLiteral("color:#ffffff;background-color: #50585a;"));

    lb=new QLabel(this);
    lb->setGeometry(QRect(0, 0,240, 30));
    lb->setAlignment(Qt::AlignCenter);
    lb->setStyleSheet(QStringLiteral("font-size:20px;background-color: #383e41;"));
    lb->setText("选择热源类型");

    bt_simp=new QToolButton(this);
    bt_simp->setGeometry(QRect(0,30, 80, 80));
    bt_simp->setStyleSheet(QStringLiteral("font-size:15px;border-style:none;"));
    QIcon icon3;
    icon3.addFile(QStringLiteral(":/image/S_.png"), QSize(), QIcon::Normal, QIcon::Off);
    bt_simp->setIcon(icon3);
    bt_simp->setIconSize(QSize(50,50));//设置图标大小
    bt_simp->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bt_simp->setText("简单");

    bt_real=new QToolButton(this);
    bt_real->setGeometry(QRect(80,30, 80, 80));
    bt_real->setStyleSheet(QStringLiteral("font-size:15px;border-style:none;"));
    QIcon icon4;
    icon4.addFile(QStringLiteral(":/image/R_.png"), QSize(), QIcon::Normal, QIcon::Off);
    bt_real->setIcon(icon4);
    bt_real->setIconSize(QSize(50,50));//设置图标大小
    bt_real->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bt_real->setText("真实");

    bt_flux=new QToolButton(this);
    bt_flux->setGeometry(QRect(160,30, 80, 80));
    bt_flux->setStyleSheet(QStringLiteral("font-size:15px;border-style:none;"));
    QIcon icon5;
    icon5.addFile(QStringLiteral(":/image/F_.png"), QSize(), QIcon::Normal, QIcon::Off);
    bt_flux->setIcon(icon5);
    bt_flux->setIconSize(QSize(50,50));//设置图标大小
    bt_flux->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bt_flux->setText("FLUX");

    bt_cancel=new QPushButton(this);
    bt_cancel->setGeometry(QRect(0,110, 240, 50));
    bt_cancel->setStyleSheet(QStringLiteral("font-size:20px;border-style:none;background-color: #383e41;"));
    bt_cancel->setText("取消");

    connect(this->bt_cancel,SIGNAL(clicked(bool)),this,SLOT(btCancel()));
    connect(this->bt_simp,SIGNAL(clicked(bool)),this,SLOT(btSimp()));
    connect(this->bt_real,SIGNAL(clicked(bool)),this,SLOT(btReal()));
    connect(this->bt_flux,SIGNAL(clicked(bool)),this,SLOT(btFlux()));
}

void Create::btCancel(){
    heat_type=NONE;
    this->close();
}

void Create::created(){
    emit set_pro_type(heat_type);
    this->close();
}

void Create::btSimp(){
    heat_type=SIMPLE;
    created();
}

void Create::btReal(){
    heat_type=REAL;
    created();
}

void Create::btFlux(){
    heat_type=FLUX;
    created();
}
