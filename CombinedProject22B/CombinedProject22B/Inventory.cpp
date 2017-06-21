#include "Inventory.h"

Inventory::Inventory()
{
	ISBN = "0";
	title = "default";
	author = "default";
	publisher = "default";
	date_added = "default";
	quantity_onHand = 0;
	wholesale_cost = 0.0;
	retail_price = 0.0;
}

Inventory::Inventory(std::string ISBN_input, std::string title_input, std::string author_input, std::string publisher_input, std::string date_addedInput, int quantity_onHandInput, double wholesale_costInput, double retail_priceInput)
{
	ISBN = ISBN_input;
	title = title_input;
	author = author_input;
	publisher = publisher_input;
	date_added = date_addedInput;
	quantity_onHand = quantity_onHandInput;
	wholesale_cost = wholesale_costInput;
	retail_price = retail_priceInput;
}

//Not member functions!These are friend functions of class Inventory
std::ostream& operator<< (std::ostream &stream, Inventory &object1)
{
	stream << object1.ISBN << std::endl;
	stream << object1.title << std::endl;
	stream << object1.author << std::endl;
	stream << object1.publisher << std::endl;
	stream << object1.date_added << std::endl;
	stream << object1.quantity_onHand << std::endl;
	stream << object1.wholesale_cost << std::endl;
	stream << object1.retail_price << std::endl;

	return stream;
}

std::istream& operator>> (std::istream &stream, Inventory &object1)
{
	stream >> object1.ISBN;
	stream >> object1.title;
	stream >> object1.author;
	stream >> object1.publisher;
	stream >> object1.date_added;
	stream >> object1.quantity_onHand;
	stream >> object1.wholesale_cost;
	stream >> object1.retail_price;

	return stream;
}

bool operator== (Inventory &object1, )
{

}


void Inventory::setISBN(std::string input)
{
	ISBN = input;
}

void Inventory::setTitle(std::string input)
{
	title = input;
}

void Inventory::setAuthor(std::string input)
{
	author = input;
}

void Inventory::setPublisher(std::string input)
{
	publisher = input;
}

void Inventory::setDate_added(std::string input)
{
	date_added = input;
}

void Inventory::setQuatity_onHand(int input)
{
	quantity_onHand = input;
}

void Inventory::setWholesale_cost(double input)
{
	wholesale_cost = input;
}

void Inventory::setRetail_price(double input)
{
	retail_price = input;
}

std::string Inventory::getISBN()
{
	return ISBN;
}

std::string Inventory::getTitle()
{
	return title;
}

std::string Inventory::getAuthor()
{
	return author;
}

std::string Inventory::getPublisher()
{
	return publisher;
}

std::string Inventory::getDate_added()
{
	return date_added;
}

int Inventory::getQuantity_onHand()
{
	return quantity_onHand;
}

double Inventory::getWholesale_cost()
{
	return wholesale_cost;
}

double Inventory::getRetail_price()
{
	return retail_price;
}