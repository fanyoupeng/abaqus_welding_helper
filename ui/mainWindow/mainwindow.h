#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTextEdit>
#include "ui/about/about.h"
#include "ui/create/create.h"
#include "ui/body/body.h"
#include "ui/refresh/refresh.h"
#include <QMessageBox>
#include <QMoveEvent>
#include <QString>
#include <QClipboard>
#include <QScrollBar>
#include <QFileDialog>
#include <QFile>
#include <QIcon>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void uiInit();
    void mainInit();
    void otherInit();
    QString createScript(QString a);
    int heat_type;

private:
    body *my_body;
    Refresh *my_refresh;
    bool m_move;
    QString name;
    QPoint m_startPoint;
    QPoint m_windowPoint;

    //控件
    QToolButton *tbCreat;
    QToolButton *tbAbout;
    QToolButton *tbMini;
    QToolButton *tbClose;
    QToolButton *tbDisplayNow;
    QToolButton *tbDisplayAll;
    QToolButton *tbChange;
    QToolButton *tbCopy;

    QToolButton *tbInte;
    QToolButton *tbLoad;
    QToolButton *tbMate;
    QToolButton *tbPart;
    QToolButton *tbStep;

    QLabel *lb1;
    QLabel *lb2;

    QWidget *wdLeft;
    QWidget *wdScript;
    QWidget *wdsa;
    QWidget *wdTool;

    QScrollArea *saWeld;

    QTextEdit *teScript;

    QVBoxLayout *vl1;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void set_pro_type(int);//设置工程类型

    void buttonClick();//导航栏按钮Click
    void on_tbClose_clicked();//退出按钮clicked
    void on_tbAbout_clicked();//关于按钮
    void on_tbMini_clicked();//最小化按钮
    void on_tbDisplayNow_clicked();//显示当前脚本
    void bar_changed(int value);//滚动条滚动
    void on_tbChange_clicked();//转化为应力分析
    void on_tbCopy_clicked();//复制到剪贴板

    void on_tbDisplayAll_clicked();
    void on_tbCreat_clicked();
};

#endif // MAINWINDOW_H
