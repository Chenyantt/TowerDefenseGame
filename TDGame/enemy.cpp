#include "enemy.h"

#include <qpixmap.h>
#include <qpainter.h>
#include <qmovie.h>
#include <qmath.h>

#include "game.h"

Enemy::Enemy(int type, std::vector<std::pair<double, double>> path, Game* game)
	:name(type),path(path),game(game),frame(0),attackTarget(NULL) {
	//根据类型创建敌人单位
	switch (name)
	{
	case 1:
		warlike = false;
		isFlight = true;
		isDistant = false;
		moveSpeed = 10;
		buff = 0;
		attackAbility = 10;
		power = 1;
		healthPoint.first = 150;
		healthPoint.second = 150;
		image = ":/Mainwindow/game_image/monster2/Boss";
		attackRadius = 25;
		break;
	case 2:
		warlike = false;
		isFlight = false;
		isDistant = false;
		moveSpeed = 10;
		buff = 0;
		attackAbility = 10;
		power = 1;
		healthPoint.first = 150;
		healthPoint.second = 150;
		image = ":/Mainwindow/game_image/monster1/Boss";
		attackRadius = 25;
		break;
	case 3:
		warlike = true;
		isFlight = true;
		isDistant = false;
		moveSpeed = 8;
		buff = 0;
		attackAbility = 20;
		power = 3;
		healthPoint.first = 225;
		healthPoint.second = 225;
		image = ":/Mainwindow/game_image/monster3/Boss";
		attackRadius = 35;
		break;
	case 4:
		warlike = false;
		isFlight = false;
		isDistant = true;
		moveSpeed = 10;
		buff = 0;
		attackAbility = 10;
		power = 1;
		healthPoint.first = 80;
		healthPoint.second = 80;
		image = ":/Mainwindow/game_image/monster4/Boss";
		attackRadius = 100;
		break;
	case 5:
		warlike = true;
		isFlight = true;
		isDistant = false;
		moveSpeed = 10;
		buff = 0;
		attackAbility = 15;
		power = 2;
		healthPoint.first = 175;
		healthPoint.second = 175;
		image = ":/Mainwindow/game_image/monster5/Boss";
		attackRadius = 35;
		break;
	case 6:
		warlike = true;
		isFlight = false;
		isDistant = true;
		moveSpeed = 8;
		buff = 0;
		attackAbility = 10;
		power = 3;
		healthPoint.first = 200;
		healthPoint.second = 200;
		image = ":/Mainwindow/game_image/monster6/Boss";
		attackRadius = 25;
		break;
	}
	//设置初始坐标
	setPos(path[0].first, path[0].second);
	destination.setX(path[1].first);
	destination.setY(path[1].second);
	pathStep = 1;
	//设置血条及攻击范围
	QBrush brush(QColor(255, 48, 48));
	healthBar->setBrush(brush);
	attackRange->setRect(-attackRadius, -attackRadius, attackRadius * 2, attackRadius * 2);
	board = new QGraphicsPixmapItem(QPixmap(":/Mainwindow/game_image/board.png"));
	text = new QGraphicsSimpleTextItem;
	board->hide();
	text->hide();
}

//重写碰撞检测函数
QRectF Enemy::boundingRect() const {
	return QRectF(-22, -22, 44, 44);
}

//重写绘图事件
void Enemy::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
	QWidget* widget) {
	Character::paint(painter, option, widget);
	static int i = 0;
	if (i == 12) i = 0;
	QImage picture(image + QString::number(i+(isAttacking?11:0)) + ".png");
	if (x() >= destination.x() && !isAttacking || isAttacking && !attackTarget->isDead()
		&& attackTarget->x()< x()) {
		picture=picture.mirrored(true,false);
	}
	painter->drawPixmap(-54, -39, 108, 78, QPixmap::fromImage(picture));
	++i;
	
}

//重写advance函数
void Enemy::advance(int phase) {
	if (!phase) {
	}
	else {
		if (healthPoint.first <= 0) {
			if (attackTarget && attackTarget->type() == Soldier::Type) {
				qgraphicsitem_cast<Soldier*>(attackTarget)->addBlock(-1);
			}
			game->menu->changeMoney(power * 20);
			delete board;
			delete text;
			delete this;
			return;
		}
		if (!attack()) {
			//计算前进距离及角度
			qreal theta = 0;
			QLineF l(pos(), destination);
			theta = -l.angle();

			if (l.length() < moveSpeed / 2) {
				if (pathStep < path.size() - 1) {
					++pathStep;
					destination.setX(path[pathStep].first);
					destination.setY(path[pathStep].second);
					theta = -QLineF(pos(), destination).angle();
				}
				else {
					game->changeLife(-power);
					delete this;
					return;
				}
			}
			qreal dy = moveSpeed / 2 * qSin(qDegreesToRadians(theta));
			qreal dx = moveSpeed / 2 * qCos(qDegreesToRadians(theta));
			moveBy(dx, dy);
		}
		update();
	}
}

//重写类型函数
int Enemy::type() const { 
	return Type; 
}

//判断是否为飞行单位
bool Enemy::flight() const {
	return isFlight;
}

//攻击函数
bool Enemy::attack() {
	if (attackTarget && attackTarget->isDead()) {
		attackTarget = NULL;
		isAttacking = false;
	}
	if (attackTarget) {
		if (frame == 8) {
			attackTarget->changeLife(-attackAbility);
			frame = 0;
		}
		else {
			++frame;
		}
		return true;
	}
	//碰撞检测
	QList<QGraphicsItem*> colliding_items = attackRange->collidingItems();
	for (QGraphicsItem* item : colliding_items) {
		if (item->type() == Soldier::Type &&
			!qgraphicsitem_cast<Soldier*>(item)->isDead() &&
			!qgraphicsitem_cast<Soldier*>(item)->isEmpty() &&
			(warlike || !isFlight && qgraphicsitem_cast<Soldier*>(item)->getBlockNum())) {
			attackTarget = qgraphicsitem_cast<Soldier*>(item);
		}
	}
	//攻击判定
	if (attackTarget) {
		if (name != 4) {
			qgraphicsitem_cast<Soldier*>(attackTarget)->addBlock(1);
		}
		isAttacking = true;
		return true;
	}
	attackTarget = NULL;
	return false;
}

//重写鼠标点击事件
void Enemy::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	scene()->addItem(board);
	scene()->addItem(text);
	board->setPos(0, 0);
	switch (name)
	{
	case 1:
		text->setText("怪物属性：\n飞行单位 避战 生命较低 攻击较低");
		break;
	case 2:
		text->setText("怪物属性：\n地面单位 近战 生命适中 攻击适中");
		break;
	case 3:
		text->setText("怪物属性：\n飞行单位 好战 生命较高 攻击较高");
		break;
	case 4:
		text->setText("怪物属性：\n地面单位 远程 生命很低 攻击较高");
		break;
	case 5:
		text->setText("怪物属性：\n飞行单位 好战 生命较高 攻击较高");
		break;
	case 6:
		text->setText("怪物属性：\n地面单位 近战 生命较高 攻击较高");
		break;
	default:
		break;
	}
	text->setPos(20, 20);
	QFont font;
	font.setPointSizeF(12);
	font.setBold(true);
	text->setBrush(QColor(255, 255, 255));
	text->setFont(font);
	text->show();
	board->show();
	update();
}

//重写鼠标释放事件
void Enemy::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	text->hide();
	board->hide();
	update();
}