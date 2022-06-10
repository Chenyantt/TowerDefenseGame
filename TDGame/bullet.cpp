#include "bullet.h"

#include <qpainter.h>
#include <qmath.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qrect.h>
#include <qbrush.h>

#include "data.h"

Bullet::Bullet() {
    name = "";
}

//设置子弹信息
void Bullet::setBullet(QString name, Enemy* target,QGraphicsObject* parent){
    this->name = name;
    this->target = target;
}

//重写advance函数
void Bullet::advance(int phase) {
    if (!phase && name!="") {
        if (target->isDead() || !target) {
            name = "";
            this->hide();
            update();
            return;
        }
        //计算子弹的前进方向及旋转角度
		qreal theta = 0;
		QLineF l(pos(), target->pos());
		theta = -l.angle();
		if (l.length() < 15) {
            target->changeLife(-TOWERATK[name]);
            name = "";
            this->hide();
            update();
            return;
		}
        qreal dy = 15 * qSin(qDegreesToRadians(theta));
        qreal dx = 15 * qCos(qDegreesToRadians(theta));
        setRotation(theta);
        setPos(x() + dx, y() + dy);
        update();
    }
}

//重写绘图事件
void Bullet::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
    QWidget* widget) {
    if (name != "") {
        if (!target->isDead()) {
            QLineF l(pos(), target->pos());
            if (l.length() < 15) {
                QGraphicsSimpleTextItem* t = new QGraphicsSimpleTextItem(this);
                QBrush brush(QColor(255, 0, 0));
                t->setBrush(brush);
                t->setText(QString("-") + QString::number(TOWERATK[name]));
                t->setRotation(-rotation());
                t->setPos(0,-TOWERATK[name]);
                QFont font = t->font();
                font.setPixelSize(20);  // 像素大小
                t->setFont(font);
                scene()->addItem(t);
            }
        }
        QImage img(":/Mainwindow/game_image/" + name + "bullet.png");
        img = img.scaled(48, 24);
        qreal x = this->x();
        qreal y = this->y();
        painter->drawImage(boundingRect(), img);
    }
}

//重写碰撞检测函数
QRectF Bullet::boundingRect() const {
    return QRectF(-24, -12, 48, 24);
}

//重写类型函数
int Bullet::type() const {
    return Type;
}