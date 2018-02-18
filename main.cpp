#include "ExcelDriver\stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "ReadBloombergInfo.h"
#include "PreForYahoo.h"
#include "YahooFinance.h"
#include "Calculation.h"
#include "ExcelDriver\ExcelDriver.hpp"
#include "ExcelDriver\ExcelMechanisms.hpp"
#include "ExcelDriver\BitsAndPieces\StringConversions.hpp"
#include "ExcelDriver\VectorsAndMatrices\NumericMatrix.cpp" // Template
#include "ExcelDriver\ExceptionClasses\DatasimException.hpp"

#include "FinalProjectWithGUI.h"
#include <QtWidgets/QApplication>

using namespace std;




int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FinalProjectWithGUI w;
	w.show();
	return a.exec();
}
