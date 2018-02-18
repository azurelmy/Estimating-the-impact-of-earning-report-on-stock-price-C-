#pragma once
#ifndef VectorMatrixoverload_h
#define VectorMatrixoverload_h

#include <stdio.h>
#include <vector>
using namespace std;
//define a new type to hold stock price,AAR,CAAR
typedef vector<double> Vector2;//my vector, the vector used for excel is Vector

//define a new type to hold result,each element is a Vector2
typedef vector<vector<Vector2>> Matrix2;

//overload some operators to make computation easier
Vector2 operator/(const Vector2& U, const Vector2& V);

Vector2 operator+(const Vector2& U, const Vector2& V);

Vector2 operator-(const Vector2& U, const Vector2& V);

Vector2 operator/(const Vector2& U, const int N);
void print(Vector2& u);

#endif
