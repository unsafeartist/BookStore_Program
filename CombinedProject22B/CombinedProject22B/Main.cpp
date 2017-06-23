//Authors Kamal, Leander, George, Jessie
//Fixing Errors copy from Master

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stdio.h> // to remove rename files
#include "Report.h"
#include "Inventory.h"
#include "Cashier.h"
using namespace std;

//Inventory Module Prototypes
int search(string search_value, string file_name);
void deleteBook(string book_name, string file_name); // function for deleting books
bool getBook(Inventory &obj, string book, string file_name, int type); // function for extracting book

void editABook(string file_name, string term2replace, string with);// edit a book function
void addBook(string fileName, string isbn, string title, string author, string publisher, string date_added, int quantity, double wholesaleCost, double retailPrice);
bool deleteBookJune21(string file_name, string inputISBN_Title, int whichOne);

bool DeleteBook(string file_name, string isbn_title, int which); // just another delete book :P


//Report Module Protoypes
int totalBook();
void getAllBook(std::string file_name, int total, Report object[]);
void sortQuan(Report testing[]);
void sortByQuan(Report array[], int max);

//Create "Inventory" object for storing book data we extract from inventory.txt file
Inventory bookData;

int main()
{
	//Change the color of the GUI window(command prompt) for user
	system("color 3F");

	//NOTE: std::cout just because compiler complains about cout being ambigous

	//Variable for if they want to run the entire program again
	char main_again = 'n';
	
	//Declare variables for main menu
	int main_choice;

	do
	{
		//Reset main_again option
		main_again = 'n';

	//Main Menu
	std::cout << "Boring Booksellers" << endl;
		std::cout << "    Main Menu    " << endl;
	std::cout << "1) Cashier Module" << endl;
	std::cout << "2) Inventory Database Module" << endl;
	std::cout << "3) Report Module" << endl;
	std::cout << "4) Exit" << endl;
	std::cout << endl << "Please enter your choice: ";
	std::cin >> main_choice;
		cout << endl; //For aesthetics

	//Validate main choice to be between 1-4 and numerical
	while (std::cin.fail() || (main_choice < 1) || (main_choice > 4))
	{
			std::cout << "Invalid input! Please enter a number between 1 and 4" << endl;
		std::cin.clear();
		std::cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		std::cin >> main_choice;
	} 
	
		//This should be first, to be more efficient
		if (main_choice == 4)
		{
			break;
		}
	
	//If user chooses report module then execute following code
	if (main_choice == 3)
	{
		//REPORT MODULE CODE BELOW
		//ALL CODE FOR REPORT MODULE BELOW
		int total = totalBook();
		Report testing[50];
		getAllBook("Inventory.txt", total, testing);

		//Display main Report menu to user and get their decision
		int decide = 0;
		std::cout << "-------REPORT MODULE-------" << endl;
		std::cout << "	1.List of All Books" << endl;
		std::cout << "	2.Report Whole Sale" << endl;
		std::cout << "	3.Report Retail Value" << endl;
		std::cout << "	4.List by Quantity" << endl;
		std::cout << "	5.List by Cost" << endl;
		std::cout << "	6.List by Age" << endl;
		std::cout << "	7.Return to Main Menu" << endl;
		std::cout << "Please enter your decision: ";
		cin >> decide;
		cout << endl; //for aesthetics

		// validation for decide ( checking to see if decision is between 0 and 7 )
		while (std::cin.fail() || (decide < 1) || (decide > 7))
		{
			std::cout << "Invalid input! Please make sure your choice is a number between 1 and 7" << endl;
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
			std::cin >> decide;
		}
		
			if (decide == 7)
			{
				main_again = 'y'; //This will return to MAIN PROGRAM MENU
			}

		while (decide != 7) //if the exit case is not true
		{
			if (decide == 1){
				//std::cout << "ISBN\tTitle\tAuthor	Publisher	Date		Quantity	Whole Sale Cost	Retail Price" << std::endl;
				for (int x = 0; x < total; x++)
				{
					testing[x].getList(total, testing, x);
				}
			}
			if (decide == 2){
				double temp = 0.0;
				for (int x = 0; x < total; x++)
				{
					temp += testing[x].getWholeSaleValue(total, testing, x);
				}
				std::cout << "the total wholesale value is $" << temp << std::endl;
			}
			if (decide == 3){
				double temp = 0.0;
				for (int x = 0; x < total; x++)
				{
					temp += testing[x].getRetailValue(total, testing, x);
				}
				std::cout << "the total retail value is $" << temp << std::endl;
			}
			if (decide == 4){
				for (int x = 0; x < total; x++)
				{
					testing[x].sortQuan(total, testing, x);
				}
			}
			if (decide == 5){
				for (int x = 0; x < total; x++)
				{
					testing[x].sortCost(total, testing, x);
				}
			}
			if (decide == 6){
				for (int x = 0; x < total; x++)
				{
					testing[x].sortAge(total, testing, x);
				}
			}


			//Skip lines for aesthetics
			cout << endl << endl;

			//Ask user if they would like to run the Report Module again
			string reportAgain_choice;
			cout << "Would you like to run the report module again? ('y' = yes, 'n' = no)" << endl;
			cout << "Please enter your choice: " << endl;
			cin >> reportAgain_choice;

			//Validate user choice
			while (reportAgain_choice != "y" && reportAgain_choice != "n")
			{
				cout << "Error! Invalid entry. Your choice can either be a lowercase 'y' for yes, or 'n' for no" << endl;
				cout << "Please re-enter your choice: ";
				cin >> reportAgain_choice;
			}

			if (reportAgain_choice == "y")
			{
				//Re-Display Report menu to user if they elect to re-run report
					std::cout << "-------REPORT MODULE-------" << endl;
				std::cout << "	1.List of All Books" << endl;
				std::cout << "	2.Report Whole Sale" << endl;
				std::cout << "	3.Report Retail Value" << endl;
				std::cout << "	4.List by Quantity" << endl;
				std::cout << "	5.List by Cost" << endl;
				std::cout << "	6.List by Age" << endl;
					std::cout << "	7.Return to Main menu" << endl;
				std::cout << "Please enter your decision: ";
				cin >> decide;
					cout << endl; //for aesthetics

					//Exit if user chooses to return to main menu
				if (decide == 7)
					{
						main_again = 'y'; //This will return to MAIN PROGRAM MENU
					break;
			}
						
				}
			else
			{
				//This will break loop if user elects not to re-run report module
				break;
			}
				
		}//end outer-while loop

} //End of if statement for report module



	//If user chooses inventory database module... Execute this code
	if (main_choice == 2)
	{
		//INVENTORY MODULE CODE BELOW
		//ALL CODE FOR INVENTORY MODULE BELOW
		//Declare variables
		string book; //  variable used for extracting book
		int choice;
		int counter = 0;
		string search_value; //Used for Title of book or ISBN number when LOOK UP book
		string input;
		string Book2Delete; //for deleting book (book name variable)
		string Book2Edit;
		//int search_input; //Used for edit a book
		bool again = false; //for look up a book 
		//char do_again = 'n'; //for look up a book
		int search_choice;// for edit a book
		int whichBook2edit; // variable to choose book for editing
		//Create inventory object
		//Inventory object; // delete once add book works

		//Variables for add a book
		string ISBN;
		string title, author, publisher, date_added;
		int quantity_onHand;
		double wholesale_cost, retail_price;
		char inventory_again = 'y';



while (inventory_again == 'y' || inventory_again == 'Y')
			{
	inventory_again = 'n';
				
		//USER MENU CHOICE FOR INVENTORY MODULE
				std::cout << "------INVENTORY DATABASE-----" << endl;
		std::cout << "1. Look Up a Book" << endl;
		std::cout << "2. Add a Book" << endl;
		std::cout << "3. Edit a Book's Record" << endl;
		std::cout << "4. Delete a Book" << endl;
		std::cout << "5. Return to Main Menu" << endl;
		std::cout << endl;
		std::cout << "Enter Your Choice: ";
		cin.ignore();
		cin >> choice;

		//VALIDATION Choice must be between 1-5
		while (choice < 1 || choice > 5)
		{
			std::cout << "Error! You must make a choice between 1-5. Please re-enter your choice: ";
			cin.ignore();
			cin >> choice;
		}


		//Run choice through switch statement and do the appropriate function
		switch (choice)
		{
		case 1:
			//LOOK UP A BOOK

			//Declare variables
			//int lineNumber;

			
				//Reset "again" variable
				again = false;

				//Display menu to user for looking up a book
				std::cout << "How would you like to search for the book?" << endl;
				std::cout << "    1)ISBN" << endl;
				std::cout << "    2)Title" << endl;
				std::cout << "Enter your choice: ";
				cin >> search_choice;

				//VALIDATION The choice to be numeric values of 1 or 2
				//NOTE: If isdigit returns a value of 0, that means that the character passed to it is not numeric && isdigit(search_choice) == 0
				while (cin.fail() || (search_choice < 1) || (search_choice > 2))
				{
					std::cout << "Invalid Entry! Value must either be 1 or 2. Please re-enter: ";
					cin.clear();
					cin.ignore(numeric_limits <streamsize> ::max(), '\n');
					cin >> search_choice;
				}

				//Run user search_choice variable through a switch statement and run appropriate code
				switch (search_choice)
				{
				case 1:
					//LOOK UP BOOK

					//Declare variables
					bool bookFound;

					//SEARCH BY ISBN
					std::cout << "Please enter the ISBN number of the book you're looking for: ";
					std::cin.ignore();
					getline(std::cin, search_value);

					//Search for book using ISBN
					//Last parameter is 1, because choice 1 = search by value
							bookFound = getBook(bookData, search_value, "Inventory.txt", 1);

					if (bookFound != false)
					{
						std::cout << "ISBN: " << bookData.getISBN() << endl;
						std::cout << "Title: " << bookData.getTitle() << endl;
						std::cout << "Author: " << bookData.getAuthor() << endl;
						std::cout << "Publisher: " << bookData.getPublisher() << endl;
						std::cout << "Date Added: " << bookData.getDate_added() << endl;
						std::cout << "Quantity on Hand: " << bookData.getQuantity_onHand() << endl;
						std::cout << "Wholesale Cost: " << bookData.getWholesale_cost() << endl;
						std::cout << "Retail Price: " << bookData.getRetail_price() << endl;
						std::cout << endl;
					}
					else
					{
						std::cout << "Book not found!" << endl;
					}
					break;
				case 2:
					//SEARCH BY TITLE
					std::cout << "Please enter the title of the book you're looking for: ";
					cin.ignore();
					getline(cin, search_value);

					//Find book using "getBook" function
					//A choice of 2(last parameter in function) allows for a search by Title of book
							bookFound = getBook(bookData, search_value, "Inventory.txt", 2);

					if (bookFound != false)
					{
						std::cout << "ISBN: " << bookData.getISBN() << endl;
						std::cout << "Title: " << bookData.getTitle() << endl;
						std::cout << "Author: " << bookData.getAuthor() << endl;
						std::cout << "Publisher: " << bookData.getPublisher() << endl;
						std::cout << "Date Added: " << bookData.getDate_added() << endl;
						std::cout << "Quantity on Hand: " << bookData.getQuantity_onHand() << endl;
						std::cout << "Wholesale Cost: " << bookData.getWholesale_cost() << endl;
						std::cout << "Retail Price: " << bookData.getRetail_price() << endl;
						std::cout << endl;
					}
					else
					{
						std::cout << "Book not found!" << endl;
					}

					break;
				default:
					std::cout << "ERROR! Default case has been entered..." << endl;
					break;
				} //end inner "switch" statement for selection of ISBN or Title

				/*
				//Ask user if they would like to search for another book
				std::cout << "Would you like to look up another book?(y = yes, n = no) ?" << endl;
				cin.ignore();
				cin >> do_again;


				//If user elects to search for another book this loop will run again
				if (do_again == 'y')
					again = true;
				*/

			} while (again == true);


			break;
		case 2:
			//ADD A BOOK

			//bound checking
			//User input "ISBN"
			std::cout << "ISBN-10 or ISBN-13: ";
			cin.ignore();
			getline(cin, ISBN);

				
			//VALIDATION ISBN
			//Must be 13 digits long
			while (ISBN.length() != 10 && ISBN.length() != 13)
			{
				std::cout << "ISBN must be 10 or 13 digits in length. Please re-enter ISBN: ";
				getline(cin, ISBN);
			}

			//*******************************
			//User input title, author, publisher
			//No validation required for these 3 data entries
			std::cout << "Title: ";
			getline(cin, title);
					while (title.length() < 1)
					{
						std::cout << "Error Please enter a valid Title: ";
						getline(cin, title);
					}

			std::cout << "Author: ";
			getline(cin, author);
					while (author.length() < 1)
					{
						std::cout << "Error Please enter a valid Author: ";
						getline(cin, author);
					}

			std::cout << "Publisher: ";
			getline(cin, publisher);
			while (publisher.length() < 1)
					{
						std::cout << "Error Please enter a valid Publisher: ";
						getline(cin, publisher);
					}
			//********************************

			//User input
			std::cout << "Date Added(mm/dd/yyyy): ";
			getline(cin, date_added);

			//VALIDATION for date_added
			//Format : mm/dd/yyyy
			//Note: First we need to make sure that the string being entered is 10 characters in length,
			//then we need to check and see if the user entered the date correctly
			//by checking for the inclusion of slashes and that the input is numbers and not letters
			while (date_added.length() != 10 || !(isdigit(date_added[0])) || !(isdigit(date_added[1])) || !(isdigit(date_added[3])) ||
				!(isdigit(date_added[4])) || !(isdigit(date_added[6])) || !(isdigit(date_added[7])) || !(isdigit(date_added[8])) ||
				!(isdigit(date_added[9]))) // if possible limit the numbers here to make sure date is correct
			{
				std::cout << "Error, date format is incorrect. Please, re-enter(Example: June 10, 2017 would be entered as 06/10/2017): ";
				getline(cin, date_added);
			}

			while (((date_added[2] != '/') || (date_added[5] != '/')))
			{
				std::cout << "date_added[2] :" << date_added[2] << "|" << endl;
				std::cout << "Error, date format is incorrect. Please, re-enter(Example: June 10, 2017 would be entered as 06/10/2017): ";
				getline(cin, date_added);
			}
			//********************************
			
			//noskipws skips white space
			std::cout << "Quantity On Hand: ";
			cin >> noskipws >> quantity_onHand;

			//VALIDATION for quantity on hand
			while (cin.fail() || quantity_onHand < 0)
			{
				cin.clear();
				std::cout << "Error! Must be numerical value > 0. Please Re-Enter: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				cin >> quantity_onHand;

			}

			//********************************
			std::cout << "Wholesale Cost: ";
			cin.ignore();
			cin >> wholesale_cost;

			while (cin.fail() || wholesale_cost < 0)
			{
				cin.clear();
				std::cout << "Error! Must be decimal value > 0 (i.e 5.50). Please Re-Enter: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				cin >> wholesale_cost;
			}

			//********************************
			std::cout << "Retail Price: ";
			cin.ignore();
			cin >> retail_price;
			while (cin.fail() || retail_price < 0)
			{
				cin.clear();
				std::cout << "Error! Must be numerical value. Please Re-Enter: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				cin >> retail_price;

			}

			//Store information into object
			/*object = { ISBN, title, author, publisher, date_added, quantity_onHand, wholesale_cost, retail_price };*/ //delete once add book works
			addBook("Inventory.txt", ISBN, title, author, publisher, date_added, quantity_onHand, wholesale_cost, retail_price);//this will write the book to file
			//Output the entire object(book) into file
			//fileObject << endl; //add space between books
			//fileObject << object; //Operator overloading allows us to ouput entire object

			cout << endl; //for aesthetics

			break;
		case 3:
			//EDIT A BOOK
			//Display menu for user
					std::cout << "How would you like to search for a book to edit?" << endl;
					std::cout << "	1)ISBN" << endl;
					std::cout << "	2)Title" << endl;
			std::cout << "Enter your choice: ";
			cin >> search_choice;

			//Validate the choice to be numeric values of 1 or 2
			//Note: if isdigit returns a value of 0, that means that the character passed to it is not numeric && isdigit(search_choice) == 0
			while (cin.fail() || (search_choice < 1) || (search_choice > 2))
			{
				std::cout << "Invalid Entry! Value must either be 1 or 2. Please re-enter: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max());
				cin >> search_choice;
			}
			cout << "What is it: ";

			cin.ignore();
			getline(cin, Book2Edit);
			cout << endl;

			while ((getBook(bookData, Book2Edit, "Inventory.txt", search_choice)) == false)
			{
				cout << "Error! Book could not be found, Please re-enter the search term: " << endl;
				cin.clear();
				//cin.ignore();
				getline(cin, Book2Edit);
				cout << "they Entered: " << Book2Edit;
			}

			cout << "Book Information: " << endl << bookData << endl;

			cout << "Which parameter would you like to edit?" << endl << "1.Isbn     2.Title     3.Author     4.Publisher     \n5.Date Added     6.Quantity     7.Wholesale Price     8.Retail Price" << endl;
			cin >> whichBook2edit;

			while (cin.fail() || whichBook2edit < 1 || whichBook2edit > 8)
			{
				cout << "Error! Invalid Input, Please Make Sure Your Input Is An Integer Between 1 And 8" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> whichBook2edit;
			}
			//-----------------------------------------------------------
			if (whichBook2edit == 1)
			{
				cout << "The current Isbn No. for this book is: " << bookData.getISBN() << endl << "Please enter the new Isbn No. :";
				cin.ignore();
				getline(cin, ISBN);
				while (ISBN.length() != 10 && ISBN.length() != 13)
				{
					std::cout << "ISBN must be 10 or 13 digits in length. Please re-enter ISBN: ";
					cin.ignore();
					getline(cin, ISBN);
				}
				
				DeleteBook("Inventory.txt", bookData.getISBN(), 1);
				//bookData.setISBN(ISBN);
				addBook("Inventory.txt", ISBN, bookData.getTitle(), bookData.getAuthor(), bookData.getPublisher(), bookData.getDate_added(), bookData.getQuantity_onHand(), bookData.getWholesale_cost(), bookData.getRetail_price());
			//	addBook()

			}
			//----------------------------------------------------------
			if (whichBook2edit == 2)
			{
				cout << "The current tite of the book is: " << bookData.getTitle() << endl << "Please enter the new Title: ";
				cin.ignore();
				getline(cin, title);
				DeleteBook("Inventory.txt", bookData.getISBN(), 1);
				//bookData.setISBN(ISBN);
				addBook("Inventory.txt", bookData.getISBN(), title, bookData.getAuthor(), bookData.getPublisher(), bookData.getDate_added(), bookData.getQuantity_onHand(), bookData.getWholesale_cost(), bookData.getRetail_price());
			}
			//----------------------------------------------------------
			if (whichBook2edit == 3)
			{
				cout << "The current Author of the book is: " << bookData.getAuthor() << endl << "Please enter the new Author's name: ";
				cin.ignore();
				getline(cin, author);
				DeleteBook("Inventory.txt", bookData.getISBN(), 1);
				//bookData.setISBN(ISBN);
				addBook("Inventory.txt", bookData.getISBN(), bookData.getTitle(), author, bookData.getPublisher(), bookData.getDate_added(), bookData.getQuantity_onHand(), bookData.getWholesale_cost(), bookData.getRetail_price());
			}
			//----------------------------------------------------------
			if (whichBook2edit == 4)
			{
				cout << "The current Publisher of the book is: " << bookData.getPublisher() << endl << "Please enter the new Publishers name: ";
				cin.ignore();
				getline(cin, publisher);
				DeleteBook("Inventory.txt", bookData.getISBN(), 1);
				//bookData.setISBN(ISBN);
				addBook("Inventory.txt", bookData.getISBN(), bookData.getTitle(), bookData.getAuthor(), publisher, bookData.getDate_added(), bookData.getQuantity_onHand(), bookData.getWholesale_cost(), bookData.getRetail_price());
			}
			//-----------------------------------------------------------
			if (whichBook2edit == 5)
			{
				cout << "The current Date added is: " << bookData.getDate_added() << endl << "Please enter the new date: ";
				//
				cin.ignore();
				getline(cin, date_added);

				}
				//while (date_added.length() != 10 || !(isdigit(date_added[0])) || !(isdigit(date_added[1])) || !(isdigit(date_added[3])) ||
				//	!(isdigit(date_added[4])) || !(isdigit(date_added[6])) || !(isdigit(date_added[7])) || !(isdigit(date_added[8])) ||
				//	!(isdigit(date_added[9]))) // if possible limit the numbers here to make sure date is correct
				//{
				//	//cin.clear();
				//	std::cout << "Error, date format is incorrect. Please, re-enter(Example: June 10, 2017 would be entered as 06/10/2017): ";
				//	cin.ignore(numeric_limits<streamsize>::max());
				//	getline(cin, date_added);
				//	//cin.ignore();
				//}
				DeleteBook("Inventory.txt", bookData.getISBN(), 1);
				//bookData.setISBN(ISBN);
				addBook("Inventory.txt", bookData.getISBN(), bookData.getTitle(), bookData.getAuthor(), bookData.getPublisher(), date_added, bookData.getQuantity_onHand(), bookData.getWholesale_cost(), bookData.getRetail_price());
			
			//-----------------------------------------------------------
			if (whichBook2edit == 6)
			{
				cout << "The current quantity is: " << bookData.getQuantity_onHand() << endl << "Please enter the new quantity: ";
				cin.ignore();
				cin >> quantity_onHand;
				while (cin.fail() || quantity_onHand < 0)
				{
					cin.clear();
					std::cout << "Error! Must be numerical value. Please Re-Enter: ";
					cin.ignore(numeric_limits < streamsize > ::max(), '\n');
					cin >> quantity_onHand;

				}
				DeleteBook("Inventory.txt", bookData.getISBN(), 1);
				//bookData.setISBN(ISBN);
				addBook("Inventory.txt", bookData.getISBN(), bookData.getTitle(), bookData.getAuthor(), bookData.getPublisher(), bookData.getDate_added(), quantity_onHand, bookData.getWholesale_cost(), bookData.getRetail_price());
			
			}
			//-----------------------------------------------------------
			if (whichBook2edit == 7)
			{
				cout << "The current WholeSale Price is: " << bookData.getWholesale_cost() << endl << "Please enter the new Wholesale price:  ";
				cin.ignore();
				cin >> wholesale_cost;
				while (cin.fail() || wholesale_cost < 0)
				{
					cin.clear();
					std::cout << "Error! Must be integer value. Please Re-Enter: ";
					cin.ignore(numeric_limits < streamsize > ::max(), '\n');
					cin >> wholesale_cost;
				}
				DeleteBook("Inventory.txt", bookData.getISBN(), 1);
				//bookData.setISBN(ISBN);
				addBook("Inventory.txt", bookData.getISBN(), bookData.getTitle(), bookData.getAuthor(), bookData.getPublisher(), bookData.getDate_added(), bookData.getQuantity_onHand(), wholesale_cost, bookData.getRetail_price());
			}

			//-----------------------------------------------------------
			if (whichBook2edit == 8)
			{
				cout << "The current RetailPrice of the book is: " << bookData.getRetail_price() << endl << "Please Enter the New Retail Price: ";
				cin.ignore();
				cin >> retail_price;
				while (cin.fail() || retail_price < 0)
				{
					cin.clear();
					std::cout << "Error! Must be numerical value. Please Re-Enter: ";
					cin.ignore(numeric_limits < streamsize > ::max(), '\n');
					cin >> retail_price;

				}
				DeleteBook("Inventory.txt", bookData.getISBN(), 1);
				//bookData.setISBN(ISBN);
				addBook("Inventory.txt", bookData.getISBN(), bookData.getTitle(), bookData.getAuthor(), bookData.getPublisher(), bookData.getDate_added(), bookData.getQuantity_onHand(), bookData.getWholesale_cost(), retail_price);
			}
			//-----------------------------------------------------------
			//write the new book data to the inventory file(update it)
			/*DeleteBook("Inventory.txt", bookData.getISBN(), 1);
			addBook("Inventory.txt", ISBN, title, author, publisher, date_added, quantity_onHand, wholesale_cost, retail_price);
*/


			//
			break;
		case 4:
			//DELETE A BOOK
			int user_choiceDeleteBook;
			//Display menu for user
			std::cout << "How would you like to search for a book to delete?" << endl;
			std::cout << "    1)ISBN" << endl;
			std::cout << "    2)Title" << endl;
			std::cout << "Enter your choice: ";
			cin >> user_choiceDeleteBook;

			//Validation for user input
			while (cin.fail() || (user_choiceDeleteBook < 1) || (user_choiceDeleteBook > 2))
			{
				cout << "Error! Invalid Choice. Choice must be either 1 or 2. Please re-enter: ";
				cin.clear(); // clears the fail state for cin.fail()
				cin.ignore(numeric_limits < streamsize > ::max(), '\n');
				cin >> user_choiceDeleteBook;
			}

			//User input for title or isbn
			cout << "Please enter it: ";
			cin.ignore();
			getline(cin, Book2Delete);

			//If delete book was succesful, then print success message
			//otherwise output error message
			if (DeleteBook("Inventory.txt", Book2Delete, user_choiceDeleteBook)){
				cout << "Book Successfully Deleted!" << endl;
			}
			else
			{
				cout << "Error! The Book Could Not Be Deleted." << endl;
			}
			

			//deleteBookJune21("Inventory.txt", book, 1); // this was commented 

			//Testing if Kamal delete book function works TESTING TESTING TESTING
		//	deleteBookKamal("Inventory.txt", book);


			//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
			//Leander Delete A Book	
			/*
			//  std::cout << "Enter the name of the book you'd like to delete" << endl;
			//	cin.clear();
			//	cin.ignore();
			//  getline(cin, bookname);
			bookName = "12654789632";  //this is isbn just using for testing -L
			std::cout << " Deleting.... " << bookName << endl;
			//deleteBook(bookName, "Inventory.txt");
			std::cout << "Book successfully deleted" << endl;
			*/
			break;
		case 5:
			//Return to main menu
					main_again = 'y';
			break;
		default:
			std::cout << "Invalid choice!";
			break;

		} //END BIG OUTSIDE SWITCH STATEMENT


		if (inventory_again != 'y')
				{
					cout << endl;
					cout << "Would you like to re-run the INVENTORY DATABASE MODULE? ('y' for yes, 'n' for no)" << endl;
					cout << "Please enter choice: ";
		/*	cin.clear();
			cin.ignore();*/
			cin>>inventory_again;
			//cout << "They entered: " << endl<<inventory_again;
		}
					//Validate user chocie to re-run data
					while (inventory_again != 'y' && inventory_again != 'Y' && inventory_again != 'n' && inventory_again != 'N')
					{
						cout << "Invalid entry! ('y' for yes, or 'n' for no)" << endl;
						cout << "Please re-enter your choice: ";
						/*cin.clear();
						cin.ignore();*/
						cin >> inventory_again;
						cout << endl; //for aesthetics
					}
				//}

				}

		//Print 
		std::cout << endl;

		//Close file 
		//fileObject.close();

	}//End if statement for Inventory Module

		//If user chooses CASHIER MODULE execute following code
	if (main_choice == 1)
	{
		int total = totalBook();  // find how many books are in the file
			Report testing[50];
		getAllBook("Inventory.txt", total, testing);  // fills the object array with all the book information
		string titleISBN;
		int sortBy = 0;	int quan;  //makes variables that user will input
		Cashier sample;  //makes a cashier object
			string reportAgain_choice; //For if user wants to re-run 
		
			//Run entire CASHIER MODULE in do-while loop if user wants to keep looping in it
			do
			{
				cout << "-----------CASHIER MODULE---------------" << endl;
				cout << "    1.Purchase by searching for Title " << endl;
				cout << "    2.Purchase by searching for ISBN  " << endl;
				cout << "    3.Return to Main Menu " << endl;
				cout << "Please enter your choice: ";
		cin >> sortBy;
				cout << endl; //skip line for aesthetics

		while (std::cin.fail() || (sortBy < 1) || (sortBy > 3))  //makes sure user entered a valid input if not they get an error message to enter a valid input
		{
			std::cout << "Invalid input! Please make sure your choice is a number 1, 2, or 3:" << endl;
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
			std::cin >> sortBy;
		}
		
				if (sortBy == 3)
		{
					main_again = 'y'; // Will return to Main Meu
					break;
				}

			if (sortBy == 1)
			{ 
				cout << "Input the title: \n";
				getline(cin, titleISBN); // need 2 because just 1 doesnt work
				getline(cin, titleISBN);
				cout << endl;
				cout << "How many of the book would you like to buy? \n";
				cin >> quan;
				cout << endl;
				cout << "*****************************************************************" << endl;
				sample.searchBuy(testing, titleISBN, total, sortBy, quan); // substracts the quantity user bought from the quantity on hand
				cout << endl << endl;  //Skip lines for aesthetics
			}
			if (sortBy == 2)	
			{
				cout << "Input the ISBN: \n";
				getline(cin, titleISBN); // need 2 because just 1 doesnt work
				getline(cin, titleISBN);
				cout << endl;
				cout << "How many of the book would you like to buy? \n";
				cin >> quan;
				cout << endl;
				cout << "*****************************************************************" << endl;
				sample.searchBuy(testing, titleISBN, total, sortBy, quan); // substracts the quantity user bought from the quantity on hand
				cout << endl << endl;  //Skip lines for aesthetics
			}

			//sample.searchBuy(testing, titleISBN, total, sortBy, quan); // substracts the quantity user bought from the quantity on hand
		
			//
			//cout << endl << endl;  //Skip lines for aesthetics

			//Ask user if they would like to run the Report Module again
			cout << "Would you like to run the Cashier module again? ('y' = yes, 'n' = no)" << endl;
			cout << "Please enter your choice: " << endl;
			cin >> reportAgain_choice;
			cout << endl;

			//Validate user choice
				while (reportAgain_choice != "y" && reportAgain_choice != "Y" && reportAgain_choice != "n" && reportAgain_choice != "N")
			{
				cout << "Error! Invalid entry. Your choice can either be a lowercase 'y' for yes, or 'n' for no" << endl;
				cout << "Please re-enter your choice: ";
				cin >> reportAgain_choice;
			}

			} while (reportAgain_choice == "y" || reportAgain_choice == "Y");


			}


		//Ask user if they would like to re-run the entire program again
		//main_again is set to 'y' when users want to return to main menu from individual modules
		if (main_again != 'y')
			{
			cout << endl << "Would you like to run the MAIN program again? ('y' = yes, 'n' = no)" << endl;
			cout << "Please enter your choice: ";
			cin.ignore();
			cin >> main_again;
			
	}

	} while (main_again == 'y' || main_again == 'Y');
	

	//Display terminating program message
	cout << "Terminating program..." << endl;

	system("PAUSE");
	return 0;

}//END MAIN

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//INVENTORY MODULE FUNCTIONS BELOW
int search(string search_value, string file_name)
{
	//Author Kamal
	//This function accepts a string parameter as input(search_value)
	//And searches for it through a file, also entered as parameter(file_name)
	//Then returns the line at which the string is found
	//CAUTION: Return Value of -1 means book was not found

	//Declare local variables
	string input;
	int lineNumber = 0;
	fstream fileObject;
	bool found = false;

	//Open file
	fileObject.open(file_name, ios::in);

	//Keep inputting the file line by line and see if the input line is equal to the search_value that was passed into function
	while (getline(fileObject, input))
	{
		lineNumber++;
		if (input == search_value)
		{
			found = true; //Set flag to true if string was found within the file
			break;
		}
	}


	if (found == true)
	{
		return lineNumber;
	}
	else
	{
		//-1 = Book not found
		return -1;
	}

	fileObject.close();
}


