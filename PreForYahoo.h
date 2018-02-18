#pragma once
#ifndef PreForYahoo_h
#define PreForYahoo_h

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include "ReadBloombergInfo.h"
using namespace std;

class stock{
private:
	string ticker;
	int index;
	string startDate;
	string endDate;
	string stockUrl;
	string spyUrl;
	const static vector<string> indexlist;
public:
	stock() {}
	stock(DownloadInfo info_);
	string& getStockUrl() {
		return stockUrl;
	}
	string& getSpyUrl() {
		return spyUrl;
	}
	string& getTicker() {
		return ticker;
	}
};

vector<string> index();

vector<stock> stockStorage(vector<DownloadInfo> v);

#endif
