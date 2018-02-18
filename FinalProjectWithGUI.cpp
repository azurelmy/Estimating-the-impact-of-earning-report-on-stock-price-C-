#include "ExcelDriver\stdafx.h"
#include "FinalProjectWithGUI.h"
#include <qwidget.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include <thread>
#include <qmessagebox.h>
#include <QlineEdit>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qmessagebox.h>
#include <QCloseEvent>

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

FinalProjectWithGUI::FinalProjectWithGUI(QWidget *parent)
	: QWidget(parent)
{

	ui.setupUi(this);
	ui.calculateButton->hide();
	ui.printButton->hide();
	ui.group1Button->hide();
	ui.group2Button->hide();
	ui.group3Button->hide();
	ui.submitStockPrice->hide();
	ui.showCAARButton->hide();
	ui.group1AAR->hide();
	ui.group2AAR->hide();
	ui.group3AAR->hide();
	ui.AARButton->hide();
	ui.CAARButton->hide();
	ui.showGraphButton->hide();
	

	connect(ui.downloadButton, SIGNAL(pressed()), this, SLOT(showtext()));
	connect(ui.downloadButton, SIGNAL(clicked()), this, SLOT(download()));
	connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(exitprogram()));
	connect(ui.printButton, SIGNAL(clicked()), this, SLOT(printonestock()));
	connect(ui.group1Button, SIGNAL(clicked()), this, SLOT(group1stockprice()));
	connect(ui.group2Button, SIGNAL(clicked()), this, SLOT(group2stockprice()));
	connect(ui.group3Button, SIGNAL(clicked()), this, SLOT(group3stockprice()));
	connect(ui.submitStockPrice, SIGNAL(clicked()), this, SLOT(submitforstockprice()));
	connect(ui.calculateButton, SIGNAL(clicked()), this, SLOT(calculationforgroups()));
	connect(ui.showCAARButton, SIGNAL(clicked()), this, SLOT(printAARs()));
	connect(ui.group1AAR, SIGNAL(clicked()), this, SLOT(group1aar()));
	connect(ui.group2AAR, SIGNAL(clicked()), this, SLOT(group2aar()));
	connect(ui.group3AAR, SIGNAL(clicked()), this, SLOT(group3aar()));
	connect(ui.AARButton, SIGNAL(clicked()), this, SLOT(showaar()));
	connect(ui.CAARButton, SIGNAL(clicked()), this, SLOT(showcaar()));
	connect(ui.showGraphButton, SIGNAL(clicked()), this, SLOT(showgraph()));


	setWindowTitle(tr("Automatically stock analysis system"));
}

//for download button
void FinalProjectWithGUI::download() {
	vector<DownloadInfo> stockInfo = getData();
	dividedGroup Groups = partitionTo3Group(stockInfo, 5.0);

	stocks1 = stockStorage(Groups[0]);
	stocks2 = stockStorage(Groups[1]);
	stocks3 = stockStorage(Groups[2]);
	stock_list.resize(3);
	vector<map<string, StockPrice>*> ptr(3);
	ptr[0] = &stock_list[0];
	ptr[1] = &stock_list[1];
	ptr[2] = &stock_list[2];
	std::thread first(downloadYahoo1, stocks1, ptr[0]);
	std::thread second(downloadYahoo2, stocks2, ptr[1]);
	std::thread third(downloadYahoo3, stocks3, ptr[2]);
	first.join();
	second.join();
	third.join();
	cout << "All threads download complete." << endl;

	ui.calculateButton->show();
	ui.printButton->show();
	ui.downloadButton->setEnabled(false);
	ui.outputBox->clear();

	QMessageBox::information(this, tr("Download successfully!"), tr("data has downloaded successfully and divided  into 3 groups individually named 'beat', 'match' and 'miss'!"));
	
}
//for downloadbutton
void FinalProjectWithGUI::showtext() {
	ui.outputBox->setText("Downloading, please wait.");
}


//for exitbutton
void FinalProjectWithGUI::exitprogram() {
	this->close();
}
//for x close
void FinalProjectWithGUI::closeEvent(QCloseEvent * event)
{
	switch (QMessageBox::information(this, tr("Exiting the program"),
		tr("Do you really want to exit the program?"),
		tr("Yes"), tr("No"),
		0, 1))
	{
	case 0:
		event->accept();
		break;
	case 1:
	default:
		event->ignore();
		break;
	}
}

