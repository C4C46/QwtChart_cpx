#include "ChartUpdaterThread.h"
#include <QTime>

ChartUpdaterThread::ChartUpdaterThread(QObject *parent) : QThread(parent) {
	qsrand(QTime::currentTime().msec());
}
ChartUpdaterThread::~ChartUpdaterThread() {

}


void ChartUpdaterThread::run() {
	int x = 0;
	while (running) {
		qreal y = (qrand() % 800);
		emit updateChart(x, y);
		x += 200;
		QThread::sleep(1); // 模拟数据更新频率
	}
}

void ChartUpdaterThread::stopRunning() {

	running = false;
}