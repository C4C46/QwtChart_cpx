#pragma once
#include <QThread>
#include <QObject>

class ChartUpdaterThread : public QThread{
	Q_OBJECT

public:
	ChartUpdaterThread(QObject *parent = nullptr);
	~ChartUpdaterThread();
	void run() override;

signals:
	void updateChart(const QString &curveName, int x, qreal y);

protected:
	bool running = true;

public slots:
	void stopRunning();

};

