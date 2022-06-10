#include "spade.h"

#include "menu.h"

Spade::Spade() {};

//���ø�����
void Spade::setParent(Menu* parent) {
    setAcceptedMouseButtons(Qt::LeftButton);
    this->parent = parent;
}


QRectF Spade::boundingRect() const {
    return QRectF(0, 0, 60, 55);
}

//��д��ͼ�¼�
void Spade::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
    QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPixmap img(":/Mainwindow/game_image/spade2.png");
    img = img.scaled(60, 55);
    painter->drawPixmap(0, 0, img);
}

//��д������¼�
void Spade::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    //���������ʽ
    if (parent->parent->isRemove == false) {
        parent->parent->isRemove = true;
        this->parent->parent->setMouse(1);
    }
    else {
        parent->parent->isRemove = false;
        this->parent->parent->setMouse(0);
    }
}

//��д����ͷ��¼�
void Spade::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
   
}
