#include "Cashier.h"
#include "Report.h"
#include "Inventory.h"

//make a getAllBook array
//prompt user for book title, isbn, and quantity of books the user wants to buy
//search the array and make changes to .quantity_onHand or retail_price
//delete the current invenotry text file
//print the changed array onto a new text file that is named the same name as the previous text file
//calculate the total price of purchase and print it

Cashier::Cashier()
{
}

void Cashier::searchBuy(Report array[], std::string term, int total, int or, int quan)
{
	std::fstream fileObject;
	fileObject.open("Inventory.txt", std::ios::in); // opening file in input mode
	double cost = 0;
	if (or == 1)
	{
		int index;
		for (index = 0; index < total; index++)
		{
			if (array[index].getTitle == term) break;
		}
		array[index].setQuatity_onHand(array[index].getQuantity_onHand() - quan);
		cost = array[index].getRetail_price()*array[index].getQuantity_onHand() + (array[index].getRetail_price()*array[index].getQuantity_onHand()*0.0725);
		std::cout << "You are buying " << array[index].getQuantity_onHand() << "copies of " << array[index].getTitle << "costing $" << cost << std::endl;
	}
	if (or == 2)
	{
		int x;
		for (x = 0; x < total; x++)
		{
			if (array[x].getISBN == term) break;
		}
		array[x].setQuatity_onHand(array[x].getQuantity_onHand() - quan);
		cost = array[x].getRetail_price()*array[x].getQuantity_onHand() + (array[x].getRetail_price()*array[x].getQuantity_onHand()*0.0725);
		std::cout << "You are buying " << array[x].getQuantity_onHand() << "copies of " << array[x].getTitle << "costing $" << cost << std::endl;
	}
	remove("Inventory.txt");
	std::fstream newFileObject;
	newFileObject.open("Inventory.txt", std::ios::out); // opening file in output mode
	for (int y = 0; y < total; y++)
	{
		newFileObject << array[y].getISBN() << std::endl;
		newFileObject << array[y].getTitle() << std::endl;
		newFileObject << array[y].getAuthor() << std::endl;
		newFileObject << array[y].getPublisher() << std::endl;
		newFileObject << array[y].getDate_added() << std::endl;
		newFileObject << array[y].getQuantity_onHand() << std::endl;
		newFileObject << array[y].getWholesale_cost() << std::endl;
		newFileObject << array[y].getRetail_price() << std::endl;
	}
}


Cashier::~Cashier()
{
}