bool getBook(Inventory &obj, string book, string file_name, int type)
{
	//Author Leander
	//This Function extracts book data from a file 
	//It first finds a book then reads in data for the next 7 lines
	//NOTE: WILL RETURN FALSE IF BOOK NOT FOUND

	// fileObject for inventory file
	fstream fileObject; 
	fileObject.open(file_name, ios::in); // opening file in input mode
	string holder; // variable to hold line input from file
	int counter = 1; // variable to keep track of lines                      
	int lineNo; //int to indicate start point of Book data (ISBN)
		lineNo = (search(book, file_name));
	  //lineNo will be x-1 if searched by title // need to implement that 
	bool bookFound = true;
	
	//To account for search by "TITLE"
	if (type == 2){
		lineNo -= 1;
	}
	
	if (lineNo > -1)
	{
		while (getline(fileObject, holder)) //advancing through each line
		{
			if (lineNo == counter)
			{
				obj.setISBN(holder);         //set ISBN
			}
			if (lineNo + 1 == counter)
			{
				obj.setTitle(holder);        //set Title
			}
			if (lineNo + 2 == counter)
			{
				obj.setAuthor(holder);       //setAuthor
			}
			if (lineNo + 3 == counter)
			{
				obj.setPublisher(holder);    //set Publisher
			}
			if (lineNo + 4 == counter)
			{
				obj.setDate_added(holder);   //set Date
			}
			if (lineNo + 5 == counter)
			{
				int quant = stoi(holder);
				obj.setQuatity_onHand(quant);   //set quantity after converting string to int 
			}
			if (lineNo + 6 == counter)
			{
				double Wcost = atof(holder.c_str());
				obj.setWholesale_cost(Wcost);   //set wholesail cost after converting string to char array and then double
			}
			if (lineNo + 7 == counter)
			{
				double price = atof(holder.c_str());
				obj.setRetail_price(price);     //set retail price after converting string to int
			}
			counter++; // incrementing counter
		}
	}
	
	if (lineNo > -1)
		bookFound = true;
	else
		bookFound = false;

	return bookFound;
	
} //end function "getBook" // have get book accept and object or return Inventory class object

