#pragma once
#include <QThread>
#include <QObject>
#include <QMutex>
class ChartUpdaterThread : public QThread{
	Q_OBJECT

public:
	ChartUpdaterThread(QObject *parent, const QStringList &curveNames);
	~ChartUpdaterThread();
	void run() override;
	void updateCurveNames(const QStringList &newCurveNames); // 增加新曲线
signals:
	void updateChart(const QString &curveName, int x, qreal y);

public slots:
	void stopRunning();


private:
	QStringList curveNames; // 存储曲线名称
	QMutex mutex; // 用于线程安全地更新曲线名称列表
	bool running = true;
};

