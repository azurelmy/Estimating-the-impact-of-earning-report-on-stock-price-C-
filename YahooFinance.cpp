#include "stdafx.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include "PreForYahoo.h"
#include "YahooFinance.h"
#include <stdio.h>
#include "curl.h"
#include <stack>
#include <mutex>


using namespace std;

struct MemoryStruct {
	char *memory;
	size_t size;
};

void *myrealloc(void *ptr, size_t size)
{
	// There might be a realloc() out there that doesn't like reallocing
	// NULL pointers, so we take care of it here 
	if (ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}

int write_data2(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;

	mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}

std::mutex mu;

void downloadYahoo1(vector<stock> stocklist, map<string, StockPrice>* result) {
	cout << "Thread 1 downloading..." << endl;
	for (unsigned int i = 0; i < stocklist.size(); i++) {
		StockPrice temp(stocklist[i].getTicker());
		struct MemoryStruct data, data2;
		data.memory = NULL;
		data.size = 0;
		data2.memory = NULL;
		data2.size = 0;
		mu.lock();
		//create pointer of curl operation
		CURL *curl1;

		//set global variance
		curl_global_init(CURL_GLOBAL_ALL);

		//indicator that can be used to judge if opening url success or not
		CURLcode res1;
		//name of url

		//init
		curl1 = curl_easy_init();

		if (curl1) {
			int k = 0, l = 0;
			const char* url1 = stocklist[i].getStockUrl().c_str(); //assign url's address to a pointer
																   //cout << stocklist[i].getStockUrl().c_str() << endl;
																   //cout << url1 << endl;
			curl_easy_setopt(curl1, CURLOPT_URL, url1);
			curl_easy_setopt(curl1, CURLOPT_ENCODING, "");
			curl_easy_setopt(curl1, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(curl1, CURLOPT_WRITEDATA, (void *)&data);
			res1 = curl_easy_perform(curl1);

			stringstream sData; //by stringstream int and string can be easily exchanged
			sData.str(data.memory);
			string sValue;
			double dValue = 0;
			stack<double>temp1;
			for (string line; getline(sData, line); )//untill the endline 
			{
				//cout << line << endl;
				sValue = line.substr(line.find_last_of(',') + 1);
				//cout << sValue << endl;
				dValue = strtod(sValue.c_str(), NULL);
				//cout << dValue << endl;
				if (k>0 && dValue>0)
				{
					temp1.push(dValue);
				}
				k++;
			}
			while (!temp1.empty())
			{
				temp.getStockPrice().push_back(temp1.top());//when stack is not empty, add first latest element to last of class stack and remove the first from top. finally reverse the stack
				temp1.pop();
			}

			//get corresponding spy data
			const char* url2 = stocklist[i].getSpyUrl().c_str();

			curl_easy_setopt(curl1, CURLOPT_URL, url2);
			curl_easy_setopt(curl1, CURLOPT_ENCODING, "");
			curl_easy_setopt(curl1, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(curl1, CURLOPT_WRITEDATA, (void *)&data2);
			res1 = curl_easy_perform(curl1);

			stringstream sData2;
			sData2.str(data2.memory);
			string sValue2;
			double dValue2 = 0;
			stack<double>temp2;
			for (string line; getline(sData2, line); )
			{
				sValue2 = line.substr(line.find_last_of(',') + 1);
				dValue2 = strtod(sValue2.c_str(), NULL);
				if (l>0 && dValue>0)
				{
					temp2.push(dValue2);
				}
				l++;
			}
			while (!temp2.empty())
			{
				temp.getSpyPrice().push_back(temp2.top());
				temp2.pop();
			}

			//check abnormal data
			if (temp.getStockPrice().size() != 91) {
				cout << temp.getTicker() << " " << temp.getStockPrice().size() << endl;
			}
		}
		//mu.lock();
		result->insert(pair<string, StockPrice>(stocklist[i].getTicker(), temp));
		//mu.unlock();
		if (res1 == CURLE_OK)
		{
			curl_easy_cleanup(curl1);
			curl_global_cleanup();
		}
		mu.unlock();
	}
	cout << "Thread 1 download Complete." << endl;
}

void downloadYahoo2(vector<stock> stocklist, map<string, StockPrice>* result) {
	cout << "Thread 2 downloading..." << endl;
	for (unsigned int i = 0; i < stocklist.size(); i++) {
		StockPrice temp(stocklist[i].getTicker());
		struct MemoryStruct data, data2;
		data.memory = NULL;
		data.size = 0;
		data2.memory = NULL;
		data2.size = 0;
		mu.lock();
		//create pointer of curl operation
		CURL *curl2;

		//set global variance
		curl_global_init(CURL_GLOBAL_ALL);

		//indicator that can be used to judge if opening url success or not
		CURLcode res2;
		//name of url

		//init
		curl2 = curl_easy_init();

		if (curl2) {
			int k = 0, l = 0;
			const char* url1 = stocklist[i].getStockUrl().c_str(); //assign url's address to a pointer
			curl_easy_setopt(curl2, CURLOPT_URL, url1);
			curl_easy_setopt(curl2, CURLOPT_ENCODING, "");
			curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(curl2, CURLOPT_WRITEDATA, (void *)&data);
			res2 = curl_easy_perform(curl2);

			stringstream sData; //by stringstream int and string can be easily exchanged
			sData.str(data.memory);
			string sValue;
			double dValue = 0;
			stack<double>temp1;
			for (string line; getline(sData, line); )//untill the endline 
			{
				//cout << line << endl;
				sValue = line.substr(line.find_last_of(',') + 1);
				//cout << sValue << endl;
				dValue = strtod(sValue.c_str(), NULL);
				//cout << dValue << endl;
				if (k>0 && dValue>0)
				{
					temp1.push(dValue);
				}
				k++;
			}
			while (!temp1.empty())
			{
				temp.getStockPrice().push_back(temp1.top());//when stack is not empty, add first latest element to last of class stack and remove the first from top. finally reverse the stack
				temp1.pop();
			}

			//get corresponding spy data
			const char* url2 = stocklist[i].getSpyUrl().c_str();

			curl_easy_setopt(curl2, CURLOPT_URL, url2);
			curl_easy_setopt(curl2, CURLOPT_ENCODING, "");
			curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(curl2, CURLOPT_WRITEDATA, (void *)&data2);
			res2 = curl_easy_perform(curl2);

			stringstream sData2;
			sData2.str(data2.memory);
			string sValue2;
			double dValue2 = 0;
			stack<double>temp2;
			for (string line; getline(sData2, line); )
			{
				sValue2 = line.substr(line.find_last_of(',') + 1);
				dValue2 = strtod(sValue2.c_str(), NULL);
				if (l>0 && dValue>0)
				{
					temp2.push(dValue2);
				}
				l++;
			}
			while (!temp2.empty())
			{
				temp.getSpyPrice().push_back(temp2.top());
				temp2.pop();
			}

			//check abnormal data
			if (temp.getStockPrice().size() != 91) {
				cout << temp.getTicker() << " " << temp.getStockPrice().size() << endl;
			}
		}
		//mu.lock();
		result->insert(pair<string, StockPrice>(stocklist[i].getTicker(), temp));
		//mu.unlock();
		if (res2 == CURLE_OK)
		{
			curl_easy_cleanup(curl2);
			curl_global_cleanup();
		}
		mu.unlock();
	}
	cout << "Thread 2 download Complete." << endl;
}

void downloadYahoo3(vector<stock> stocklist, map<string, StockPrice>* result) {
	cout << "Thread 3 downloading..." << endl;
	for (unsigned int i = 0; i < stocklist.size(); i++) {
		StockPrice temp(stocklist[i].getTicker());
		struct MemoryStruct data, data2;
		data.memory = NULL;
		data.size = 0;
		data2.memory = NULL;
		data2.size = 0;
		mu.lock();
		//create pointer of curl operation
		CURL *curl3;

		//set global variance
		//curl_global_init(CURL_GLOBAL_ALL);

		//indicator that can be used to judge if opening url success or not
		CURLcode res3;
		//name of url

		//init
		curl3 = curl_easy_init();

		if (curl3) {
			int k = 0, l = 0;
			const char* url1 = stocklist[i].getStockUrl().c_str(); //assign url's address to a pointer
																   //cout << stocklist[i].getStockUrl().c_str() << endl;
																   //cout << url1 << endl;
			curl_easy_setopt(curl3, CURLOPT_URL, url1);
			curl_easy_setopt(curl3, CURLOPT_ENCODING, "");
			curl_easy_setopt(curl3, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(curl3, CURLOPT_WRITEDATA, (void *)&data);
			res3 = curl_easy_perform(curl3);

			stringstream sData; //by stringstream int and string can be easily exchanged
			sData.str(data.memory);
			string sValue;
			double dValue = 0;
			stack<double>temp1;
			for (string line; getline(sData, line); )//untill the endline 
			{
				//cout << line << endl;
				sValue = line.substr(line.find_last_of(',') + 1);
				//cout << sValue << endl;
				dValue = strtod(sValue.c_str(), NULL);
				//cout << dValue << endl;
				if (k>0 && dValue>0)
				{
					temp1.push(dValue);
				}
				k++;
			}
			while (!temp1.empty())
			{
				temp.getStockPrice().push_back(temp1.top());//when stack is not empty, add first latest element to last of class stack and remove the first from top. finally reverse the stack
				temp1.pop();
			}

			//get corresponding spy data
			const char* url2 = stocklist[i].getSpyUrl().c_str();

			curl_easy_setopt(curl3, CURLOPT_URL, url2);
			curl_easy_setopt(curl3, CURLOPT_ENCODING, "");
			curl_easy_setopt(curl3, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(curl3, CURLOPT_WRITEDATA, (void *)&data2);
			res3 = curl_easy_perform(curl3);

			stringstream sData2;
			sData2.str(data2.memory);
			string sValue2;
			double dValue2 = 0;
			stack<double>temp2;
			for (string line; getline(sData2, line); )
			{
				sValue2 = line.substr(line.find_last_of(',') + 1);
				dValue2 = strtod(sValue2.c_str(), NULL);
				if (l>0 && dValue>0)
				{
					temp2.push(dValue2);
				}
				l++;
			}
			while (!temp2.empty())
			{
				temp.getSpyPrice().push_back(temp2.top());
				temp2.pop();
			}

			//check abnormal data
			if (temp.getStockPrice().size() != 91) {
				cout << temp.getTicker() << " " << temp.getStockPrice().size() << endl;
			}
		}
		//mu.lock();
		result->insert(pair<string, StockPrice>(stocklist[i].getTicker(), temp));
		//mu.unlock();
		if (res3 == CURLE_OK)
		{
			curl_easy_cleanup(curl3);
			//curl_global_cleanup();
		}
		mu.unlock();
	}
	cout << "Thread 3 download Complete." << endl;
}