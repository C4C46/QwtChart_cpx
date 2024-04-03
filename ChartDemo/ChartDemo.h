#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChartDemo.h"

class ChartDemo : public QMainWindow
{
    Q_OBJECT

public:
    ChartDemo(QWidget *parent = nullptr);
    ~ChartDemo();

	void init();

private:
    Ui::ChartDemoClass ui;
};
