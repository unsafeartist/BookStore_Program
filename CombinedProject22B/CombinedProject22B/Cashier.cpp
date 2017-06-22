#include "Cashier.h"
#include "Report.h"
#include "Inventory.h"
#include <iomanip>
//make a getAllBook array
//prompt user for book title or isbn and quantity they want to buy,
//search the array and make changes to .quantity_onHand or retail_price
//tell user how much they bought it for
//delete the current inventory text file
//print the changed array onto a new text file that is named the same name as the previous text file
//calculate the total price of purchase and print it

Cashier::Cashier()
{
}


void Cashier::searchBuy(Report array[], std::string term, int total, int or, int quan) //replace cashier's method with this method
//(the parameters explained) array, the title/isbn that user wants to buy, total amount of books, int deciding to search by isbn or title, the amount of books of that title the user wants to buy
{
	std::cout << std::setprecision(4);
	std::fstream fileObject;
	fileObject.open("Inventory.txt", std::ios::in);    // opening file in input mode
	double cost = 0;
	int valid = 0;
	if (or == 1)
	{
		int index;
		for (index = 0; index < total; index++)    // matches the user entered title or isbn to the corresponding object holding it's information
		{
			if (array[index].getTitle() == term)
			{
				break;
			}
			valid++;
		}
		if (valid == total)   //makes sure the book exists before calculating
		{
			std::cout << "This book does not exist" << std::endl;
		}
		else
		{


			if (array[index].getQuantity_onHand() < quan)         //Makes sure that user does not try to buy more books than are in stock  
			{
				std::cout << "You are trying to buy more books than are in stock!" << std::endl;
		}
			else
			{

		array[index].setQuatity_onHand(array[index].getQuantity_onHand() - quan);// subtracts the quantity the user wants to buy from the quantity on hand and sets that as new quantity
		cost = array[index].getRetail_price()*quan + (array[index].getRetail_price()*quan*0.0725); // calculates the cost of the books user is buying
		std::cout << "You are buying " << quan << " copies of " << array[index].getTitle() << " costing $" << cost << std::endl;// displays to user how many copies they bought and for how much
		if (array[index].getQuantity_onHand() == 0)
		{
			while (index != total)
			{
						array[index] = array[index + 1];       //shifts the array elements up one so that when new file is written the book is deleted
				index++;
			}
		}
	}
		}
	}


	if (or == 2)
	{
		int index;
		for (index = 0; index < total; index++)
		{
		if (array[index].getISBN() == term)
			{
				break;
			}
			valid++;
		}
		if (valid == total)   //makes sure the book exists before calculating
			{
			std::cout << "This book does not exist" << std::endl;
			}
		else
			{
			if (array[index].getQuantity_onHand() < quan)  //Makes sure that user does not try to buy more books than are in stock  
			{
				std::cout << "You are trying to buy more books than are in stock!" << std::endl;
		}

		if (array[index].getQuantity_onHand() < quan)  //Makes sure that user does not try to buy more books than are in stock  
		{
			std::cout << "You are trying to buy more books than are in stock!" << std::endl;  
		}
		else
		{

		array[index].setQuatity_onHand(array[index].getQuantity_onHand() - quan);                                     //does same things as the previous logic if they chose to search by book
		cost = array[index].getRetail_price()*quan + (array[index].getRetail_price()*quan*0.0725);
		std::cout << "You are buying " << quan << " copies of " << array[index].getTitle() << " costing $" << cost << std::endl;
		if (array[index].getQuantity_onHand() == 0)
		{
			while (index != total)
			{
						array[index] = array[index + 1];    //shifts the array elements up one so that when new file is written the book is deleted
				index++;
			}
		}
		}

	}
	fileObject.close();     //closing the file before it is removed
	remove("Inventory.txt");	//removes file
	std::fstream newFileObject;
	newFileObject.open("Inventory.txt", std::ios::out); // opening file in input mode
	
	for (int y = 0; y < total; y++) //makes the new file have all updated information about books being bought
	{
	newFileObject << array[y].getISBN() << std::endl;
	newFileObject << array[y].getTitle() << std::endl;
	newFileObject << array[y].getAuthor() << std::endl;
	newFileObject << array[y].getPublisher() << std::endl;
	newFileObject << array[y].getDate_added() << std::endl;
	newFileObject << array[y].getQuantity_onHand() << std::endl;
	newFileObject << array[y].getWholesale_cost() << std::endl;
	newFileObject << array[y].getRetail_price() << std::endl;
	newFileObject << "" << std::endl; // puts the whitespace inbetween each book for the new file
	}
}

Cashier::~Cashier()
{
}