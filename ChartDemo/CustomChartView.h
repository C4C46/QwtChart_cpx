#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QLineSeries>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <QWidget>
#include <QVBoxLayout>
class CustomChartView : public QWidget {
	Q_OBJECT

public:
	explicit CustomChartView(QWidget *parent = nullptr);
	virtual ~CustomChartView();

	void setPlot(QwtPlot *plot);

protected:


private:
	QwtPlot *plot;
	QwtPlotPanner *panner;
	QwtPlotMagnifier *magnifier;
};