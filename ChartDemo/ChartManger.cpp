#include "ChartManger.h"

#pragma execution_character_set("utf-8")

ChartManager::ChartManager(QObject *parent, QWidget *parentWidget) 
	: QObject(parent), m_widget(parentWidget) 
{
	plot = new QwtPlot(parentWidget);
	plot->setTitle("实时趋势图");
	plot->setCanvasBackground(Qt::white);

	// 设置X轴和Y轴的标题
	plot->setAxisTitle(QwtPlot::xBottom,"");
	plot->setAxisTitle(QwtPlot::yLeft,"");

	//// 设置X轴和Y轴的范围
	//plot->setAxisScale(QwtPlot::xBottom, 0, 1400);
	//plot->setAxisScale(QwtPlot::yLeft, 0, 800);

	// 创建并配置网格
	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->attach(plot); // 将网格附加到图表
	grid->setVisible(false); // 隐藏网格线

	//// 创建曲线
	//curve = new QwtPlotCurve();
	//curve->setPen(Qt::blue, 2); // 设置曲线颜色和宽度
	//curve->attach(plot); // 将曲线附加到图表
	//addCurve("Curve1", Qt::blue);
	//addCurve("Curve2", Qt::red);

		// 添加18条曲线
	for (int i = 1; i <= 18; ++i) {
		QColor color = QColor::fromHsv((i * 20) % 360, 255, 255); // 生成不同的颜色
		addCurve(QString("Curve%1").arg(i), color);
	}


	QVBoxLayout *layout = new QVBoxLayout(m_widget);
	layout->addWidget(plot);
	m_widget->setLayout(layout);

	if (m_widget) {
		m_widget->setLayout(new QVBoxLayout());
		m_widget->layout()->addWidget(plot);
	}

	updaterThread = new ChartUpdaterThread(this);
	//connect(updaterThread, &ChartUpdaterThread::updateChart, this, &ChartManager::onChartUpdate);
	//connect(updaterThread, &ChartUpdaterThread::updateChart, this, [this](int x, qreal y) {
	//	onChartUpdate("Curve1", x, y);
	//});

	connect(updaterThread, &ChartUpdaterThread::updateChart, this, &ChartManager::onChartUpdate);
}



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

QWidget* ChartManager::getWidget() {
	return m_widget;
}

void ChartManager::onChartUpdate(const QString &curveName, int x, qreal y) {
	//xData << x;
	//yData << y;
	//curve->setSamples(xData, yData); // 更新曲线的数据点

	if (!xDataMap.contains(curveName) || !yDataMap.contains(curveName)) {
		return; // 如果曲线名称不存在，则直接返回
	}

	xDataMap[curveName] << x;
	yDataMap[curveName] << y;

	for (auto &curve : curves) {
		if (curve->title().text() == curveName) {
			curve->setSamples(xDataMap[curveName], yDataMap[curveName]); // 更新指定曲线的数据点
			break;
		}
	}
		// 确定当前数据点所在的X轴区间
	int xIntervalIndex = x / xInterval; // 计算当前数据点属于哪个间隔区间
	double xMin = xIntervalIndex * xInterval;
	double xMax = xMin + xInterval;

	// Y轴区间计算
	int yIntervalIndex = y / yInterval; // 计算当前数据点属于哪个间隔区间
	double yMin = yIntervalIndex * yInterval;
	double yMax = yMin + yInterval;

	//// 为了美观，可以在Y轴的最大值和最小值上下各留一点空间
	//yMin = floor(yMin / yInterval) * yInterval;
	//yMax = ceil((yMax + yInterval) / yInterval) * yInterval;

	// 更新X轴和Y轴的范围
	plot->setAxisScale(QwtPlot::xBottom, xMin, xMax);
	plot->setAxisScale(QwtPlot::yLeft, yMin, yMax);

	plot->replot(); // 重绘图表
}

void ChartManager::onIntervalPBClicked() {
	QDialog dialog(m_widget); // 使用当前widget作为父窗口
	QVBoxLayout layout(&dialog);

	QLabel xLabel("设置x轴间隔米数：", &dialog);
	QLineEdit xInput(&dialog);
	xInput.setValidator(new QDoubleValidator(0, 10000, 2, &xInput)); // 限制输入为数字

	QLabel yLabel("设置y轴间隔毫米数：", &dialog);
	QLineEdit yInput(&dialog);
	yInput.setValidator(new QDoubleValidator(0, 10000, 2, &yInput)); // 限制输入为数字

	QPushButton confirmButton("确认", &dialog);
	connect(&confirmButton, &QPushButton::clicked, &dialog, &QDialog::accept);

	layout.addWidget(&xLabel);
	layout.addWidget(&xInput);
	layout.addWidget(&yLabel);
	layout.addWidget(&yInput);
	layout.addWidget(&confirmButton);

	// 显示对话框
	if (dialog.exec() == QDialog::Accepted) {
		xInterval = xInput.text().toDouble();
		yInterval = yInput.text().toDouble();

		// 计算新的X轴和Y轴范围
		double xMin = 0;
		double xMax = xMin + xInterval; // 以xInterval为间隔计算xMax
		double yMin = 0;
		double yMax = yMin + yInterval; // 以yInterval为间隔计算yMax

		// 更新图表的X轴和Y轴范围
		plot->setAxisScale(QwtPlot::xBottom, xMin, xMax);
		plot->setAxisScale(QwtPlot::yLeft, yMin, yMax);

		//// 更新图表的X轴和Y轴间隔
		//plot->setAxisScale(QwtPlot::xBottom, plot->axisScaleDiv(QwtPlot::xBottom).lowerBound(), plot->axisScaleDiv(QwtPlot::xBottom).upperBound(), xInterval);
		//plot->setAxisScale(QwtPlot::yLeft, plot->axisScaleDiv(QwtPlot::yLeft).lowerBound(), plot->axisScaleDiv(QwtPlot::yLeft).upperBound(), yInterval);

		plot->replot(); // 重绘图表以应用新的间隔
	}
}


void ChartManager::addCurve(const QString &curveName, const QColor &color) {
	QwtPlotCurve *curve = new QwtPlotCurve(curveName);
	curve->setPen(color, 2); // 设置曲线颜色和宽度
	curve->attach(plot);
	curves.append(curve);
	xDataMap[curveName] = QVector<double>(); // 初始化数据存储
	yDataMap[curveName] = QVector<double>();
}