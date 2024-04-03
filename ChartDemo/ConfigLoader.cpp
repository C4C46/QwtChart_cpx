#include "ConfigLoader.h"
#include "ConfigLoader.h"
#include <QFile>
#include <QTextStream>

ConfigLoader::ConfigLoader(QTableWidget *tableWidget, QObject *parent)
	: QObject(parent), m_tableWidget(tableWidget)
{}

void ConfigLoader::loadConfig(const QString &filePath)
{
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		// 假设配置文件格式为：选项名称,是否显示
		QStringList parts = line.split(",");
		if (parts.size() != 2) continue;

		int row = m_tableWidget->rowCount();
		m_tableWidget->insertRow(row);
		m_tableWidget->setItem(row, 0, new QTableWidgetItem(parts[0]));
		m_tableWidget->setItem(row, 1, new QTableWidgetItem(parts[1]));
	}
}