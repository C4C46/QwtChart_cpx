#pragma once

#include <QObject>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_scale_div.h>
#include <QVBoxLayout>
#include <QTime>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleValidator>
#include "CustomChartView.h" 
#include "ChartUpdaterThread.h"
#include <qwt_plot_magnifier.h>

class CustomMagnifier : public QwtPlotMagnifier {
public:
	using QwtPlotMagnifier::QwtPlotMagnifier; // 继承构造函数

protected:
	virtual void rescale(double factor) override {
		QwtPlot* plot = this->plot();
		if (!plot) return;

		// 调用基类的rescale方法进行缩放
		QwtPlotMagnifier::rescale(factor);

		double xMin = plot->axisScaleDiv(QwtPlot::xBottom).lowerBound();
		double xMax = plot->axisScaleDiv(QwtPlot::xBottom).upperBound();
		double yMin = plot->axisScaleDiv(QwtPlot::yLeft).lowerBound();
		double yMax = plot->axisScaleDiv(QwtPlot::yLeft).upperBound();

		// 确保X轴和Y轴的最小值不小于0
		xMin = std::max(0.0, xMin);
		yMin = std::max(0.0, yMin);

		// 重新设置坐标轴范围
		plot->setAxisScale(QwtPlot::xBottom, xMin, xMax);
		plot->setAxisScale(QwtPlot::yLeft, yMin, yMax);

		plot->replot();
	}
};


class ChartManager : public QObject {
    Q_OBJECT

public:
    ChartManager(QObject *parent, QWidget*parentWidget =nullptr);
	~ChartManager();
    void start();
	QWidget* getWidget();


public slots:
	void onChartUpdate(int x, qreal y);
	void onIntervalPBClicked();

private:
	QWidget *m_widget; // 替换QMainWindow为QWidget
	QwtPlot *plot; // 使用QwtPlot代曲原来的QChart
	QwtPlotCurve *curve; // 用于绘制曲线
	ChartUpdaterThread *updaterThread;
	QVector<double> xData, yData; // 用于存储数据点
	double xInterval = 10; // 默认x间隔值
	double yInterval = 10; // 默认y间隔值


};

