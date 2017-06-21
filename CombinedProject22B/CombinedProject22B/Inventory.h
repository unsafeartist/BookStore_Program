#ifndef _INVENTORY_H_ //Add Guard
#define _INVENTORY_H_ //Definition

#include <string> 
#include <iostream>

class Inventory
{
	private:
		std::string ISBN;
		std::string title, author, publisher, date_added;
		int quantity_onHand;
		double wholesale_cost, retail_price;
	public:
		//Constructors
		Inventory();
		Inventory(std::string ISBN_input, std::string title_input, std::string author_input, std::string publisher_input, std::string date_addedInput, int quantity_onHandInput, double wholesale_costInput, double retail_priceInput);

		//Setter and getter functions should be below
		void setISBN(std::string input);
		void setTitle(std::string input);
		void setAuthor(std::string input);
		void setPublisher(std::string input);
		void setDate_added(std::string input);
		void setQuatity_onHand(int input);
		void setWholesale_cost(double input);
		void setRetail_price(double input);
		std::string getISBN();
		std::string getTitle();
		std::string getAuthor();
		std::string getPublisher();
		std::string getDate_added();
		int getQuantity_onHand();
		double getWholesale_cost();
		double getRetail_price();

		//Operator<< overload to be able to print entire object
		//In plain-english I allowed the "<<" operator to be used on
		//an object instantiated from Inventory class, meaning
		//I am able to print an entire object using "cout << object"
		//P.S - Not a member function
		friend std::ostream& operator<< (std::ostream &stream, Inventory &object1);

		//Operator overload for istream operator
		friend std::istream& operator>> (std::istream &stream, Inventory &object1);

		//Operator overload for ==
		friend bool operator== (Inventory &object1, Inventory &object2);


};

#endif