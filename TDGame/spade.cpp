#include "spade.h"

#include "menu.h"

Spade::Spade() {};

//设置父物体
void Spade::setParent(Menu* parent) {
    setAcceptedMouseButtons(Qt::LeftButton);
    this->parent = parent;
}


QRectF Spade::boundingRect() const {
    return QRectF(0, 0, 60, 55);
}

//重写绘图事件
void Spade::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
    QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPixmap img(":/Mainwindow/game_image/spade2.png");
    img = img.scaled(60, 55);
    painter->drawPixmap(0, 0, img);
}

//重写鼠标点击事件
void Spade::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    //设置鼠标样式
    if (parent->parent->isRemove == false) {
        parent->parent->isRemove = true;
        this->parent->parent->setMouse(1);
    }
    else {
        parent->parent->isRemove = false;
        this->parent->parent->setMouse(0);
    }
}

//重写鼠标释放事件
void Spade::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
   
}
