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
	double x = 0;
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

//void ChartUpdaterThread::run() {
//    double x = 0;
//    while (running) {
//        // 生成一个小于1的随机增量，模拟1米内有多个点
//        qreal xIncrement = (qrand() % 100) / 100.0; // 产生0到1之间的随机数
//        x += xIncrement;
//
//        for (const QString &curveName : curveNames) {
//            qreal y = qrand() % 1000; // y值现在表示毫米，范围0到999
//            emit updateChart(curveName, x, y);
//        }
//
//        QThread::msleep(100); // 使用msleep代替sleep，以便更频繁地更新数据
//    }
//}

void ChartUpdaterThread::stopRunning() {

	running = false;
}

void ChartUpdaterThread::updateCurveNames(const QStringList &newCurveNames) {
	QMutexLocker locker(&mutex); // 确保线程安全
	curveNames = newCurveNames;
}