#pragma once
#include "ExcelDriver\stdafx.h"
#include <QtWidgets/QWidget>
#include "ui_FinalProjectWithGUI.h"
#include <qwidget.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include <qmessagebox.h>
#include <qtextedit.h>
#include <QlineEdit>
#include <qpushbutton.h>

#include <iostream>
#include <vector>
#include <string>
#include "ReadBloombergInfo.h"
#include "PreForYahoo.h"
#include "YahooFinance.h"
#include "Calculation.h"
#include "Excel.h"
#include "ExcelDriver\ExcelDriver.hpp"
#include "ExcelDriver\ExcelMechanisms.hpp"
#include "ExcelDriver\BitsAndPieces\StringConversions.hpp"
#include "ExcelDriver\VectorsAndMatrices\NumericMatrix.cpp" // Template
#include "ExcelDriver\ExceptionClasses\DatasimException.hpp"

class FinalProjectWithGUI : public QWidget
{
	Q_OBJECT

public:
	FinalProjectWithGUI(QWidget *parent = 0);
	QString availableTicker(vector<stock> stocks);
	QString getStockPrice(StockPrice stockprice);
	QString getAAR(vector<Vector2> AAR);


public slots://for buttons
    void download();
	void showtext();
	void exitprogram();
	void closeEvent(QCloseEvent * event);
	void printonestock();
	void group1stockprice();
	void group2stockprice();
	void group3stockprice();
	void submitforstockprice();
	void calculationforgroups();
	void printAARs();
	void group1aar();
	void group2aar();
	void group3aar();
	void showaar();
	void showcaar();
	void showgraph();

private:
	Ui::FinalProjectWithGUIClass ui;
	QString temp_input;

	vector<map<string, StockPrice>> stock_list;
	vector<stock> stocks1;
	vector<stock> stocks2;
	vector<stock> stocks3;
	vector<Vector2> AAR;
	vector<Vector2> CAAR;
	vector<Vector<double, long>> aar;
	vector<Vector<double, long>> caar;
	NumericMatrix<double, long> result;
	int group_number;


};
