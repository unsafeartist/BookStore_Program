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
	fileObject.open("test.txt", std::ios::in); // opening file in input mode
	double cost = 0;
	if (or == 1)
	{
		int index;
		for (index = 0; index < total; index++)
		{
			if (array[index].getTitle() == term) break;
		}
		//else{
		//std::cout << "book doesnt exist \n" << endl;
		//}
		array[index].setQuatity_onHand(array[index].getQuantity_onHand() - quan);
		cost = array[index].getRetail_price()*quan + (array[index].getRetail_price()*quan*0.0725);
		std::cout << "You are buying " << quan << " copies of " << array[index].getTitle() << " costing $" << cost << std::endl;
		if (array[index].getQuantity_onHand() == 0)
		{
			while (index != total)
			{
				array[index] = array[index + 1];
				index++;
			}
		}
	}
	if (or == 2)
	{
		int index;
		for (index = 0; index < total; index++)
		{
			if (array[index].getISBN() == term) break;
		}
		array[index].setQuatity_onHand(array[index].getQuantity_onHand() - quan);
		cost = array[index].getRetail_price()*quan + (array[index].getRetail_price()*quan*0.0725);
		std::cout << "You are buying " << quan << " copies of " << array[index].getTitle() << " costing $" << cost << std::endl;
		if (array[index].getQuantity_onHand() == 0)
		{
			while (index != total)
			{
				array[index] = array[index + 1];
				index++;
			}
		}

	}
	//close
	/*remove("test.txt");	//coudlnt get the print out to another file working
	std::fstream newFileObject;
	newFileObject.open("test.txt", std::ios::out); // opening file in input mode
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
	}*/
}

Cashier::~Cashier()
{
}