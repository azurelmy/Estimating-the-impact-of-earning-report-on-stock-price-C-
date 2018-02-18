#pragma once
#ifndef Calculation_h
#define Calculation_h

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include "PreForYahoo.h"
#include "VectorMatrixoverload.h"
#include "YahooFinance.h"
#include "ExcelDriver\VectorsAndMatrices\NumericMatrix.cpp"


void calAAR(map<string, StockPrice>& stocklist, Vector2& result);

void calCAAR(Vector2& AAR, Vector2& CAAR);

//convert Vector2 to Vector, Vector is a class that excelDrive required
void convertv2tv1(Vector<double, long> &v1, Vector2 &v2);





#endif