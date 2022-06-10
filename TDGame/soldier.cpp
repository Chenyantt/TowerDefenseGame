#include "soldier.h"

#include <qbrush.h>
#include <qgraphicssceneevent.h>
#include <qmimedata.h>

#include "game.h"
#include "data.h"

Soldier::Soldier() :isOccupied(false), name(""), dragOver(false),attackTarget(NULL),frame(0) {
    //设置允许接受鼠标拖拽与悬停
    setAcceptHoverEvents(true);
    setAcceptDrops(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    image = "";
    //设置血条画刷
    QBrush brush(QColor(0, 238, 0));
    healthBar->setBrush(brush);
}

//设置初始化位置
void Soldier::setPosition(QPointF point) {
    this->point = point;
    setPos(point);
}

//设置游戏配置信息
void Soldier::setGame(Game* game) {
    this->game = game;
}

//设置碰撞检测函数
QRectF Soldier::boundingRect() const {
    return QRectF(-22, -22, 44, 44);
}

//重写绘图事件
void Soldier::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
	QWidget* widget) {
    if(isOccupied) {
        Character::paint(painter, option, widget);
        //判断是否播放攻击动画
        if (!isAttacking) {
            //判断攻击方向，决定动画是否翻转
            if (name != "wall") {
                QPixmap img(image);
                img = img.scaled(63, 50);
                painter->drawPixmap(-31.5, -25, img);
            }
            else {
                QPixmap img(":/Mainwindow/game_image/" + name + QString::number((healthPoint.second - healthPoint.first) / 51 + 1) + ".png");
                img = img.scaled(63, 50);
                painter->drawPixmap(-31.5, -25, img);
            }
            
        }
        else {
            if (name != "wall") {
                //判断攻击方向，决定动画是否翻转
                QImage img(":/Mainwindow/game_image/" + name + QString::number(frame / ((name=="wizzard")?2:3) + 1) + ".png");
                if (name != "wizzard") {
                    if (!attackTarget->isDead() && x() > attackTarget->x()) {
                        img = img.mirrored(true, false);
                    }
                    img = img.scaled(63, 50);
                    painter->drawImage(-31.5, -25, img);
                }
                else {
                    img = img.scaled(150, 100);
                    painter->drawImage(-31.5, -75, img);
                }
                
            }
            else {
                QPixmap img(":/Mainwindow/game_image/" + name + QString::number((healthPoint.second-healthPoint.first)/51+1) + ".png");
                img = img.scaled(63, 50);
                painter->drawPixmap(-31.5, -25, img);
            }
            
        }
    }
}

void Soldier::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {}
void Soldier::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {}

//重写拖入事件
void Soldier::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {
    if (event->mimeData()->hasText() && !isOccupied && SOLDIERLIST.count(event->mimeData()->text())) {
        event->setAccepted(true);
        dragOver = true;
        update();
    }
    else {
        event->setAccepted(false);
    }
}

//重写拖离事件
void Soldier::dragLeaveEvent(QGraphicsSceneDragDropEvent* event) {
    Q_UNUSED(event);
    dragOver = false;
    update();
}

//重写拖拽释放事件
void Soldier::dropEvent(QGraphicsSceneDragDropEvent* event) {
   //判断拖拽物体信息
    if (event->mimeData()->hasText()) {
        dragOver = false;
        QString s = event->mimeData()->text();
        //创建近战单位
        if (game->buildSoldier(s, this)) {
            isOccupied = true;
            name = s;
            image = ":/Mainwindow/game_image/" + name + ".png";
            attackRadius = SOLDIERRANGE[s];
            attackAbility = SOLDIERATK[s];
            attackType = SOLDIERATKTYPE[s];
            healthPoint.first = SOLDIERHEALTH[s];
            healthPoint.second = healthPoint.first;
            blockNum.first = 0;
            blockNum.second = SOLDIERBLOCK[s];
            attackRange->setRect(-attackRadius, -attackRadius, attackRadius * 2, attackRadius * 2);
            healthBar->show();
        }
        update();
    }
}

//重写advance函数
void Soldier::advance(int phase) {
    if (isOccupied && healthPoint.first <= 0) {
        isOccupied = false;
        name = "";
        healthBar->hide();
        update();
        return;
    }
    if (isOccupied && attackAbility!=0) {
        attack();
    }
    update();
}

//重写鼠标点击事件
void Soldier::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (game->isRally == true) {
        game->isRally = false;
        game->setMouse(0);
        game->rallyPoint = this;
        update();
        return;
    }
    if (isOccupied) {
        //展示攻击范围
        attackRange->show();
    }
}

//重写鼠标释放事件
void Soldier::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (isOccupied) {
        //隐藏攻击范围
        attackRange->hide();
    }
}

//重写绘图函数
int Soldier::type() const {
    return Type;
}

//获取阻挡单位数量
bool Soldier::getBlockNum() const {
    return !(blockNum.first == blockNum.second);
}

//增加阻挡单位
void Soldier::addBlock(int i) {
    blockNum.first+=i;
}

//判断单位是否为空
bool Soldier::isEmpty() const {
    return !isOccupied;
}

//攻击函数
void Soldier::attack() {
    //判断攻击单位是否已经死亡
    if (attackTarget && attackTarget->isDead()) {
        attackTarget = NULL;
        isAttacking = false;
    }
    //判断攻击时间是否仍在cd
    if (attackTarget) {
        if (name == "wizzard") {
            QList<QGraphicsItem*> colliding_items = attackRange->collidingItems();
            if (!colliding_items.contains(attackTarget)) {
                attackTarget = NULL;
                isAttacking = false;
                goto next;
            }
        }
        if (frame == 8) {
            //攻击目标
            attackTarget->changeLife(-attackAbility);
            frame = 0;
        }
        else {
            ++frame;
        }
        return;
    }
    next:
    QList<QGraphicsItem*> colliding_items = attackRange->collidingItems();
    for (QGraphicsItem* item : colliding_items) {
        if (item->type() == Enemy::Type &&
            !qgraphicsitem_cast<Enemy*>(item)->isDead() &&
            (!qgraphicsitem_cast<Enemy*>(item)->flight() || attackType == 2)) {
            attackTarget = qgraphicsitem_cast<Enemy*>(item);
        }
    }
    if (attackTarget) {
        isAttacking = true;
    }
}