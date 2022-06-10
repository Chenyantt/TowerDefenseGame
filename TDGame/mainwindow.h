#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class Mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    Mainwindow(QWidget *parent = Q_NULLPTR);
    
    void paintEvent(QPaintEvent* e);
private:
    Ui::MainwindowClass ui;
};
