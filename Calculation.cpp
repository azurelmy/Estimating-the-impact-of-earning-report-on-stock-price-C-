#include "stdafx.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include "PreForYahoo.h"
#include "Calculation.h"
#include "ExcelDriver\VectorsAndMatrices\NumericMatrix.cpp"
#include "VectorMatrixoverload.h"
#include "YahooFinance.h"


using namespace std;

//compute AAR for one group by going through the map of stocks
void calAAR(map<string, StockPrice>& stocklist, Vector2& result) {
	map<string, StockPrice>::iterator itr;
	//Vector2 result(90);
	for (itr = stocklist.begin(); itr != stocklist.end(); itr++) {
		Vector2 stock_return(90);
		Vector2 spy_return(90);
		for (int i = 0; i < 90; i++) {
			stock_return[i] = (itr->second.getStockPrice()[i + 1] - itr->second.getStockPrice()[i]) / itr->second.getStockPrice()[i];
			spy_return[i] = (itr->second.getSpyPrice()[i + 1] - itr->second.getSpyPrice()[i]) / itr->second.getSpyPrice()[i];
		}
		result = result + (stock_return - spy_return);
	}
	result = result / stocklist.size();
}

//compute CAAR for one group
void calCAAR(Vector2& AAR, Vector2& CAAR) {
	//Vector2 CAAR(90);
	CAAR[0] = AAR[0];
	for (int j = 1; j < 90; j++) {
		CAAR[j] = CAAR[j - 1] + AAR[j];
	}
	//return CAAR;
}

void convertv2tv1(Vector<double, long> &v1, Vector2 &v2) {
	int n1 = v2.size();
	int n2 = v1.Array::Size();

	for (int i = 0; i <n2; i++) {
		v1[i + 1] = v2[i];
	}
}