//for print button
void FinalProjectWithGUI::printonestock() {
	ui.inputLabel->setText("Please select a group");
	ui.outputBox->clear();
	ui.inputLine->clear();
	ui.group1Button->show();
	ui.group2Button->show();
	ui.group3Button->show();
	ui.inputLine->hide();
}

//for print available ticker
QString FinalProjectWithGUI::availableTicker(vector<stock> stocks) {
	QString ret;
	for (unsigned int i = 0; i < stocks.size(); i++) {
		ret = ret + QString::fromStdString(stocks[i].getTicker()) + QString::fromStdString("; ");
	}
	return ret;
}

//for group1stockprice
void FinalProjectWithGUI::group1stockprice() {
	ui.inputLabel->setText("Please input a ticker and click submit:");
	ui.group1Button->hide();
	ui.group2Button->hide();
	ui.group3Button->hide();
	ui.inputLine->show();
	ui.submitStockPrice->show();
	ui.outputLabel->setText("Available tickers are listed below:");
	ui.outputBox->setText(availableTicker(stocks1));
	group_number = 0;
}

//for group2stockprice
void FinalProjectWithGUI::group2stockprice() {
	ui.inputLabel->setText("Please input a ticker and click submit:");
	ui.group1Button->hide();
	ui.group2Button->hide();
	ui.group3Button->hide();
	ui.inputLine->show();
	ui.submitStockPrice->show();
	ui.outputLabel->setText("Available tickers are listed below:");
	ui.outputBox->setText(availableTicker(stocks2));
	group_number = 1;
}

//for group1stockprice
void FinalProjectWithGUI::group3stockprice() {
	ui.inputLabel->setText("Please input a ticker and click submit:");
	ui.group1Button->hide();
	ui.group2Button->hide();
	ui.group3Button->hide();
	ui.inputLine->show();
	ui.submitStockPrice->show();
	ui.outputLabel->setText("Available tickers are listed below:");
	ui.outputBox->setText(availableTicker(stocks3));
	group_number = 2;
}

QString FinalProjectWithGUI::getStockPrice(StockPrice stockprice) {
	QString ret;
	for (unsigned int i = 0; i < stockprice.getStockPrice().size(); i++) {
		ret = ret + QString::fromStdString(to_string(stockprice.getStockPrice()[i])) + QString::fromStdString("\n");
	}
	return ret;
}

//for submit button
void FinalProjectWithGUI::submitforstockprice() {
    map<string, StockPrice>::iterator it;

	QString stockticker = ui.inputLine->text();

	if (stockticker.isEmpty()) {
		QMessageBox::information(this, tr("Empty Field"),
			tr("Please enter a ticker."));
		return;
	}
	for (it = stock_list[group_number].begin(); it != stock_list[group_number].end(); it++) {
		if (QString::fromStdString(it->first) == stockticker) {
			ui.outputBox->clear();
			ui.outputBox->setText(getStockPrice(it->second));
			ui.outputLabel->setText("Stock price for " + QString::fromStdString(it->first) + ":");
			break;
		}
	}
	if (it == stock_list[group_number].end()) {
		QMessageBox::information(this, tr("Cannot find entered ticker!"),
			tr("Please enter again.\nNote: Case sensitive."));
		ui.inputLine->clear();
		return;
	}
	ui.submitStockPrice->hide();
	ui.inputLabel->setText("Please input here:");
}

void FinalProjectWithGUI::calculationforgroups() {
	ui.inputLine->clear();
	ui.outputBox->clear();
	ui.outputLabel->setText("Output:");
	ui.submitStockPrice->hide();

	for (int i = 0; i < 3; i++) {
		Vector2 temp(90);
		AAR.push_back(temp);
		CAAR.push_back(temp);
	}
	
	for (int i = 0; i < 3; i++) {
		Vector<double, long> temp(90);
		aar.push_back(temp);
		caar.push_back(temp);
	}

	NumericMatrix<double, long> tempnumericmatrix(90, 6);//matrix for excel
	result = tempnumericmatrix;
	Matrix2 tempResult(3);
	for (int i = 0; i < 3; i++) {
		calAAR(stock_list[i], AAR[i]);
		calCAAR(AAR[i], CAAR[i]);
		convertv2tv1(aar[i], AAR[i]);
		convertv2tv1(caar[i], CAAR[i]);
	}
	for (int i = 0; i < 3; i++) {
		tempResult[i].resize(2);
		tempResult[i][0] = AAR[0];  tempResult[i][1] = CAAR[0];
	}
	result.Column(1, aar[0]);  result.Column(2, aar[1]);
	result.Column(3, aar[2]);  result.Column(4, caar[0]);
	result.Column(5, caar[1]); result.Column(6, caar[2]);

	QMessageBox::information(this, tr("Calculation completed!"), 
		tr("Calculation for AARs and CAARs of each group is completed."));
	ui.calculateButton->setEnabled(false);
	ui.showCAARButton->show();
	ui.showGraphButton->show();
}


