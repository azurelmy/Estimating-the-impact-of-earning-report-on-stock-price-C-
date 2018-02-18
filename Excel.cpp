#include "stdafx.h"
#include "Excel.h"

using namespace std;

int exlforprint(NumericMatrix<double, long>& matrix, ExcelDriver& excel, Vector<double, long>& v1, Vector<double, long>& v2, Vector<double, long>& v3)
{

	long N = 89; //long M = 30;
				 //NumericMatrix<double, long> matrix(N + 1, M + 1);

	Vector<double, long> xarr(N + 1);
	//Vector<double, long> yarr(N + 1, 1, 0);
	//Vector<double, long> yarr2(N+1);
	//Vector<double, long> yarr(6); //AARCAAR y-axis
	//yarr[1] = 1; yarr[2] = 2; yarr[3] = 3;
	//yarr[4] = 1; yarr[5] = 2; yarr[6] = 3;


	//set x-axis range& steps
	double h1 = 1;
	xarr[xarr.MinIndex()] = -30;
	xarr[xarr.MaxIndex()] = 59;
	for (long i = xarr.MinIndex() + 1; i <= xarr.MaxIndex(); i++)
	{
		xarr[i] = xarr[i - 1] + h1;
	}

	//double h2 = 0.2;
	//yarr[yarr.MinIndex()] = 0.0;
	//for (long j = yarr.MinIndex()+1; j <= yarr.MaxIndex(); j++)
	//{
	//	yarr[j] = yarr[j-1] + h2;
	//yarr2[j] = yarr2[j-1] + yarr[j];
	//}

	//create textual info
	list<std::string> rowlabels = convertToString(xarr);
	//list<std::string> columnlabels = convertToString(yarr);
	list<std::string> columnlabels = { "AAR-miss","AAR-match","AAR-beat","CAAR-miss","CAAR-match","CAAR-beat" };
	std::string sheetName("AAR&CAAR data");


	//start excel and make it visible
	//	ExcelDriver& excel = ExcelDriver::Instance();
	excel.MakeVisible(true);		// Default is INVISIBLE!

									//send the matrix to the excel
	excel.AddMatrix(sheetName, matrix, rowlabels, columnlabels);

	list<Vector<double, long>>m;//m is the combination of CAAR for 3 groups
	m.push_back(v1);
	m.push_back(v2);
	m.push_back(v3);

	string chartTitle = "CAAR for 3 groups";// graph title
	string xTitle = "Day"; //graph x-axis title
	string yTitle = "CAAR";//graph y-axis title
	list<std::string> vectorlabels = { "miss","match", "beat" };

	try
	{
		excel.CreateChart(xarr, vectorlabels, m, chartTitle, xTitle, yTitle);
	}
	catch (DatasimException &e)
	{
		e.print();
	}
	catch (...)
	{
		// Catches everything else
	}


	return 0;
}