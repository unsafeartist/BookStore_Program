#pragma once

#ifndef Cashier_H
#define Cashier_H

#include <string>
#include <fstream>
#include "Inventory.h"
#include "Report.h"

class Cashier : public Report
{
	std::string ISBN, title, author, publisher, date_added;
	int quantity_onHand;
	double wholesale_cost, retail_price;

public:
	Cashier();
	void searchBuy(Report array[], std::string term, int total, int or, int quan);
	~Cashier();
};

#endif