bool DeleteBook(string file_name, string isbn_title, int which)
{
	//Leander and Kamal

	//This function accepts 3 parameters file_name of file to be read,
	//isbn or title of book as string input, "which" = user selection to 
	//delete by title or isbn
	//This function will return false if: input file is unable to open & 
	//if book is not found
	//Function is reliant on "search" function, because it needs the line number
	//of book object in source file

	//Declare local variables
	string holder;
	int counter = 1; //counter = 1 because we start counting at 1

	//Open file for input
	ifstream source;
	source.open(file_name);

	//if file fails to open return false
	if (source.fail())
	{
		return false;
	}

	//create temporary buffer file
	//That stores original source file without delted book
	ofstream buffer;
	buffer.open("buffer.txt");
	int lineNo;
	//get line number of the book and modify it according to search by title ot isbn
	if ((search(isbn_title, "Inventory.txt")) != -1)
	{
		lineNo = (search(isbn_title, "Inventory.txt")) + 1 - which;
	}
	else
{
		return false;
	}
	//If user elects to search_by Title then subtract 1 from the line number to account for 
	 
	//if line number = -1 that means the search function could not find the book and so we return false
	//if (lineNo == -1)
	//{
	//	return false;
	//}
	
	
	//iterate through the file line by line and increment the counter 
	//if counter value is not equal to the line number of the book
	//write the value of the line (read into holder) to the output (buffer file)
	while (getline(source, holder))
	{
		if (counter != lineNo	  &&
			counter != lineNo + 1 &&
			counter != lineNo + 2 &&
			counter != lineNo + 3 &&
			counter != lineNo + 4 &&
			counter != lineNo + 5 &&
			counter != lineNo + 6 &&
			counter != lineNo + 7 &&
			counter != lineNo + 8)
	{
			buffer << holder << endl;
		}
		counter++;
	}

	//close both source and buffer files
	source.close();
	buffer.close();

	//remove the source file and rename the buffer file
	std::remove(file_name.c_str());
	std::rename("buffer.txt", file_name.c_str());

	//If all goes according to plan then return true
	return true;
}
//REPORT MODULE FUNCTIONS
int totalBook()   //this function counts how many books there are in the file for use on report functions
{
	ifstream test;
	test.open("Inventory.txt");
	int total = 0;
	int counter = 0;
	if (test.is_open())      //searches for how many ISBNs there are in the file to count how many books there are
	{
		int length;
		string temp;
		while (test >> temp) //reads in strings in file to a temp variable
		{
			temp.c_str();
			length = temp.length();
			int x = 0;
			if (length > 9 && length < 14)  //checks if the string stored in temp is an isbn
			{
				while (x < length)
				{
					if (isdigit(temp[x]) != 0)   //makes sure it is all digits to confirm it is an ISBN
					{
						x++;
						counter++;
						if (x == (length - 1))	total++;  //if it is an ISBN adds to the total counter of books
					}
					else break;  // if it is not an ISBN breaks and does not contribute to the total counter of books
				}
			}
		}
	}
	test.close();
	const int temp = total;   // makes the total a constant because it should remain unchanged throughout the program after this
	return temp;
}

