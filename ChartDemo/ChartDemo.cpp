#include "ChartDemo.h"
#include "ConfigLoader.h"
#include "ChartManger.h"


ChartDemo::ChartDemo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	init();
}

ChartDemo::~ChartDemo()
{}

void ChartDemo::init()
{
	ConfigLoader *configLoader = new ConfigLoader(ui.tableWidget, this);
	configLoader->loadConfig("path/to/your/config.txt");

	ChartManager *chartmanger = new ChartManager(this, ui.Chartwidget);
	chartmanger->start();
	QVBoxLayout *layout = new QVBoxLayout(ui.Chartwidget); // 创建一个新的垂直布局
	layout->addWidget(chartmanger->getChartView()); // 将chartView添加到布局中
	ui.Chartwidget->setLayout(layout); // 将布局设置给ui.Chartwidget
}



