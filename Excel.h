#pragma once

#ifndef Excel_h
#define Excel_h

#include "ExcelDriver\BitsAndPieces\StringConversions.hpp"
#include "ExcelDriver\ExcelDriver.hpp"
#include "ExcelDriver\ExcelMechanisms.hpp"
#include "ExcelDriver\VectorsAndMatrices\NumericMatrix.cpp" // Template
#include "ExcelDriver\ExceptionClasses\DatasimException.hpp"
#include <string>
#include "VectorMatrixoverload.h"

using namespace std;

int exlforprint(NumericMatrix<double, long>& matrix, ExcelDriver& excel, Vector<double, long>& v1, Vector<double, long>& v2, Vector<double, long>& v3);


#endif