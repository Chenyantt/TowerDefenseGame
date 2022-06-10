#include "rally.h"

#include "menu.h"

Rally::Rally() {};

//设置父物体
void Rally::setParent(Menu* parent) {
    setAcceptedMouseButtons(Qt::LeftButton);
    this->parent = parent;
}

//重写碰撞检测函数
QRectF Rally::boundingRect() const {
    return QRectF(0, 0, 60, 55);
}

//重写绘图事件
void Rally::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
    QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPixmap img(":/Mainwindow/game_image/rally.png");
    img = img.scaled(60, 55);
    painter->drawPixmap(0, 0, img);
}

//重写鼠标点击事件
void Rally::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (parent->parent->isRally == false) {
        parent->parent->isRally = true;
        this->parent->parent->setMouse(2);
    }
    else {
        parent->parent->isRemove = false;
        this->parent->parent->setMouse(0);
    }
}

//重写鼠标释放事件
void Rally::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {

}