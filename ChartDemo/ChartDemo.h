#pragma once

#include <QWidget>
#include "ui_ChartDemo.h"
#include "ChartManger.h"
#include "ConfigLoader.h"

class ChartDemo : public QWidget
{
    Q_OBJECT

public:
    ChartDemo(QWidget *parent = nullptr);
    ~ChartDemo();



	void init();


public slots:
	void handleIntervalPBClicked();
	void toggleTableVisibility();


private:
    Ui::lpTendencyClass ui;
	ChartManager *chartManager;
	ConfigLoader *configLoader;


};
