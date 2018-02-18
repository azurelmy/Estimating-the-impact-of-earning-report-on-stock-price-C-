#pragma once
#ifndef YahooFinance_h
#define YahooFinance_h

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include "PreForYahoo.h"

using namespace std;

class StockPrice {
private:
	string ticker;
	vector<double> stockPrice;
	vector<double> spyPrice;

public:
	StockPrice() {}
	StockPrice(string ticker_) :ticker(ticker_) {}
	string& getTicker() {
		return ticker;
	}
	vector<double>& getStockPrice() {
		return stockPrice;
	}
	vector<double>& getSpyPrice() {
		return spyPrice;
	}
	void printInfo(StockPrice &stockprice) {
		for (unsigned int i = 0; i < stockPrice.size(); i++) {
			cout << stockPrice[i] << endl;
		}
	}
};

void downloadYahoo1(vector<stock> stocklist, map<string, StockPrice>* result);
void downloadYahoo2(vector<stock> stocklist, map<string, StockPrice>* result);
void downloadYahoo3(vector<stock> stocklist, map<string, StockPrice>* result);

#endif

