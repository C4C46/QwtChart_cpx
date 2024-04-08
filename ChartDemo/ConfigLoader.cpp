#include "ConfigLoader.h"
#include <QFile>
#include <QTextStream>

ConfigLoader::ConfigLoader(QTableWidget *tableWidget, QObject *parent)
	: QObject(parent), m_tableWidget(tableWidget)
{
	m_tableWidget->setColumnCount(2); // 设置为2列，一列是复选框，一列是名称
	m_tableWidget->verticalHeader()->setVisible(false); // 隐藏行号
	m_tableWidget->horizontalHeader()->setVisible(false); // 隐藏列号
	m_tableWidget->setShowGrid(false);
}

QStringList ConfigLoader::getCurveNames() const {
	return curveNames;
}


void ConfigLoader::loadConfig(const QString &filePath)
{
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QByteArray fileData = file.readAll();
	QJsonDocument doc = QJsonDocument::fromJson(fileData);

	if (doc.isNull() || !doc.isObject())
		return;

	QJsonObject jsonObject = doc.object();
	QJsonArray configArray = jsonObject["event_name"].toArray();

	m_tableWidget->setRowCount(configArray.size()); // 根据配置文件动态设置行数

	for (int i = 0; i < configArray.size(); ++i) {
		QJsonObject configObject = configArray[i].toObject();
		QString name = configObject["name"].toString();
		bool display = configObject["display"].toBool();

		if (display) { // 只有当display为true时，才考虑这个曲线名称
			curveNames.append(name); // 存储曲线名称
		}


		QCheckBox* checkBox = new QCheckBox();
		checkBox->setChecked(display);
		m_tableWidget->setCellWidget(i, 0, checkBox);
		m_tableWidget->setItem(i, 1, new QTableWidgetItem(name));
	}

}

void ConfigLoader::saveConfig(const QString &filePath)
{
	QJsonArray configArray;

	for (int i = 0; i < m_tableWidget->rowCount(); ++i) {
		QCheckBox* checkBox = qobject_cast<QCheckBox*>(m_tableWidget->cellWidget(i, 0));
		QTableWidgetItem* item = m_tableWidget->item(i, 1);

		if (checkBox && item) {
			QJsonObject configObject;
			configObject["name"] = item->text();
			configObject["display"] = checkBox->isChecked();
			configArray.append(configObject);
		}
	}

	QJsonObject jsonObject;
	jsonObject["event_name"] = configArray;

	QFile file(filePath);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QJsonDocument doc(jsonObject);
	file.write(doc.toJson());
}
