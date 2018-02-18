#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include "PreForYahoo.h"
#include "ReadBloombergInfo.h"
#include "stdafx.h"

using namespace std;

//get trading days from 07012016 to 03312017
vector<string> index() {
	ifstream file("TradingDate.txt");
	vector<string> result;
	string line;
	while (getline(file, line)) {
		result.push_back(line);
	}
	return result;
}

//int j = 0;

stock::stock(DownloadInfo info_) {
	for (unsigned int i = 0; i < indexlist.size(); i++) {
		if (info_.getdate() == indexlist[i]) {
			index = i;
			break;
		}
		/*check whether the earning date is a trading day
		if (i == 180) {
			cout << j << "Aha! Earning date not in trading day! " << info.getticker() << endl;
			j++;
		}
		*/
	}
	ticker = info_.getticker();
	startDate = indexlist[index + 30];
	endDate = indexlist[index - 60];
	stockUrl = string("http://real-chart.finance.yahoo.com/table.csv?s=") + ticker
		+ string("&a=") + to_string(atoi(startDate.substr(0, 2).c_str()) - 1) + string("&b=") + startDate.substr(2, 2)
		+ string("&c=2016&g=d") + string("&d=") + to_string(atoi(endDate.substr(0, 2).c_str()) - 1) + string("&e=")
		+ endDate.substr(2, 2) + string("&f=") + endDate.substr(4, 4) + string("&ignore=.csv");
	spyUrl = string("http://real-chart.finance.yahoo.com/table.csv?s=") + "SPY"
		+ string("&a=") + to_string(atoi(startDate.substr(0, 2).c_str()) - 1) + string("&b=") + startDate.substr(2, 2)
		+ string("&c=2016&g=d") + string("&d=") + to_string(atoi(endDate.substr(0, 2).c_str()) - 1) + string("&e=")
		+ endDate.substr(2, 2) + string("&f=") + endDate.substr(4, 4) + string("&ignore=.csv");
}

vector<string> indexlist1 = index();
const vector<string> stock::indexlist = indexlist1;

vector<stock> stockStorage(vector<DownloadInfo> v) {
	vector<stock> result;
	for (unsigned int i = 0; i < v.size(); i++) {
		stock temp = stock(v[i]);
		result.push_back(temp);
	}
	return result;
}

