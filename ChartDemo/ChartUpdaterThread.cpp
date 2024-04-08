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
		qreal xIncrement = qrand() % 200 + 1; // 生成1到200之间的随机增量
		x += xIncrement; // x递增一个随机值
		qreal y = qrand() % 100; // 生成0到99之间的随机y值

		emit updateChart(x, y);
		QThread::sleep(1); // 模拟数据更新频率
	}
}

void ChartUpdaterThread::stopRunning() {

	running = false;
}