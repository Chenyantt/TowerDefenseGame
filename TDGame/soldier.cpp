#include "soldier.h"

#include <qbrush.h>
#include <qgraphicssceneevent.h>
#include <qmimedata.h>

#include "game.h"
#include "data.h"

Soldier::Soldier() :isOccupied(false), name(""), dragOver(false),attackTarget(NULL),frame(0) {
    //����������������ק����ͣ
    setAcceptHoverEvents(true);
    setAcceptDrops(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    image = "";
    //����Ѫ����ˢ
    QBrush brush(QColor(0, 238, 0));
    healthBar->setBrush(brush);
}

//���ó�ʼ��λ��
void Soldier::setPosition(QPointF point) {
    this->point = point;
    setPos(point);
}

//������Ϸ������Ϣ
void Soldier::setGame(Game* game) {
    this->game = game;
}

//������ײ��⺯��
QRectF Soldier::boundingRect() const {
    return QRectF(-22, -22, 44, 44);
}

//��д��ͼ�¼�
void Soldier::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
	QWidget* widget) {
    if(isOccupied) {
        Character::paint(painter, option, widget);
        //�ж��Ƿ񲥷Ź�������
        if (!isAttacking) {
            //�жϹ������򣬾��������Ƿ�ת
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
                //�жϹ������򣬾��������Ƿ�ת
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

//��д�����¼�
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

//��д�����¼�
void Soldier::dragLeaveEvent(QGraphicsSceneDragDropEvent* event) {
    Q_UNUSED(event);
    dragOver = false;
    update();
}

//��д��ק�ͷ��¼�
void Soldier::dropEvent(QGraphicsSceneDragDropEvent* event) {
   //�ж���ק������Ϣ
    if (event->mimeData()->hasText()) {
        dragOver = false;
        QString s = event->mimeData()->text();
        //������ս��λ
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

//��дadvance����
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

//��д������¼�
void Soldier::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (game->isRally == true) {
        game->isRally = false;
        game->setMouse(0);
        game->rallyPoint = this;
        update();
        return;
    }
    if (isOccupied) {
        //չʾ������Χ
        attackRange->show();
    }
}

//��д����ͷ��¼�
void Soldier::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (isOccupied) {
        //���ع�����Χ
        attackRange->hide();
    }
}

//��д��ͼ����
int Soldier::type() const {
    return Type;
}

//��ȡ�赲��λ����
bool Soldier::getBlockNum() const {
    return !(blockNum.first == blockNum.second);
}

//�����赲��λ
void Soldier::addBlock(int i) {
    blockNum.first+=i;
}

//�жϵ�λ�Ƿ�Ϊ��
bool Soldier::isEmpty() const {
    return !isOccupied;
}

//��������
void Soldier::attack() {
    //�жϹ�����λ�Ƿ��Ѿ�����
    if (attackTarget && attackTarget->isDead()) {
        attackTarget = NULL;
        isAttacking = false;
    }
    //�жϹ���ʱ���Ƿ�����cd
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
            //����Ŀ��
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