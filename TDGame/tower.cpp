#include "tower.h"

#include <qpainter.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qdrag.h>
#include <qmimedata.h>
#include <qrect.h>
#include <qtimer.h>
#include <qlabel>
#include <qmath.h>

#include "game.h"
#include "data.h"


Tower::Tower() :isOccupied(false), name(""),dragOver(false),cd(0) {
    setAcceptHoverEvents(true);
    setAcceptDrops(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    image = ":/Mainwindow/game_image/base1.png";
    build = new QMovie(this);
    //����Ѫ����ˢ
    QBrush brush(QColor(0, 238, 0));
    healthBar->setBrush(brush);
    healthPoint.first = 100;
    healthPoint.second = 100;
    bulletNum = 0;
}

//���ó�ʼ������
void Tower::setPos(QPointF point) {
    this->point = point;
    QGraphicsItem::setPos(point);
}

//������Ϸ��Ϣ
void Tower::setGame(Game* game) {
    this->game = game;
}

//��д��ײ��⺯��
QRectF Tower::boundingRect() const {
    return QRectF(-40,-37.5, 80, 75);
}

//��д��ͼ�¼�
void Tower::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
    QWidget* widget) {
    //�ж��Ƿ񲥷Ž��춯��
    if (build->isValid()) {
            build->jumpToNextFrame();
            if (build->currentFrameNumber() == build->frameCount() - 1) {
                QPixmap img(image);
                img = img.scaled(80, 75);
                painter->drawPixmap(-40,-37.5, img);
                build->setFileName("");
                killTimer(buildTimer);
            }
            else {
                painter->drawImage(QRectF(-40, -47.5, 80, 20), build->currentImage());
                QPixmap img(":/Mainwindow/game_image/" + name + "build.png");
                img = img.scaled(60, 55);
                painter->drawPixmap(-25, -25, img);
            }
            return;
        }
        if (isOccupied == false) {
            QPixmap img(image);
            img = img.scaled(80, 75);
            painter->drawPixmap(-40,-37.5, img);
        }
        else {
            Character::paint(painter, option, widget);
            QPixmap img(image);
            img = img.scaled(80, 75);
            painter->drawPixmap(-40,-37.5, img);
        }
}

void Tower::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    //�жϸõ�Ԫ�����Ƿ���Զ�̵�λ
    if (!isOccupied) {
        image = ":/Mainwindow/game_image/base2.png";
    }
    else {
        image = ":/Mainwindow/game_image/" + name + "1.png";
    } 
    update();
}

void Tower::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    //�жϸõ�Ԫ�����Ƿ���Զ�̵�λ
    if (!isOccupied) {
        image = ":/Mainwindow/game_image/base1.png";
    }
    else {
        image = ":/Mainwindow/game_image/" + name + ".png";
    }
    update();
}

//��д��ק�����¼�
void Tower::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {
    if (event->mimeData()->hasText()&& TOWERLIST.count(event->mimeData()->text()) && !isOccupied) {
        event->setAccepted(true);
        dragOver = true;
        update();
    }
    else {
        event->setAccepted(false);
    }
}

//��д�����¼�
void Tower::dragLeaveEvent(QGraphicsSceneDragDropEvent* event) {
    Q_UNUSED(event);
    dragOver = false;
    update();
}

//��д��ק�ͷ��¼�
void Tower::dropEvent(QGraphicsSceneDragDropEvent* event) {
    //�ж���ק��Ϣ�Ƿ�Ϸ�
    if (event->mimeData()->hasText()) {
        dragOver = false;
        QString s = event->mimeData()->text();
        //����Զ�̵�λ
        if (game->buildTower(s, this)) {
            build->setFileName(":/Mainwindow/game_image/build.gif");
            isOccupied = true;
            name = s;
            image = ":/Mainwindow/game_image/" + name + ".png";
            //����Զ�̵�λ��Ϣ
            attackRadius = TOWERRANGE[s];
            attackAbility = TOWERATK[s];
            attackType = TOWERATKTYPE[s];
            attackRange->setRect(-attackRadius, -attackRadius, attackRadius * 2, attackRadius * 2);
            buildTimer=startTimer(20);
            healthBar->show();
        } 
        update();
    }
}

//��д��ʱ���¼�
void Tower::timerEvent(QTimerEvent*) {
    update();
}

