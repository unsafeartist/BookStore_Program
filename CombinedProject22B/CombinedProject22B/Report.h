#pragma once

#ifndef Report_H
#define Report_H

#include <string>
#include <fstream>
#include "Inventory.h"

class Report : public Inventory
{
	std::string ISBN, title, author, publisher, date_added;
	int quantity_onHand;
	double wholesale_cost, retail_price;
	

	double wholeV, retailV;					//all of whole sale and all of retail
	int total;
	//the total number of books
	
	
public:
	Report();
	//Report::Report(std::string ISBN_input, std::string title_input, std::string author_input, std::string publisher_input, std::string date_addedInput, int quantity_onHandInput, double wholesale_costInput, double retail_priceInput, int total); // , Report array[]);//, Report array[]);
	void sortByQuan(int max, Report array[], int counter);
	void sortByPrice(int max, Report array[], int counter);
	int compareDate(std::string a, std::string b);
	void sortByDate(int max, Report array[], int counter);
	void getList(int t, Report array[], int counter);
	void setWholeSaleValue(int t, Report array[], int counter);
	double getWholeSaleValue(int t, Report array[], int counter);
	void setRetailValue(int t, Report array[], int counter);
	double getRetailValue(int t, Report array[], int counter);
	void sortQuan(int t, Report array[], int counter);
	void sortCost(int t, Report array[], int counter);
	void sortAge(int t, Report array[], int counter);

	//void Report::setTitle(std::string input)

	~Report();
};

#endif
