#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "ReadBloombergInfo.h"
#include "stdafx.h"

using namespace std;


vector<DownloadInfo> getData(){
	cout << "Reading Data..." << endl;
	ifstream file("Data FRE.csv");
	vector<DownloadInfo> downloadResult;
	string line;
	string ticker;
	double BEst;
	double EPSAdj;
	string date;

	//string useless;
	//int count = 1;
	vector<string> deal;
	while (getline(file, line)) {
		//read ticker line
		ticker = line;
		//skip the nonsense date
		getline(file, line);
		//read BEst data
		//could make this process as a function, task for Zhang
		getline(file, line);
		stringstream ss1(line);
		string token;
		deal.clear();
		while (getline(ss1, token, ','))
		{
			deal.push_back(token);
		}
	    BEst = atof(deal[1].c_str());

		//read actual EPS data
		getline(file, line);
		stringstream ss2(line);
		deal.clear();
		while (getline(ss2, token, ','))
		{
			deal.push_back(token);
		}
		EPSAdj = atof(deal[1].c_str());

		//get report date
		getline(file, line);
		stringstream ss3(line);
		deal.clear();
		while (getline(ss3, token, ','))
		{
			deal.push_back(token);
		}
		date = deal[1].substr(4, 4) + deal[1].substr(0, 4);


		//skip NA line
		getline(file, line);

		//save info
		DownloadInfo temp(ticker, BEst, EPSAdj, date);
		downloadResult.push_back(temp);
		//cout << temp.getticker() << " " << temp.getBEst() << " " << temp.getEPSAdj() << " " << temp.getmonthAndDay() << " " << count << endl;
		//count++;
	}
	cout << "Data read." << endl;
	return downloadResult;
}

//divide vector of DownloadInfo into 3 groups by bar
dividedGroup partitionTo3Group(vector<DownloadInfo> v, double bar) {
	dividedGroup group(3);
	srand(time(NULL));
	set<int> chosenNumbers;
	int temp = 1,chance=0;
	set<int>::iterator itr;
	int count1 = 0, count2 = 0, count3 = 0;
	while(temp==1) {
		int j = rand() % 453;//we have 453 stocks in Data FRE.csv
		for (itr = chosenNumbers.begin(); itr != chosenNumbers.end(); itr++) {
			if (*itr == j) { break; }
			if (itr == chosenNumbers.end()) { chance = 1; }
		}
		if(chance=1){
				chosenNumbers.insert(j);
				if (v[j].getchangePercent() < -bar) {
					if (count1 < 40) {
						group[0].push_back(v[j]);
						count1++;
					}
				}
				else if (v[j].getchangePercent() >= -bar && bar >= v[j].getchangePercent()) {
					if (count2 < 40) {
						group[1].push_back(v[j]);
						count2++;
					}
				}
				else if (v[j].getchangePercent() > bar) {
					if (count3 < 40) {
						group[2].push_back(v[j]);
						count3++;
					}
				}
				chance = 0;
		}
		if (count1 == 40 && count2 == 40 && count3 == 40) {
			temp = 0;
		}
	}
	return group;
}