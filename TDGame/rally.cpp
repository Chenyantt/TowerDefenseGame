#include "rally.h"

#include "menu.h"

Rally::Rally() {};

//���ø�����
void Rally::setParent(Menu* parent) {
    setAcceptedMouseButtons(Qt::LeftButton);
    this->parent = parent;
}

//��д��ײ��⺯��
QRectF Rally::boundingRect() const {
    return QRectF(0, 0, 60, 55);
}

//��д��ͼ�¼�
void Rally::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
    QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPixmap img(":/Mainwindow/game_image/rally.png");
    img = img.scaled(60, 55);
    painter->drawPixmap(0, 0, img);
}

//��д������¼�
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

//��д����ͷ��¼�
void Rally::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {

}