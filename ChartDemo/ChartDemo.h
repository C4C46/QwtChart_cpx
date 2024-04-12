#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChartDemo.h"
#include "ChartManger.h"
#include "ConfigLoader.h"

class ChartDemo : public QMainWindow
{
    Q_OBJECT

public:
    ChartDemo(QWidget *parent = nullptr);
    ~ChartDemo();



	void init();

	void updateToggleButtonPosition();

public slots:
	void handleIntervalPBClicked();
	void toggleTableVisibility();
protected:
	void resizeEvent(QResizeEvent * event) override;

private:
    Ui::ChartDemoClass ui;
	ChartManager *chartManager;
	ConfigLoader *configLoader;

	QPushButton* toggleTableButton;
};
