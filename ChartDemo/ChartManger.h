#pragma once

#include <QObject>
//#include <QtCharts/QChartView>
//#include <QtCharts/QLineSeries>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include "CustomChartView.h" 
#include "ChartUpdaterThread.h"

QT_CHARTS_USE_NAMESPACE

class ChartManager : public QObject {
    Q_OBJECT

public:
    ChartManager(QObject *parent, QWidget*parentWidget =nullptr);
	~ChartManager();
    void start();
    QMainWindow* getWindow();
	CustomChartView* getChartView() const { return chartView; }

private:
    QMainWindow *window;
	QWidget *m_widget;
    QLineSeries *series;
    QChart *chart;
    CustomChartView *chartView;

	QwtPlot *plot; // 使用QwtPlot代曲原来的QChart
	QwtPlotCurve *curve; // 用于绘制曲线
    ChartUpdaterThread *updaterThread;

private slots:
    void onChartUpdate(int x, qreal y);

};

