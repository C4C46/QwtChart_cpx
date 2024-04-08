#pragma once
#include <QThread>
#include <QObject>

class ChartUpdaterThread : public QThread{
	Q_OBJECT

public:
	ChartUpdaterThread(QObject *parent, const QStringList &curveNames);
	~ChartUpdaterThread();
	void run() override;

signals:
	void updateChart(const QString &curveName, int x, qreal y);

protected:
	bool running = true;

public slots:
	void stopRunning();


private:
	QStringList curveNames; // 存储曲线名称
};

