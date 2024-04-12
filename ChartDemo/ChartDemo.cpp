#include "ChartDemo.h"
#pragma execution_character_set("utf-8")

ChartDemo::ChartDemo(QWidget *parent)
    : QMainWindow(parent)
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


	// 初始化按钮并设置文本
	toggleTableButton = new QPushButton("趋势指标勾选隐藏", this);
	updateToggleButtonPosition();

	// 连接按钮的clicked信号到toggleTableVisibility槽
	connect(toggleTableButton, &QPushButton::clicked, this, &ChartDemo::toggleTableVisibility);

	connect(ui.Interval_PB, &QPushButton::clicked, this, &ChartDemo::handleIntervalPBClicked);
}


void ChartDemo::updateToggleButtonPosition() {
	int buttonWidth = 120;
	int buttonHeight = 30;

	QSize mainWindowSize = this->size();
	int x = mainWindowSize.width() - buttonWidth; 
	int y = mainWindowSize.height() - buttonHeight; 

	toggleTableButton->setGeometry(x, y, buttonWidth, buttonHeight);
}


void ChartDemo::toggleTableVisibility() {
	ui.tableWidget->setVisible(!ui.tableWidget->isVisible());
	toggleTableButton->setText(ui.tableWidget->isVisible() ? "趋势指标勾选隐藏" : "趋势指标勾选显示");
}

void ChartDemo::handleIntervalPBClicked() {
	if (chartManager) {
		chartManager->onIntervalPBClicked();//用于显示间隔设置对话框
	}
}

void ChartDemo::resizeEvent(QResizeEvent* event) {
	QMainWindow::resizeEvent(event);
	updateToggleButtonPosition();
}



