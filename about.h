#ifndef ABOUT_H
#define ABOUT_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();
    void guiInit();

private:
    QLabel *lb_1;
    QLabel *lb_2;
    QLabel *lb_3;
    QLabel *lb_4;
    QPushButton *bt_1;

private slots:
    void btQuit();
    void openUrl(QString url);
};
#endif // ABOUT_H
