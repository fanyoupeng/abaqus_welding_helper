#ifndef REFRESH_H
#define REFRESH_H

#include <QWidget>
#include <QTimer>

class Refresh : public QWidget{
    Q_OBJECT
public:
    Refresh(QWidget *parent=0);
    int value=0;
    int x=500;
    int y=10;
    float opacity=1;
    QColor color=QColor("#00ffaa");
    void refresh_once();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QTimer m_timer;

private slots:
    void onTimeout();
};

#endif
