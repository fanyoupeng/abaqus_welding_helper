#include "mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent){
    uiInit();
}

MainWindow::~MainWindow(){
}

/*
 * UI初始化
 */
void MainWindow::uiInit(){
    //加载样式表
    QFile qss(":/qss/main.css");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    //添加logo
    this->setWindowIcon(QIcon(":/new/prefix1/CA-DCP.png")); 

    //选择热源类型
    Create *create=new Create();
    connect(create,SIGNAL(set_pro_type(int)),this,SLOT(set_pro_type(int)));//设置工程类型
    create->exec();
    delete create;

    //主窗口初始化
    mainInit();

    //主体
    my_body= new body(wdsa);
    my_body->heat_type=heat_type;
    my_body->setObjectName("my_body");
    connect(tbChange,SIGNAL(clicked(bool)),my_body,SLOT(stepChange()));//设置工程类型

    //导航栏，标题栏初始化
    otherInit();


}

//主窗口初始化
void MainWindow::mainInit(){

    this->setWindowFlags(Qt::FramelessWindowHint );//无边界窗口,不能调整窗口的大小
    this->resize(860, 430);

    //刷新
    my_refresh=new Refresh(this);
    my_refresh->setGeometry(QRect(0,30,860, 3));

    //创控件
    saWeld=new QScrollArea(this);
    saWeld->setObjectName("saWeld");

    wdLeft=new QWidget(this);
    wdLeft->setObjectName("wdLeft");
    wdScript=new QWidget(this);
    wdScript->setObjectName("wdScript");
    wdsa=new QWidget(saWeld);
    wdsa->setObjectName("wdsa");
    saWeld->setWidget(wdsa);
    wdTool=new QWidget(this);
    wdTool->setObjectName("wdTool");

    tbCreat=new QToolButton(this);
    tbCreat->setObjectName("tbCreat");
    tbAbout=new QToolButton(this);
    tbAbout->setObjectName("tbAbout");
    tbMini=new QToolButton(this);
    tbMini->setObjectName("tbMini");
    tbClose=new QToolButton(this);
    tbClose->setObjectName("tbClose");
    tbDisplayNow=new QToolButton(wdTool);
    tbDisplayNow->setObjectName("tbDisplayNow");
    tbDisplayAll=new QToolButton(wdTool);
    tbDisplayAll->setObjectName("tbDisplayAll");
    tbChange=new QToolButton(wdTool);
    tbChange->setObjectName("tbChange");
    tbCopy=new QToolButton(wdTool);
    tbCopy->setObjectName("tbCopy");

    tbInte=new QToolButton(wdLeft);
    tbInte->setObjectName("tbInte");
    tbLoad=new QToolButton(wdLeft);
    tbLoad->setObjectName("tbLoad");
    tbMate=new QToolButton(wdLeft);
    tbMate->setObjectName("tbMate");
    tbPart=new QToolButton(wdLeft);
    tbPart->setObjectName("tbPart");
    tbStep=new QToolButton(wdLeft);
    tbStep->setObjectName("tbStep");

    lb1=new QLabel(this);
    lb1->setObjectName("lb1");
    lb2=new QLabel(wdScript);
    lb2->setObjectName("lb2");

    teScript=new QTextEdit(wdScript);
    teScript->setObjectName("teScript");


    //赋属性
    saWeld->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    saWeld->setGeometry(QRect(110,40,410, 350));
    connect(saWeld->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(bar_changed(int)));

    wdLeft->setGeometry(QRect(20,40,90, 350));

    wdScript->setGeometry(QRect(540,40,300, 350));

    wdsa->setGeometry(QRect(0,0,390, 2300));

    wdTool->setGeometry(QRect(0,400,860, 30));

    tbCreat->setGeometry(QRect(0, 0,30, 30));
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/image/fire_.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbCreat->setIcon(icon1);
    tbCreat->setIconSize(QSize(16,16));//设置图标大小
    connect(tbCreat, SIGNAL(clicked()), this, SLOT(on_tbCreat_clicked()));//绑定槽函数

    tbAbout->setGeometry(QRect(770, 0,30, 30));
    QIcon icon2;
    icon2.addFile(QStringLiteral(":/image/about_.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbAbout->setIcon(icon2);
    tbAbout->setIconSize(QSize(16,16));//设置图标大小
    connect(tbAbout, SIGNAL(clicked()), this, SLOT(on_tbAbout_clicked()));//绑定槽函数

    tbMini->setGeometry(QRect(800, 0,30, 30));
    QIcon icon3;
    icon3.addFile(QStringLiteral(":/image/mini_.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbMini->setIcon(icon3);
    connect(tbMini, SIGNAL(clicked()), this, SLOT(on_tbMini_clicked()));//绑定槽函数

    tbClose->setGeometry(QRect(830, 0,30, 30));
    QIcon icon4;
    icon4.addFile(QStringLiteral(":/image/off_.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbClose->setIcon(icon4);
    connect(tbClose, SIGNAL(clicked()), this, SLOT(on_tbClose_clicked()));//绑定槽函数

    tbDisplayNow->setGeometry(QRect(30, 0,200, 30));
    QIcon icon5;
    icon5.addFile(QStringLiteral(":/image/display_.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbDisplayNow->setIcon(icon5);
    tbDisplayNow->setText("显示当前脚本");
    tbDisplayNow->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(tbDisplayNow, SIGNAL(clicked()), this, SLOT(on_tbDisplayNow_clicked()));//绑定槽函数

    tbDisplayAll->setGeometry(QRect(230, 0,200, 30));
    tbDisplayAll->setIcon(icon5);
    tbDisplayAll->setText("显示所有脚本");
    tbDisplayAll->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(tbDisplayAll, SIGNAL(clicked()), this, SLOT(on_tbDisplayAll_clicked()));//绑定槽函数

    tbChange->setGeometry(QRect(430, 0,200, 30));
    QIcon icon6;
    icon6.addFile(QStringLiteral(":/image/change_.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbChange->setIcon(icon6);
    tbChange->setText("转为应力分析");
    tbChange->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(tbChange, SIGNAL(clicked()), this, SLOT(on_tbChange_clicked()));//绑定槽函数

    tbCopy->setGeometry(QRect(630, 0,200, 30));
    QIcon icon7;
    icon7.addFile(QStringLiteral(":/image/copy_.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbCopy->setIcon(icon7);
    tbCopy->setText("复制工程脚本");
    tbCopy->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(tbCopy, SIGNAL(clicked()), this, SLOT(on_tbCopy_clicked()));//绑定槽函数

    tbInte->setGeometry(QRect(0, 210,90, 70));
    QIcon icon8;
    icon8.addFile(QStringLiteral(":/image/interaction_.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbInte->setIcon(icon8);
    tbInte->setText("交互");

    tbLoad->setGeometry(QRect(0, 280,90, 70));
    QIcon icon9;
    icon9.addFile(QStringLiteral(":/image/load_.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbLoad->setIcon(icon9);
    tbLoad->setText("加载");

    tbMate->setGeometry(QRect(0, 70,90, 70));
    QIcon icon10;
    icon10.addFile(QStringLiteral(":/image/material_.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbMate->setIcon(icon10);
    tbMate->setText("属性");

    tbPart->setGeometry(QRect(0, 0,90, 70));
    QIcon icon11;
    icon11.addFile(QStringLiteral(":/image/part_.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbPart->setIcon(icon11);
    tbPart->setText("建模");

    tbStep->setGeometry(QRect(0, 140,90, 70));
    QIcon icon12;
    icon12.addFile(QStringLiteral(":/image/step_.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbStep->setIcon(icon12);
    tbStep->setText("分析");

    //左边导航栏初始化
    QSize icoSize(24, 24);//图标大小
    QList<QToolButton *> tbtns =wdLeft->findChildren<QToolButton *>();//获取导航栏按钮
    //循环遍历
    foreach (QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);//设置图标大小
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btn->setCheckable(true);//可选中
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));//绑定槽函数
    }

    lb1->setGeometry(QRect(30, 0,740, 30));
    lb1->setText("Abaqus焊接助手");
    lb1->setAlignment(Qt::AlignCenter);

    lb2->setGeometry(QRect(0, 0,300, 30));
    lb2->setText("脚本");
    lb2->setAlignment(Qt::AlignCenter);

    teScript->setGeometry(QRect(10, 40,280, 300));
}

void MainWindow::otherInit(){
    //标题栏按钮提示
    tbCreat->setToolTip(tr("热源类型"));
    tbMini->setToolTip(tr("最小化"));
    tbClose->setToolTip(tr("关闭"));
    tbAbout->setToolTip(tr("关于"));

    //左边导航栏初始化
    QSize icoSize(24, 24);//图标大小
    QList<QToolButton *> tbtns =wdLeft->findChildren<QToolButton *>();//获取导航栏按钮
    //循环遍历
    foreach (QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);//设置图标大小
        btn->setCheckable(true);//可选中
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));//绑定槽函数
    }
    //滚动条改变槽函数
    connect(saWeld->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(bar_changed(int)));
}

/*
 * 设置工程类型
 */
void MainWindow::set_pro_type(int heat){
    heat_type=heat;
}

/*
 * 导航栏按钮
 */
void MainWindow::buttonClick(){
    QToolButton *b = (QToolButton *)sender();
    name =b->text();
    QList<QToolButton *> tbtns = wdLeft->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        if (btn == b) {
            btn->setChecked(true);
        } else {
            btn->setChecked(false);
        }
    }
    if (name=="建模") {
        saWeld->verticalScrollBar()->setValue(0);
    } else if (name=="属性"){
        saWeld->verticalScrollBar()->setValue(483);
    } else if (name=="分析") {
        saWeld->verticalScrollBar()->setValue(1182);
    } else if (name=="交互") {
        saWeld->verticalScrollBar()->setValue(1575);
    } else if (name=="加载") {
        saWeld->verticalScrollBar()->setValue(1857);
    }
}

/*
 * 创建工程
 */
void MainWindow::on_tbCreat_clicked(){
    Create *create=new Create();
    //create->move(this->x()+200,this->y()+100);
    //create->setWindowTitle(QStringLiteral("模式对话框"));
    connect(create,SIGNAL(set_pro_type(int)),this,SLOT(set_pro_type(int)));//设置工程类型
    create->exec();
    delete create;
}

/*
 * 退出按钮
 */
void MainWindow::on_tbClose_clicked(){
    this->close();
}

/*
 * 最小化按钮
 */
void MainWindow::on_tbMini_clicked(){
    this->showMinimized();
}

/*
 * 关于按钮
 */
void MainWindow::on_tbAbout_clicked(){
    About *about = new About(this);
    //about->setWindowTitle(QStringLiteral("模式对话框"));
    about->exec();
    delete about;
}

/*
 * 鼠标可拖动
 */
void MainWindow::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标.
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton){
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可.
        this->move(m_windowPoint + relativePos );
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        //改变移动状态.
        m_move = false;
    }
}


/*
 * 生成脚本
 */
QString MainWindow::createScript(QString name_str){

}

/*
 * 显示当前脚本
 */
void MainWindow::on_tbDisplayNow_clicked(){
    my_refresh->refresh_once();
}

/*
 * 显示工程脚本
 */
void MainWindow::on_tbDisplayAll_clicked(){
    my_refresh->refresh_once();
}

/*
 * 转化分析
 */
void MainWindow::on_tbChange_clicked(){
    my_refresh->refresh_once();
    if(tbChange->text()=="转为应力分析"){
        tbChange->setText("转为热分析");
    }
    else{
        tbChange->setText("转为应力分析");
    }
}

/*
 * 复制到剪贴板
 */
void MainWindow::on_tbCopy_clicked(){
    my_refresh->refresh_once();
}

//滚动条改变
void MainWindow::bar_changed(int){
    //获取滚动条数值
    int bar_value=saWeld->verticalScrollBar()->value();
    //所有导航栏按钮
    QList<QToolButton *> tbtns =wdLeft->findChildren<QToolButton *>();
    if(bar_value>1867-150)
        name="加载";
    else if(bar_value>1585-150)
        name="交互";
    else if(bar_value>1192-150)
        name="分析";
    else if(bar_value>493-150)
        name="属性";
    else
        name="建模";
    foreach (QToolButton *btn, tbtns) {
        if (btn->text()==name) {
            btn->setChecked(true);
        } else {
            btn->setChecked(false);
        }
    }
}
