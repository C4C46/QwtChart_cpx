#include "TrendWidget.h"
#include <QPainter>

TrendWidget::TrendWidget(QWidget *parent)
	: QWidget(parent)
{}

void TrendWidget::setPoints(const QVector<QPointF> &points)
{
	m_points = points;
	update(); // 重绘组件
}

void TrendWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	if (m_points.isEmpty()) return;

	// 绘制趋势图逻辑
	for (int i = 0; i < m_points.size() - 1; ++i) {
		painter.drawLine(m_points[i], m_points[i + 1]);
	}
}