void getAllBook(std::string file_name, int total, Report object[])
{
	std::fstream fileObject;
	fileObject.open(file_name, std::ios::in); // opening file in input mode
	std::string holder;

	try // used this to exception handle. Used to be a bug here that was fixed
	{
		for (int x = 0; x < total; x++)
		{
		
			getline(fileObject, holder);      //set ISBN
			object[x].setISBN(holder);

			getline(fileObject, holder);         //set Title
			object[x].setTitle(holder);

			getline(fileObject, holder);        //setAuthor
			object[x].setAuthor(holder);

			getline(fileObject, holder);     //set Publisher
			object[x].setPublisher(holder);

			getline(fileObject, holder);    //set Date
			object[x].setDate_added(holder);

			std::string temp;
			getline(fileObject, temp);    //set quantity_onHand after converting string to int 
			int quantity_onHand = stoi(temp);
			object[x].setQuatity_onHand(quantity_onHand);

			getline(fileObject, holder);			//set wholesale cost
			object[x].setWholesale_cost(stod(holder));

			getline(fileObject, holder);
			object[x].setRetail_price(stod(holder));				//set retail price

			getline(fileObject, holder);					//last line
		}
	}
	catch (exception e) //catches exception so it does not crash
	{
		cout << e.what() << endl; //tells what the exception is so it can be fixed
		return;
	}
}

