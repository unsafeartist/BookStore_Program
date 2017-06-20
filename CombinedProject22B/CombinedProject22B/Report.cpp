#include "Report.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>


std::ifstream test;

Report::Report()
{
	ISBN = "0";
	title = "default";
	author = "default";
	publisher = "default";
	date_added = "default";
	quantity_onHand = 0;
	wholesale_cost = 0.0;
	retail_price = 0.0;
	wholeV = 0;
	retailV = 0;
}


void Report::getList(int total, Report array[], int counter)		//returns the full list of book details
{
	std::cout << array[counter].getISBN() << std::endl;
	std::cout << array[counter].getTitle() << std::endl;
	std::cout << array[counter].getAuthor() << std::endl;
	std::cout << array[counter].getPublisher() << std::endl;
	std::cout << array[counter].getDate_added() << std::endl;
	std::cout << array[counter].getQuantity_onHand() << std::endl;
	std::cout << array[counter].getWholesale_cost() << std::endl;
	std::cout << array[counter].getRetail_price() << std::endl;
}
void Report::setWholeSaleValue(int total, Report array[], int counter)		//adds the value of all the whole sale costs added together
{
	std::cout << array[counter].getTitle() << "	" << "$" << array[counter].getQuantity_onHand()*array[counter].getWholesale_cost() << std::endl;
	wholeV += array[counter].getQuantity_onHand()*array[counter].getWholesale_cost();
}
double Report::getWholeSaleValue(int total, Report array[], int counter)		// returns a list of all the whole sale cost
{
	setWholeSaleValue(total, array, counter);
	return wholeV;
}
void Report::setRetailValue(int total, Report array[], int counter)			//returns the value of all the retail values added up
{
		std::cout << array[counter].getTitle() << "	" << "$" << array[counter].getQuantity_onHand()*array[counter].getRetail_price() << std::endl;
		retailV += array[counter].getQuantity_onHand()*array[counter].getRetail_price();
}
double Report::getRetailValue(int total, Report array[], int counter)		//returns a list of all the retail values
{
	setRetailValue(total, array, counter);
	return retailV;
}
void Report::sortQuan(int total, Report array[], int counter)		//prints out the list of all the sorted quantity_onHands
{
	sortByQuan(total, array, counter);
	std::cout << array[counter].getQuantity_onHand() << " of " << array[counter].getTitle() << std::endl;
}

void Report::sortByQuan(int max, Report array[], int counter)			//sorts all the books by quantity_onHands
{
	for (int x = 0; x < max; x++)
	{
		double min = array[counter].getQuantity_onHand();
		int index = counter;
		for (int y = counter; y < max; y++)
		{
			if (array[y].getQuantity_onHand() < min)
			{
				min = array[y].getQuantity_onHand();
				index = y;
			}
		}
		Report temp = array[counter];
		array[counter] = array[index];
		array[index] = temp;
	}
}

void Report::sortCost(int total, Report array[], int counter)							//prints out all the sorted whole sale prices
{
	sortByPrice(total, array, counter);
	std::cout << array[counter].getTitle() << " $" << array[counter].getWholesale_cost() << std::endl;
}
void Report::sortByPrice(int max, Report array[], int counter)		//sorts all the books by whole sale price
{
	for (int x = 0; x < max; x++)
	{
		double min = array[counter].getWholesale_cost();
		int index = counter;
		for (int y = counter; y < max; y++)
		{
			if (array[y].getWholesale_cost() < min)
			{
				min = array[y].getWholesale_cost();
				index = y;
			}
		}
		Report temp = array[counter];
		array[counter] = array[index];
		array[index] = temp;
	}
}

int Report::compareDate(std::string a, std::string b)		//compares 2 years then if the 2nd is bigger than the 1st it compares the 2 months, if the 2nd month is bigger than the first, it compares the 2 days
{
	std::string aYear = a.substr(7, 4);						//mm/dd/yyyy
	std::string aMonth = a.substr(2);
	std::string aDay = a.substr(4, 2);
	std::string bYear = b.substr(7, 4);
	std::string bMonth = b.substr(2);
	std::string bDay = b.substr(4, 2);
	if (aYear < bYear)
	{
		return 1;
	}
	else if (bYear < aYear)
	{
		return -1;
	}
	else
	{
		if (aMonth < bMonth)
		{
			return 1;
		}
		else if (bMonth < aMonth)
		{
			return -1;
		}
		else
		{
			if (aDay < bDay)
			{
				return 1;
			}
			else if (bDay < aDay)
			{
				return -1;
			}
		}
	}
	return 0;
}


void Report::sortByDate(int max, Report array[], int counter)		//sorts the date_addeds using the compareDate
{
	for (int x = 0; x < max; x++)
	{
		std::string curr = array[counter].getDate_added();
		int index = counter;
		for (int y = counter + 1; y < max; y++)
		{
			if (compareDate(curr, array[y].getDate_added()) == -1)
			{
				curr = array[y].date_added;
				index = y;
			}
		}
		Report temp = array[counter];
		array[counter] = array[index];
		array[index] = temp;
	}
}
void Report::sortAge(int total, Report array[], int counter)			//prints out all the sorted books by age in Reporttory
{
	sortByDate(total, array, counter);
	std::cout << array[counter].getTitle() << " purchased on " << array[counter].getDate_added() << std::endl;
}

Report::~Report()
{
}



