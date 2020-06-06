#ifndef CREATE_H
#define CREATE_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QMoveEvent>
#include <QFile>

#define NONE 0
#define SIMPLE 1
#define REAL 2
#define FLUX 3

class Create : public QDialog
{
    Q_OBJECT

public:
    explicit Create(QWidget *parent = 0);
    ~Create();
    void guiInit();
    void created();
    int heat_type;

private:
    QLabel *lb;
    QToolButton *bt_simp;
    QToolButton *bt_real;
    QToolButton *bt_flux;
    QPushButton *bt_cancel;

private slots:
    void btCancel();
    void btSimp();
    void btReal();
    void btFlux();

signals:
    void set_pro_type(int heat_type);

};
#endif // ABOUT_H
