#include "refresh.h"
#include <QPainter>
#include <QtDebug>

Refresh::Refresh(QWidget *parent)
    :QWidget(parent){
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void Refresh::refresh_once(){
    m_timer.start(5);//5毫秒
}

void Refresh::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setBrush(color);//填充颜色
    painter.setOpacity(opacity);//透明度
    painter.drawRect(QRectF(0, 0,value,y));//画矩形
}

void Refresh::onTimeout(){
    if(value+10<=this->width()){
        value+=10;
    }
    else{
        value=0;
        m_timer.stop();
    }
    update();
}