//��дadvance����
void Tower::advance(int phase) {
    if (!phase) {
    }
    else {
        //�жϵ�Ԫ�����Ƿ���Զ�̵�λ
        if (isOccupied) {
            if (healthPoint.first <= 0) {
                isOccupied = false;
                name = "";
                healthBar->hide();
                update();
                return;
            }
            if (cd == 0 && name!="icy") {
                if (attack()) {
                    cd = 15;
                }
            }
            else if (name == "icy") {
                //�жϹ����Ƿ���cd
                if (cd == 0) {
                    srand(time(NULL));
                    //����������ս��λ
                    if (game->rallyPoint != NULL && game->rallyPoint->isOccupied==false) {
                        game->rallyPoint->isOccupied = true;
                        QString s = "warrior";
                        game->rallyPoint->name = "warrior";
                        game->rallyPoint->image = ":/Mainwindow/game_image/warrior.png";
                        game->rallyPoint->attackRadius = SOLDIERRANGE[s];
                        game->rallyPoint->attackAbility = SOLDIERATK[s];
                        game->rallyPoint->attackType = SOLDIERATKTYPE[s];
                        game->rallyPoint->healthPoint.first = SOLDIERHEALTH[s];
                        game->rallyPoint->healthPoint.second = game->rallyPoint->healthPoint.first;
                        game->rallyPoint->blockNum.first = 0;
                        game->rallyPoint->blockNum.second = SOLDIERBLOCK[s];
                        game->rallyPoint->attackRange->setRect(-game->rallyPoint->attackRadius, -game->rallyPoint->attackRadius, game->rallyPoint->attackRadius * 2, game->rallyPoint->attackRadius * 2);
                        game->rallyPoint->healthBar->show();
                        cd = 250;
                    }
                    else {
                        int i;
                        for (i = rand() % game->soldierNum; !game->soldierList[i].isEmpty(); i = rand() % game->soldierNum);
                        game->soldierList[i].isOccupied = true;
                        QString s = "warrior";
                        game->soldierList[i].name = "warrior";
                        game->soldierList[i].image = ":/Mainwindow/game_image/warrior.png";
                        game->soldierList[i].attackRadius = SOLDIERRANGE[s];
                        game->soldierList[i].attackAbility = SOLDIERATK[s];
                        game->soldierList[i].attackType = SOLDIERATKTYPE[s];
                        game->soldierList[i].healthPoint.first = SOLDIERHEALTH[s];
                        game->soldierList[i].healthPoint.second = game->soldierList[i].healthPoint.first;
                        game->soldierList[i].blockNum.first = 0;
                        game->soldierList[i].blockNum.second = SOLDIERBLOCK[s];
                        game->soldierList[i].attackRange->setRect(-game->soldierList[i].attackRadius, -game->soldierList[i].attackRadius, game->soldierList[i].attackRadius * 2, game->soldierList[i].attackRadius * 2);
                        game->soldierList[i].healthBar->show();
                        cd = 250;
                    }  
                }
                else {
                    --cd;
                }
            }
            else{
                --cd;
            }
        }
        update();
    }
}

//��д������¼�
void Tower::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (game->isRemove == true && name!="") {
        isOccupied = false;
        game->isRemove = false;
        game->setMouse(0);
        update();
        game->menu->changeMoney(TOWERLIST[name] / 2);
        name = "";
        healthBar->hide();
    }
    else if(isOccupied){
        attackRange->show();
        return;
    }
}

//��д����ͷ��¼�
void Tower::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event);
    if (isOccupied) {
        attackRange->hide();
    }
    return;
}

//��������
bool Tower::attack() {
    QList<QGraphicsItem*> colliding_items = attackRange->collidingItems();
    Enemy* attackTarget = NULL;
    //��ײ���
    for (QGraphicsItem* item : colliding_items) {
        if (item->type() == Enemy::Type &&
            ! qgraphicsitem_cast<Enemy*>(item)->isDead() && 
            (attackType==2 || attackType==1 && !qgraphicsitem_cast<Enemy*>(item)->flight())) {
            attackTarget = qgraphicsitem_cast<Enemy*>(item);
        }
    }
    //���ɹ����ӵ�
    if (attackTarget) {
        bullet[bulletNum].setBullet(name, attackTarget,this);
        QLineF ln(QPointF(x(), y()), attackTarget->pos());
        qreal angle = -1 * ln.angle();
        qreal dy = 15 * qSin(qDegreesToRadians(angle));
        qreal dx = 15 * qCos(qDegreesToRadians(angle));
        bullet[bulletNum].setPos(x() + dx, y() + dy);
        scene()->addItem(&bullet[bulletNum]);
        bullet[bulletNum].setRotation(angle);
        ++bulletNum;
        return true;
    }
    return false;
}

int Tower::type() const {
    return Type;
}

bool Tower::isEmpty() const {
    return !isOccupied;
}