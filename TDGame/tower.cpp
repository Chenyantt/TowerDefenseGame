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
    //设置血条画刷
    QBrush brush(QColor(0, 238, 0));
    healthBar->setBrush(brush);
    healthPoint.first = 100;
    healthPoint.second = 100;
    bulletNum = 0;
}

//设置初始化坐标
void Tower::setPos(QPointF point) {
    this->point = point;
    QGraphicsItem::setPos(point);
}

//配置游戏信息
void Tower::setGame(Game* game) {
    this->game = game;
}

//重写碰撞检测函数
QRectF Tower::boundingRect() const {
    return QRectF(-40,-37.5, 80, 75);
}

//重写绘图事件
void Tower::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
    QWidget* widget) {
    //判断是否播放建造动画
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
    //判断该单元格上是否有远程单位
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
    //判断该单元格上是否有远程单位
    if (!isOccupied) {
        image = ":/Mainwindow/game_image/base1.png";
    }
    else {
        image = ":/Mainwindow/game_image/" + name + ".png";
    }
    update();
}

//重写拖拽进入事件
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

//重写拖离事件
void Tower::dragLeaveEvent(QGraphicsSceneDragDropEvent* event) {
    Q_UNUSED(event);
    dragOver = false;
    update();
}

//重写拖拽释放事件
void Tower::dropEvent(QGraphicsSceneDragDropEvent* event) {
    //判断拖拽信息是否合法
    if (event->mimeData()->hasText()) {
        dragOver = false;
        QString s = event->mimeData()->text();
        //建造远程单位
        if (game->buildTower(s, this)) {
            build->setFileName(":/Mainwindow/game_image/build.gif");
            isOccupied = true;
            name = s;
            image = ":/Mainwindow/game_image/" + name + ".png";
            //配置远程单位信息
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

//重写计时器事件
void Tower::timerEvent(QTimerEvent*) {
    update();
}

//重写advance函数
void Tower::advance(int phase) {
    if (!phase) {
    }
    else {
        //判断单元格上是否有远程单位
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
                //判断攻击是否在cd
                if (cd == 0) {
                    srand(time(NULL));
                    //创建己方近战单位
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

//重写鼠标点击事件
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

//重写鼠标释放事件
void Tower::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event);
    if (isOccupied) {
        attackRange->hide();
    }
    return;
}

//攻击函数
bool Tower::attack() {
    QList<QGraphicsItem*> colliding_items = attackRange->collidingItems();
    Enemy* attackTarget = NULL;
    //碰撞检测
    for (QGraphicsItem* item : colliding_items) {
        if (item->type() == Enemy::Type &&
            ! qgraphicsitem_cast<Enemy*>(item)->isDead() && 
            (attackType==2 || attackType==1 && !qgraphicsitem_cast<Enemy*>(item)->flight())) {
            attackTarget = qgraphicsitem_cast<Enemy*>(item);
        }
    }
    //生成攻击子弹
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