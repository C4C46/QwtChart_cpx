#include "ChartManger.h"
#include <QTime>

#pragma execution_character_set("utf-8")

ChartManager::ChartManager(QObject *parent, QWidget *parentWidget) : QObject(parent) {
	plot = new QwtPlot(parentWidget);
	plot->setTitle("实时趋势图");
	plot->setCanvasBackground(Qt::white);

	// 设置X轴和Y轴的标题
	plot->setAxisTitle(QwtPlot::xBottom, "X轴");
	plot->setAxisTitle(QwtPlot::yLeft, "Y轴");

	// 设置X轴和Y轴的范围
	plot->setAxisScale(QwtPlot::xBottom, 0, 1400);
	plot->setAxisScale(QwtPlot::yLeft, 0, 800);

	// 创建并配置网格
	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->attach(plot); // 将网格附加到图表
	grid->setVisible(false); // 隐藏网格线

	// 创建曲线
	curve = new QwtPlotCurve();
	curve->setPen(Qt::blue, 2); // 设置曲线颜色和宽度
	curve->attach(plot); // 将曲线附加到图表

	// 如果没有提供parentWidget，则创建新窗口
	if (!parentWidget) {
		window = new QMainWindow();
		window->setCentralWidget(plot);
		window->resize(1200, 900);
	}

	updaterThread = new ChartUpdaterThread(this);
	connect(updaterThread, &ChartUpdaterThread::updateChart, this, &ChartManager::onChartUpdate);
}



//ChartManager::ChartManager(QObject *parent, QWidget *parentWidget) : QObject(parent) {
//	series = new QLineSeries();
//	QObject::connect(series, &QLineSeries::hovered, [](const QPointF &point, bool state) {
//		Q_UNUSED(state)
//			QToolTip::showText(QCursor::pos(), QString("X: %1\nY: %2").arg(point.x()).arg(point.y()));
//	});
//
//	chart = new QChart();
//	chart->legend()->hide();
//	chart->addSeries(series);
//	chart->setTitle("实时趋势图");
//	chart->createDefaultAxes();
//
//	QValueAxis *axisX = new QValueAxis;
//	axisX->setRange(0, 1400);
//	axisX->setTickCount(8); //设置X轴刻度数量
//	axisX->setGridLineVisible(false); // 隐藏X轴网格线
//	QValueAxis *axisY = new QValueAxis;
//	axisY->setRange(0, 800);
//	axisY->setTickCount(9); // 设置y轴刻度数量
//	chart->setAxisX(axisX, series);
//	chart->setAxisY(axisY, series);
//
//	chartView = new CustomChartView(chart, parentWidget); // 使用parentWidget作为父对象
//	chartView->setRenderHint(QPainter::Antialiasing);
//
//	if (!parentWidget) { // 如果没有提供parentWidget，则创建新窗口
//		window = new QMainWindow();
//		window->setCentralWidget(chartView);
//		window->resize(1200, 900);
//	}
//
//	updaterThread = new ChartUpdaterThread(this);
//	connect(updaterThread, &ChartUpdaterThread::updateChart, this, &ChartManager::onChartUpdate);
//}

ChartManager::~ChartManager() {
	if (updaterThread) {
		updaterThread->stopRunning();
		updaterThread->wait(); 
		delete updaterThread; 
		updaterThread = nullptr;
	}

}

void ChartManager::start() {
	if (updaterThread && !updaterThread->isRunning()) {
		updaterThread->start();
	}
}

QMainWindow* ChartManager::getWindow() {
	return window;
}

void ChartManager::onChartUpdate(int x, qreal y) {
	// 更新数据
	QVector<double> xData, yData;
	xData << x;
	yData << y;
	curve->setSamples(xData, yData); // 更新曲线的数据点

	plot->replot(); // 重绘图表
}

//
//void ChartManager::onChartUpdate(int x, qreal y) {
//	series->append(x, y);
//	QValueAxis *axisX = static_cast<QValueAxis*>(chart->axes(Qt::Horizontal).first());
//	int maxRange = axisX->max(); // 获取当前x轴的最大值
//
//	if (x > maxRange) {
//		axisX->setRange(maxRange, maxRange + 200); // 将x轴范围向右移动200
//	}
//}
