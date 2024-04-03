#include "CustomChartView.h"

CustomChartView::CustomChartView(QChart *chart, QWidget *parent) :
	QChartView(chart, parent),
	isDragging(false) {
	setInteractive(true);
}

CustomChartView::~CustomChartView() {

}

void CustomChartView::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		m_lastPos = event->pos();
		isDragging = true;
	}
	QChartView::mousePressEvent(event);
}

void CustomChartView::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() & Qt::LeftButton && isDragging) {
		int dx = event->pos().x() - m_lastPos.x();
		chart()->scroll(-dx, 0);
		m_lastPos = event->pos();
	}
	QChartView::mouseMoveEvent(event);
}

void CustomChartView::mouseReleaseEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton && isDragging) {
		isDragging = false;
	}
	QChartView::mouseReleaseEvent(event);
}

void CustomChartView::wheelEvent(QWheelEvent *event) {
	double factor = 1.1;
	if (event->angleDelta().y() > 0) {
		chart()->zoom(factor);
	}
	else {
		chart()->zoom(1.0 / factor);
	}
}