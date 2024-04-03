#pragma once
#include <qwidget.h>
#include <QVector>
#include <QPointF>

class TrendWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TrendWidget(QWidget *parent = nullptr);
	void setPoints(const QVector<QPointF> &points);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	QVector<QPointF> m_points;
};

