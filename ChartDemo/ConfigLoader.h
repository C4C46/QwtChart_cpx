#pragma once

#include <QObject>
#include <QTableWidget>
class ConfigLoader :
	public QObject
{
	Q_OBJECT

public:
	explicit ConfigLoader(QTableWidget *tableWidget, QObject *parent = nullptr);
	void loadConfig(const QString &filePath);

private:
	QTableWidget *m_tableWidget;
};

