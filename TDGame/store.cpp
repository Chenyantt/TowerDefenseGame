#include "store.h"

#include <qpixmap.h>
#include <qpainter.h>
#include <qcursor.h>
#include <qapplication.h>
#include <qdrag.h>
#include <qmimedata.h>
#include <QWidget>


#include "data.h"
#include "menu.h"

Store::Store() {
    /*setCursor(Qt::OpenHandCursor);*/
    setAcceptedMouseButtons(Qt::LeftButton);
}

//�����̵���Ϣ
void Store::set(QString name, QString image, int cost,Menu* parent) {
    this->name = name;
    this->image = image;
    this->cost = cost;
    this->parent = parent;
}

//��д��ײ��⺯��
QRectF Store::boundingRect() const {
    return QRectF(0, 0, 53, 50);
}

//��д��ͼ�¼�
void Store::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
    QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPixmap img(image);
    if (cost > parent->getMoney()) {
        QPixmap img(":/Mainwindow/game_image/" + name + "0.png");
        img = img.scaled(53, 50);
        painter->drawPixmap(0, 0, img);
        QFont font;
        font.setPointSizeF(10);
        painter->setFont(font);
        painter->setPen(Qt::red);
        painter->drawText(QRectF(120, 30, 100, 50), QString::number(cost));
        painter->drawPixmap(70, 30, 20, 20, QPixmap(":/Mainwindow/game_image/money.png"));
        return;
    }
    img = img.scaled(53, 50);
    painter->drawPixmap(0, 0, img);
    QFont font;
    font.setPointSizeF(10);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(QRectF(120, 30, 100, 50), QString::number(cost));
    painter->drawPixmap(70, 30, 20, 20, QPixmap(":/Mainwindow/game_image/money.png"));
}

//��д������¼�
void Store::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event)
        if (cost > parent->getMoney() && parent->parent->isRemove==false) {
           /* setCursor(Qt::ClosedHandCursor);*/
            event->setAccepted(false);
            return;
        }
}

//��д����ƶ��¼�
void Store::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    //������ק����
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance())
        return;

    QDrag* drag = new QDrag(event->widget());
    QMimeData* mime = new QMimeData();
    mime->setText(name);
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap(image).scaled(80,75));
    drag->setHotSpot(QPoint(35, 35));
    //������ק����
    drag->exec();
}

//��д����ͷ��¼�
void Store::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event)
  /*  setCursor(Qt::OpenHandCursor);*/
}