#include "ChartUpdaterThread.h"
#include <QTime>

ChartUpdaterThread::ChartUpdaterThread(QObject *parent) : QThread(parent) {
	qsrand(QTime::currentTime().msec());
}
ChartUpdaterThread::~ChartUpdaterThread() {

}

//
//void ChartUpdaterThread::run() {
//	int x = 0;
//	while (running) {
//		qreal xIncrement = qrand() % 200 + 1; // 生成1到200之间的随机增量
//		x += xIncrement; // x递增一个随机值
//		qreal y1 = qrand() % 100; // 生成0到99之间的随机y值
//		qreal y2 = qrand() % 100; // 为第二条曲线生成另一个随机y值
//
//		emit updateChart("Curve1", x, y1);
//		emit updateChart("Curve2", x, y2);
//		QThread::sleep(1); // 模拟数据更新频率
//	}
//}

void ChartUpdaterThread::run() {
	int x = 0;
	while (running) {
		qreal xIncrement = qrand() % 50 + 1; // 生成1到50之间的随机增量
		x += xIncrement; // x递增一个随机值

		for (int i = 1; i <= 18; ++i) {
			qreal y = qrand() % 100; // 生成0到99之间的随机y值
			QString curveName = QString("Curve%1").arg(i);
			emit updateChart(curveName, x, y);
		}

		QThread::sleep(1); // 模拟数据更新频率
	}
}
void ChartUpdaterThread::stopRunning() {

	running = false;
}