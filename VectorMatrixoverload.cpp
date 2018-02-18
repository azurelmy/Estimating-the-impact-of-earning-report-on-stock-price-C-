#include "stdafx.h"
#include "curl.h"
#include <stdio.h>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include "VectorMatrixoverload.h"
#include <stack>
#include <cmath>
using namespace std;



using namespace std;

Vector2 operator/(const Vector2& U, const Vector2& V)
{
	int d = U.size();
	Vector2 W(d);
	for (int j = 0; j<d; j++)
	{
		W[j] = U[j] / V[j];
	}
	return W;
}


Vector2 operator+(const Vector2& U, const Vector2& V)
{
	int d = U.size();
	Vector2 W(d);
	for (int j = 0; j<d; j++)
	{
		W[j] = U[j] + V[j];
	}
	return W;
}


Vector2 operator-(const Vector2& U, const Vector2& V)
{
	int d = U.size();
	Vector2 W(d);
	for (int j = 0; j<d; j++)
	{
		W[j] = U[j] - V[j];
	}
	return W;
}

Vector2 operator/(const Vector2& U, const int N)
{
	int d = U.size();
	Vector2 W(d);
	for (int j = 0; j<d; j++) { W[j] = U[j] / N; }
	return W;
}
void print(Vector2& u)
{
	Vector2::iterator itr;
	for (itr = u.begin(); itr != u.end(); itr++) cout << *itr << endl;
};