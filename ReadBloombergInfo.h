#pragma once
#ifndef ReadBloombergInfo_h
#define ReadBloombergInfo_h
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <cstring>

using namespace std;

//read data in excel downloaded from Bloomberg
class DownloadInfo {
private:
	string ticker;
	double BEst;
	double EPSAdj;
	double changePercent;
	string date;

public:
	DownloadInfo() {};
	DownloadInfo(string ticker_, double BEst_, double EPSAdj_, string date_) {
		size_t fi = ticker_.find_first_of(" ");
		ticker = ticker_.substr(0, fi);
		BEst = BEst_;
		EPSAdj = EPSAdj_;
		changePercent = (EPSAdj - BEst) / BEst*100.0;
		date = date_;
	}
	string getticker() {
		return ticker;
	}
	double getBEst() {
		return BEst;
	}
	double getEPSAdj() {
		return EPSAdj;
	}
	double getchangePercent() {
		return changePercent;
	}
	string getdate() {
		return date;
	}
};

vector<DownloadInfo> getData();

typedef vector<vector<DownloadInfo>> dividedGroup;

dividedGroup partitionTo3Group(vector<DownloadInfo> v, double bar = 5.0);

#endif

