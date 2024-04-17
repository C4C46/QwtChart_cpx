#include "ChartDemo.h"
#pragma execution_character_set("utf-8")

ChartDemo::ChartDemo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	init();
	
}

ChartDemo::~ChartDemo()
{
	configLoader->saveConfig("Config/Event.json");
	delete chartManager;
	delete configLoader;
}

void ChartDemo::init()
{
	configLoader = new ConfigLoader(ui.tableWidget, this);
	configLoader->loadConfig("Config/Event.json");


	QStringList curveNames = configLoader->getCurveNames(); // 获取曲线名称
	chartManager = new ChartManager(this, ui.Chartwidget, curveNames);
	chartManager->start();
	connect(configLoader, &ConfigLoader::curveDisplayChanged, chartManager, &ChartManager::onCurveDisplayChanged);


	ui.Toggle_PB->setText("趋势指标勾选隐藏");
	// 连接按钮的clicked信号到toggleTableVisibility槽
	connect(ui.Toggle_PB, &QPushButton::clicked, this, &ChartDemo::toggleTableVisibility);

	connect(ui.Interval_PB, &QPushButton::clicked, this, &ChartDemo::handleIntervalPBClicked);
}



void ChartDemo::toggleTableVisibility() {
	ui.tableWidget->setVisible(!ui.tableWidget->isVisible());
	ui.Toggle_PB->setText(ui.tableWidget->isVisible() ? "趋势指标勾选隐藏" : "趋势指标勾选显示");
}

void ChartDemo::handleIntervalPBClicked() {
	if (chartManager) {
		chartManager->onIntervalPBClicked();//用于显示间隔设置对话框
	}
}




