#include "ChartDemo.h"


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
	toggleTableButton = new QPushButton("Hide Table", this);
	updateToggleButtonPosition();

	// 连接按钮的clicked信号到toggleTableVisibility槽
	connect(toggleTableButton, &QPushButton::clicked, this, &ChartDemo::toggleTableVisibility);

	connect(ui.Interval_PB, &QPushButton::clicked, this, &ChartDemo::handleIntervalPBClicked);
}


void ChartDemo::updateToggleButtonPosition() {
	int buttonWidth = 100;
	int buttonHeight = 30;
	// 获取主窗口的大小
	QSize mainWindowSize = this->size();
	// 计算按钮的新位置，使其位于主窗口的右下角
	int x = mainWindowSize.width() - buttonWidth; // 从窗口右边缘向左偏移按钮宽度+10的距离
	int y = mainWindowSize.height() - buttonHeight; // 从窗口底部向上偏移按钮高度+30的距离，30是为了考虑状态栏的高度或窗口边框

	toggleTableButton->setGeometry(x, y, buttonWidth, buttonHeight);
}


void ChartDemo::toggleTableVisibility() {
	ui.tableWidget->setVisible(!ui.tableWidget->isVisible());
	toggleTableButton->setText(ui.tableWidget->isVisible() ? "Hide Table" : "Show Table");
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



