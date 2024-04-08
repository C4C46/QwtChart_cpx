#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChartDemo.h"
#include "ChartManger.h"
#include "ConfigLoader.h"

class ChartDemo : public QMainWindow
{
    Q_OBJECT

public:
    ChartDemo(QWidget *parent = nullptr);
    ~ChartDemo();

	void init();

public slots:
	void handleIntervalPBClicked();

private:
    Ui::ChartDemoClass ui;
	ChartManager *chartManager;
	ConfigLoader *configLoader;
};
