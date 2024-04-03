#pragma once
#include <QtCharts/QChartView>
#include <QGestureEvent>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QScroller>
#include <QtCharts/QChart>
#include <QApplication>
#include <QMainWindow>
#include <QChartView>
#include <QLineSeries>
#include <QTimer>
#include <QValueAxis>
#include <QTime>
#include <QToolTip>
#include <QMouseEvent>
#include <QWheelEvent>

QT_CHARTS_USE_NAMESPACE

class CustomChartView : public QChartView {
	Q_OBJECT

public:
	explicit CustomChartView(QChart *chart, QWidget *parent = nullptr);
	~CustomChartView();

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

private:
	bool isDragging;
	QPoint m_lastPos;
};