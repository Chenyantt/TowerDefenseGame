#include "menu.h"

#include "config.h"
#include "game.h"
#include "data.h"

class Game;

Menu::Menu(int i,Game* parent):parent(parent) {
	this->setParent(parent);
    //���ü�����λ����ѡ��ͼ��
    store[0].set("archer", ":/Mainwindow/game_image/archer.png", 70,this);
    store[1].set("icy", ":/Mainwindow/game_image/icy.png", 70,this);
    store[2].set("mage", ":/Mainwindow/game_image/mage.png", 100,this);
    store[3].set("canon", ":/Mainwindow/game_image/canon.png", 120,this);
    store[4].set("warrior", ":/Mainwindow/game_image/warrior.png", 25, this);
    store[5].set("wall", ":/Mainwindow/game_image/wall.png", 20, this);
    store[6].set("wizzard", ":/Mainwindow/game_image/wizzard.png", 30, this);
    for (int i = 0; i < 7; ++i) {
        store[i].setParentItem(this);
        store[i].setPos(30, 150 + 60 * i);
    }
    //���ò���������λͼ��
    spade.setParentItem(this);
    spade.setParent(this);
    spade.setPos(40, 580);
    //���ü�����λ���ϵ�ͼ��
    rally.setParentItem(this);
    rally.setParent(this);
    rally.setPos(120, 580);
    //�����ļ���Ϣ
	menuConfig(this, i);
}

QRectF Menu::boundingRect() const {
    return QRectF(0, 0, 255, 670);
}

//��д��ͼ�¼�
void Menu::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
    QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(30, 70, 25, 25, QPixmap(":/Mainwindow/game_image/life.png"));
    painter->drawPixmap(120, 70, 25, 25, QPixmap(":/Mainwindow/game_image/money.png"));
    painter->drawPixmap(30, 110, 25, 25, QPixmap(":/Mainwindow/game_image/bout.png"));
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(QRectF(70, 70, 100, 50), QString::number(life));
    painter->drawText(QRectF(160, 70, 100, 50), QString::number(money));
    painter->drawText(QRectF(70, 110, 100, 50), QString::number(boutCount.first)+"/"
        + QString::number(boutCount.second));
    
}

//��ȡ��Ϸ��ǰ��Ǯ
int Menu::getMoney() {
    return money;
}

//�ı���Ϸ��ǰ��Ǯ
void Menu::changeMoney(int n) {
    money += n;
    update();
}