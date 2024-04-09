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
#include <QStringList>
#include "CustomChartView.h" 
#include "ChartUpdaterThread.h"
#include <qwt_plot_magnifier.h>
#include <qwt_text.h>
#include <qwt_legend.h>
class ChartManager : public QObject {
    Q_OBJECT

public:
    ChartManager(QObject *parent, QWidget*parentWidget, const QStringList &curveNames);
	~ChartManager();
    void start();
	QWidget* getWidget();


public slots:
	void onChartUpdate(const QString &curveName, int x, qreal y);
	void onIntervalPBClicked();
	void addCurve(const QString &curveName, const QColor &color); // 新增方法


private:
	QWidget *m_widget; // 替换QMainWindow为QWidget
	QwtPlot *plot; // 使用QwtPlot代曲原来的QChart
	ChartUpdaterThread *updaterThread;
	QVector<QwtPlotCurve *> curves; // 支持多条曲线
	QMap<QString, QVector<double>> xDataMap, yDataMap; // 使用映射存储每条曲线的数据
	double xInterval = 10; // 默认x间隔值
	double yInterval = 10; // 默认y间隔值

	QStringList curveNames; // 添加成员变量存储曲线名称
};

