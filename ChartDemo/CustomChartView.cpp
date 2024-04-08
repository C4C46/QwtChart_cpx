#include "CustomChartView.h"

CustomChartView::CustomChartView(QWidget *parent) : QWidget(parent), plot(new QwtPlot(this)), panner(nullptr), magnifier(nullptr) {
	
	
	//QVBoxLayout *layout = new QVBoxLayout(this);
	//layout->addWidget(plot);
	//layout->setMargin(0); // 移除周围的边距，让plot充满整个widget
	//setLayout(layout);

	//// 设置QwtPlot的父对象为当前widget
	//plot->setParent(this);

	//// 启用拖动
	//panner = new QwtPlotPanner(plot->canvas());
	//panner->setMouseButton(Qt::LeftButton);

	//// 启用缩放
	//magnifier = new QwtPlotMagnifier(plot->canvas());
	//magnifier->setMouseButton(Qt::NoButton);
	//magnifier->setWheelModifiers(Qt::ControlModifier); // 使用Ctrl+滚轮进行缩放
}

CustomChartView::~CustomChartView() {

}

void CustomChartView::setPlot(QwtPlot *newPlot) {
	//delete panner; // 删除旧的panner
	//panner = new QwtPlotPanner(plot->canvas()); // 创建新的panner
	//panner->setMouseButton(Qt::LeftButton); // 重新设置拖动按钮

	//delete magnifier; // 删除旧的magnifier
	//magnifier = new QwtPlotMagnifier(plot->canvas()); // 创建新的magnifier
	//magnifier->setMouseButton(Qt::NoButton); // 重新设置缩放按钮
	//magnifier->setWheelModifiers(Qt::ControlModifier); // 使用Ctrl+滚轮进行缩放
}