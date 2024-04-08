﻿#include "ChartDemo.h"

#include "ChartManger.h"


ChartDemo::ChartDemo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	init();


	connect(ui.Interval_PB, &QPushButton::clicked, this, &ChartDemo::handleIntervalPBClicked);
}

ChartDemo::~ChartDemo()
{
	configLoader->saveConfig("F:/QwtChart_cpx/x64/Release/Event.json");
	delete chartManager;
}

void ChartDemo::init()
{
	configLoader = new ConfigLoader(ui.tableWidget, this);
	configLoader->loadConfig("F:/QwtChart_cpx/x64/Release/Event.json");

	chartManager = new ChartManager(this, ui.Chartwidget);
	chartManager->start();
}

void ChartDemo::handleIntervalPBClicked() {
	if (chartManager) {
		chartManager->onIntervalPBClicked();//用于显示间隔设置对话框
	}
}