void editABook(string file_name, string term2replace, string replace_with) // a function that replaces a certain parameter 
{
	//Authors Leander and Kamal

	//This function works with two files
	//It reads input from original file and if
	//a string is matched to replace with, it replaces it with the "with" parameter passed to this function
	//And output to 

	//Open original file
	ifstream inventoryfile;			
	inventoryfile.open(file_name); 
	
	//Open temp file
	ofstream temp;					
	temp.open("temp.txt");

	//Variable for storing input
	string input;					

	//Read the file line by line
	while (getline(inventoryfile, input)) 
	{
		//If "input" is equal to the term2replace
		//then replace it with user entered parameter("replace_with")
		if (input == term2replace)
		{
			temp << replace_with <<endl;
		}
		else
		{
			//Else write data from original file as it is
			temp << input <<endl; 

		}
	}

	//Close both temp and source files
	inventoryfile.close(); 
	temp.close();				

	//Remove the original file and rename it to 
	std::remove(file_name.c_str());
	std::rename("temp.txt", file_name.c_str());
} // needs work... get delete book to work first.... // needs work... get delete book to work first
//needs.. work get delete book to work first
void addBook(string fileName,string isbn, string title, string author, string publisher, string date_added, int quantity, double wholesaleCost, double retailPrice)
{
	fstream write(fileName, ios::out | ios::app); //open file for writing with pointer at the end
	Inventory *newBook = new Inventory(isbn, title, author, publisher, date_added, quantity, wholesaleCost, retailPrice); // dynamicaly creating book
	write << *newBook <<endl; //write book to file 
	write.close(); //close fstream object
	delete newBook; //free up memory
}

