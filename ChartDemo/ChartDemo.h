#pragma once

#include <QWidget>
#include "ui_ChartDemo.h"
#include "ChartManger.h"
#include "ConfigLoader.h"
#include "DataScope.h"
#include "ChartUpdaterThread.h"



class ChartDemo : public QWidget
{
	Q_OBJECT

public:
	ChartDemo(QWidget *parent = nullptr);
	~ChartDemo();




	void init();

public slots:
	void updateData(const QString &curveName, double x, double y);
	void handleIntervalPBClicked();
	void toggleTableVisibility();

	


private:
	Ui::lpTendencyClass ui;
	ChartManager *chartManager;
	ConfigLoader *configLoader;
	DataScope *dataScope;
	ChartUpdaterThread *chartUpdaterThread;



};
