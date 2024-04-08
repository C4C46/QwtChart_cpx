#pragma once

#include <QObject>
#include <QTableWidget>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class ConfigLoader :
	public QObject
{
	Q_OBJECT

public:
	explicit ConfigLoader(QTableWidget *tableWidget, QObject *parent = nullptr);
	void loadConfig(const QString &filePath);
	void saveConfig(const QString &filePath); // 添加保存配置的声明
private:
	QTableWidget *m_tableWidget;
};

