#ifndef BODY_H
#define BODY_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>
#include <QTableWidget>
#include <QHeaderView>
#include <QToolButton>
#include <QCoreApplication>
#include <QFileDialog>
#include <QIcon>

#define THERMAL 0
#define DEFORMATION 1

class body : public QWidget
{
    Q_OBJECT

public:
    explicit body(QWidget *parent = 0);
    ~body();
    void uiInit();
    void drawLine(QString str1,QString str2);
    void drawBigTitle(QString str);
    void drawSmallTitle(QString str);
    void drawTable_A(QString name,int row,int col,const QString header[],const QString str[]);
    void drawTable_B(QString name,int row,int col,const QString header[],const QString str[]);
    void drawFile(QString name,QString str,QString initPath);
    int heat_type;
    int step_type;

private:
    QVBoxLayout *vboxLayout;

    QList <QLabel *> lbs;
    QList <QToolButton *> tbs;
    QList <QLineEdit *> les;
    QList <QTableWidget *> tws;
    QList <QSpacerItem *> sps;
    QList <QWidget *> wds;

private slots:
    void stepChange();
    void btAdd();
    void btSub();
    void fileBt();
};

#endif // BODY_H