void FinalProjectWithGUI::printAARs() {
	ui.submitStockPrice->hide();
	ui.inputLabel->setText("Please select a group");
	ui.outputBox->clear();
	ui.inputLine->clear();
	ui.group1AAR->show();
	ui.group2AAR->show();
	ui.group3AAR->show();
	ui.inputLine->hide();
	ui.AARButton->hide();
	ui.CAARButton->hide();
}

//for group1aar
void FinalProjectWithGUI::group1aar() {
	ui.inputLabel->setText("Please select AARs or CAARs:");
	ui.group1AAR->hide();
	ui.group2AAR->hide();
	ui.group3AAR->hide();
	ui.AARButton->show();
	ui.CAARButton->show();
	group_number = 0;
}

//for group2aar
void FinalProjectWithGUI::group2aar() {
	ui.inputLabel->setText("Please select AARs or CAARs:");
	ui.group1AAR->hide();
	ui.group2AAR->hide();
	ui.group3AAR->hide();
	ui.AARButton->show();
	ui.CAARButton->show();
	group_number = 1;
}

//for group3aar
void FinalProjectWithGUI::group3aar() {
	ui.inputLabel->setText("Please select AARs or CAARs:");
	ui.group1AAR->hide();
	ui.group2AAR->hide();
	ui.group3AAR->hide();
	ui.AARButton->show();
	ui.CAARButton->show();
	group_number = 2;
}

QString FinalProjectWithGUI::getAAR(vector<Vector2> AAR) {
	QString ret;
	for (unsigned int i = 0; i < AAR[group_number].size(); i++) {
		ret = ret + QString::fromStdString(to_string(AAR[group_number][i])) + QString::fromStdString("\n");
	}
	return ret;
}

void FinalProjectWithGUI::showaar() {
	ui.outputLabel->setText("Group " + QString::fromStdString(to_string(group_number + 1))+"'s AARs:");
	ui.outputBox->setText(getAAR(AAR));
}

void FinalProjectWithGUI::showcaar() {
	ui.outputLabel->setText("Group " + QString::fromStdString(to_string(group_number + 1)) + "'s CAARs:");
	ui.outputBox->setText(getAAR(CAAR));
}

void FinalProjectWithGUI::showgraph() {
	static ExcelDriver &excel = ExcelDriver::Instance();
	exlforprint(result, excel, caar[0], caar[1], caar[2]);
	
	ui.inputLabel->setText("Please input here:");
	ui.inputLine->show();
	ui.outputLabel->setText("Output:");
	ui.outputBox->clear();
	ui.group1Button->hide();
	ui.group2Button->hide();
	ui.group3Button->hide();
	ui.submitStockPrice->hide();
	ui.group1AAR->hide();
	ui.group2AAR->hide();
	ui.group3AAR->hide();
	ui.AARButton->hide();
	ui.CAARButton->hide();
	ui.showGraphButton->setEnabled(false);
	
}

void multiCalculation(void(*calAAR)(map<string, StockPrice>& stocklist, Vector2& result), void(*calCAAR)(Vector2& AAR, Vector2& CAAR),
	void(*convertv2tv1)(Vector<double, long> &v1, Vector2 &v2),
	map<string, StockPrice>& stocklist, Vector2& AAR, Vector2& CAAR, Vector<double, long>& aar, Vector<double, long>& caar,
	int* calController) {
	while (1) {
		if ((*calController) == 1) { break; }
	}
	calAAR(stocklist, AAR);
	calCAAR(AAR, CAAR);
	convertv2tv1(aar, AAR);
	convertv2tv1(caar, CAAR);
	cout << "Calculation Complete." << endl;
}