#include "ChartUpdaterThread.h"
#include <QTime>

ChartUpdaterThread::ChartUpdaterThread(QObject *parent, const QStringList &curveNames)
	: QThread(parent), curveNames(curveNames)
{
	qsrand(QTime::currentTime().msec());
}
ChartUpdaterThread::~ChartUpdaterThread() {

}

void ChartUpdaterThread::run() {
	int x = 0;
	while (running) {
		qreal xIncrement = qrand() % 50 + 1;
		x += xIncrement;

		for (const QString &curveName : curveNames) {
			qreal y = qrand() % 100;
			emit updateChart(curveName, x, y);
		}

		QThread::sleep(1);
	}
}

void ChartUpdaterThread::stopRunning() {

	running = false;
}