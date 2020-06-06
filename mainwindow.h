#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"
#include <QMessageBox>
#include <QMoveEvent>
#include <QString>
#include <QClipboard>
#include <QScrollBar>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void uiInit();
    QString createScript(QString a);

private:
    Ui::MainWindow *ui;
    QString a,b,c,d,m;
    bool m_move;
    int material_index;
    QString name;
    QPoint m_startPoint;
    QPoint m_windowPoint;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void buttonClick();//导航栏按钮Click
    void on_tbClose_clicked();//退出按钮clicked
    void on_tbAbout_clicked();//关于按钮
    void on_tbMini_clicked();//最小化按钮
    void on_tbDisplayNow_clicked();//显示当前脚本
    void bar_changed(int value);//滚动条滚动
    void on_tbCopy_clicked();//复制到剪贴板

    //增减表格
    void on_tbCondAdd_clicked();
    void on_tbCondSub_clicked();
    void on_tbLateAdd_clicked();
    void on_tbLateSub_clicked();
    void on_tbSpecAdd_clicked();
    void on_tbSpecSub_clicked();
    void on_tbInteAdd_clicked();
    void on_tbInteSub_clicked();

    //选择热源子程序路径
    void on_tbLoad_2_clicked();
    void on_tbDisplayAll_clicked();
};

#endif // MAINWINDOW_H
