#include "ChartManger.h"

#pragma execution_character_set("utf-8")

ChartManager::ChartManager(QObject *parent, QWidget *parentWidget, const QStringList &curveNames)
	: QObject(parent), m_widget(parentWidget), curveNames(curveNames)
{
	plot = new QwtPlot(parentWidget);
	//plot->setTitle("实时趋势图");
	plot->setCanvasBackground(Qt::white);

	// 启用图例
	plot->insertLegend(new QwtLegend(), QwtPlot::TopLegend);

	// 设置X轴和Y轴的标题
	plot->setAxisTitle(QwtPlot::xBottom,"");
	plot->setAxisTitle(QwtPlot::yLeft,"");

	// 创建并配置网格
	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->attach(plot); // 将网格附加到图表
	grid->setVisible(false); // 隐藏网格线

	updaterThread = new ChartUpdaterThread(this, curveNames);

	//定义颜色生成步长
	int colorStep = 360 / curveNames.size();
	for (int i = 0; i < curveNames.size(); ++i)
	{
		QColor color = QColor::fromHsv((colorStep * i) % 360, 255, 180);
		addCurve(curveNames[i], color);
	}

	if (m_widget)
	{
		QVBoxLayout *layout = new QVBoxLayout(m_widget);
		layout->addWidget(plot);
		m_widget->setLayout(layout);
	}

	QwtLegend *legend = new QwtLegend();
	legend->setDefaultItemMode(QwtLegendData::Clickable);
	plot->insertLegend(legend, QwtPlot::TopLegend);


	connect(updaterThread, &ChartUpdaterThread::updateChart, this, &ChartManager::onChartUpdate);
	// 连接图例点击信号
	connect(legend, SIGNAL(clicked(const QVariant &, int)), this, SLOT(onLegendClicked(const QVariant &, int)));

	installEventFilters();
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

	// 更新X轴和Y轴的范围
	plot->setAxisScale(QwtPlot::xBottom, xMin, xMax);
	plot->setAxisScale(QwtPlot::yLeft, yMin, yMax);

	plot->replot(); // 重绘图表
}

void ChartManager::onIntervalPBClicked() {
	QDialog dialog(m_widget); // 使用当前widget作为父窗口
	QVBoxLayout layout(&dialog);
	dialog.setWindowTitle("参数设置");

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
		plot->replot(); // 重绘图表以应用新的间隔
	}
}


void ChartManager::addCurve(const QString &curveName, const QColor &color) {
	QwtPlotCurve *curve = new QwtPlotCurve(curveName);
	curve->setTitle(curveName); // 设置曲线的标题，这将在图例中显示
	curve->setPen(color, 3); // 设置曲线颜色和宽度
	curve->attach(plot);
	curves.append(curve);
	xDataMap[curveName] = QVector<double>(); // 初始化数据存储
	yDataMap[curveName] = QVector<double>();
}

void ChartManager::onLegendClicked(const QVariant &itemInfo, int index) {
	QwtPlotItem *clickedItem = plot->infoToItem(itemInfo);
	if (!clickedItem) return;

	// 首先重置所有曲线到初始透明度状态
	resetCurvesOpacity();

	// 然后设置未被点击曲线的透明度
	for (auto &curve : curves) {
		if (curve != clickedItem) {
			QColor color = curve->pen().color();
			color.setAlpha(50); // 设置为半透明
			curve->setPen(QPen(color, 2));
		}
	}

	plot->replot(); // 重绘图表以应用更改
}


void ChartManager::resetCurvesOpacity() {
	for (auto &curve : curves) {
		QColor color = curve->pen().color();
		color.setAlpha(255); // 设置为完全不透明
		curve->setPen(QPen(color, 3));
	}
}


void ChartManager::installEventFilters() {
	plot->canvas()->installEventFilter(this);
}

bool ChartManager::eventFilter(QObject *watched, QEvent *event) {
	if (watched == plot->canvas() && event->type() == QEvent::MouseButtonPress) {
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
		if (mouseEvent->button() == Qt::LeftButton) {
			resetCurvesOpacity();
			plot->replot();
			return true; // 表示事件已处理
		}
	}
	return QObject::eventFilter(watched, event); // 对于其他事件，调用基类的事件过滤器方法
}