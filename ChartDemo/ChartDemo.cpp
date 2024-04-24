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



	configLoader = new ConfigLoader(ui.treeWidget, this);
	configLoader->loadConfig("Config/Event.json");

	QStringList curveNames = configLoader->getCurveNames(); // 获取勾选的曲线名称
	QStringList allCurveNames = configLoader->getAllCurveNames(); // 获取所有曲线名称

		// 创建一个线程来处理所有数据
	chartUpdaterThread = new ChartUpdaterThread(this, allCurveNames);

	// 创建图表管理器，只处理勾选的曲线
	chartManager = new ChartManager(this, ui.Chartwidget, curveNames, 
		configLoader, chartUpdaterThread);
	chartManager->start();

	// 创建数据显示区域
	dataScope = new DataScope(ui.tableWidget, this);
	dataScope->setColumnNames(allCurveNames);

	ui.Toggle_PB->setText("趋势指标勾选隐藏");

	connect(configLoader, &ConfigLoader::curveDisplayChanged, chartManager, &ChartManager::onCurveDisplayChanged);
//	connect(chartUpdaterThread, &ChartUpdaterThread::updateChart, chartManager, &ChartManager::onChartUpdate);
	connect(chartUpdaterThread, &ChartUpdaterThread::updateChart, this, &ChartDemo::updateData);
	connect(ui.Toggle_PB, &QPushButton::clicked, this, &ChartDemo::toggleTableVisibility);
	connect(ui.Interval_PB, &QPushButton::clicked, this, &ChartDemo::handleIntervalPBClicked);
}


void ChartDemo::toggleTableVisibility() {
	ui.treeWidget->setVisible(!ui.treeWidget->isVisible());
	ui.Toggle_PB->setText(ui.treeWidget->isVisible() ? "趋势指标勾选隐藏" : "趋势指标勾选显示");
}

void ChartDemo::handleIntervalPBClicked() {
	if (chartManager) {
		chartManager->onIntervalPBClicked();//用于显示间隔设置对话框
	}
}
void ChartDemo::updateData(const QString &curveName, double x, double y) {
	qDebug() << "Updating data for" << curveName << "with X:" << x << "Y:" << y;
	dataScope->addData(curveName, x, y); // 使用已有的addData函数来添加数据到表格

		// 如果曲线被用户选中，则更新图表
	if (configLoader->getCurveNames().contains(curveName)) {
		chartManager->onChartUpdate(curveName, x, y);
	}
}





