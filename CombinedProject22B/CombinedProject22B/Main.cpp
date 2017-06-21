//Authors Kamal, Leander, George, Jessie

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stdio.h> // to remove rename files
#include "Report.h"
#include "Inventory.h"
using namespace std;

//Inventory Module Prototypes
int search(string search_value, string file_name);
void deleteBook(string book_name, string file_name); // function for deleting books
bool getBook(string book, string file_name, int type); // function for extracting book
//void deleteBookKamal(string file_name, string isbn_input);
void deleteBookLK(string fileName, string book, int by);
void editABook(string file_name, string term2replace, string with);// edit a book function

//Report Module Protoypes
int totalBook();
void getAllBook(std::string file_name, int total, Report object[]);
void sortQuan(Report testing[]);
void sortByQuan(Report array[], int max);

//Create "Inventory" object for storing book data we extract from inventory.txt file
Inventory bookData;

int main()
{
	//NOTE: std::cout just because compiler complains about cout being ambigous

	//Declare variables for main menu
	int main_choice;

	//Main Menu
	std::cout << "Boring Booksellers" << endl;
	std::cout << "    Main Menu     " << endl;
	std::cout << "1) Cashier Module" << endl;
	std::cout << "2) Inventory Database Module" << endl;
	std::cout << "3) Report Module" << endl;
	std::cout << "4) Exit" << endl;
	std::cout << endl << "Please enter your choice: ";
	std::cin >> main_choice;

	//Validate main choice to be between 1-4 and numerical
	while (std::cin.fail() || (main_choice < 1) || (main_choice > 4))
	{
		std::cout<<"Invalid input! Please enter a number between 1 and 4" << endl;
		std::cin.clear();
		std::cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		std::cin >> main_choice;
	} 
	
	//If user chooses report module then execute following code
	if (main_choice == 3)
	{
		//REPORT MODULE CODE BELOW
		//ALL CODE FOR REPORT MODULE BELOW
		int total = totalBook();
		Report testing[25];
		getAllBook("Inventory.txt", total, testing);

		//Display main Report menu to user and get their decision
		int decide = 0;
		std::cout << "Report Module" << endl;
		std::cout << "	1.List of All Books" << endl;
		std::cout << "	2.Report Whole Sale" << endl;
		std::cout << "	3.Report Retail Value" << endl;
		std::cout << "	4.List by Quantity" << endl;
		std::cout << "	5.List by Cost" << endl;
		std::cout << "	6.List by Age" << endl;
		std::cout << "	7.to exit" << endl;
		std::cout << "Please enter your decision: ";
		cin >> decide;

		// validation for decide ( checking to see if decision is between 0 and 7 )
		while (std::cin.fail() || (decide < 1) || (decide > 7))
		{
			std::cout << "Invalid input! Please make sure your choice is a number between 1 and 7" << endl;
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
			std::cin >> decide;
		}
		
		while ((decide != 7)) //if the exit case is not true
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
				std::cout << "Report Module" << endl;
				std::cout << "	1.List of All Books" << endl;
				std::cout << "	2.Report Whole Sale" << endl;
				std::cout << "	3.Report Retail Value" << endl;
				std::cout << "	4.List by Quantity" << endl;
				std::cout << "	5.List by Cost" << endl;
				std::cout << "	6.List by Age" << endl;
				std::cout << "	7.to exit" << endl;
				std::cout << "Please enter your decision: ";
				cin >> decide;

				//Exit if user chooses to exit
				if (decide == 7)
					break;
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
		string bookName; //for deleting book (book name variable)
		//int search_input; //Used for edit a book
		bool again = false; //for look up a book 
		char do_again; //for look up a book

		//Create inventory object
		Inventory object;

		//Variables for add a book
		string ISBN;
		string title, author, publisher, date_added;
		int quantity_onHand;
		double wholesale_cost, retail_price;

		//Create file object for ADD BOOK functionality
		fstream fileObject;

		//Open the file
		fileObject.open("Inventory.txt", ios::out | ios::in | ios::app);

		//USER MENU CHOICE FOR INVENTORY MODULE
		std::cout << "Boring Booksellers Inventory Database" << endl;
		std::cout << "1. Look Up a Book" << endl;
		std::cout << "2. Add a Book" << endl;
		std::cout << "3. Edit a Book's Record" << endl;
		std::cout << "4. Delete a Book" << endl;
		std::cout << "5. Return to Main Menu" << endl;
		std::cout << endl;
		std::cout << "Enter Your Choice: ";
		cin >> choice;

		cin.ignore();

		//VALIDATION Choice must be between 1-5
		while (choice < 1 || choice > 5)
		{
			std::cout << "Error! You must make a choice between 1-5. Please re-enter your choice: ";
			cin >> choice;
		}


		//TESTING TESTING
		string search_choice;

		//Run choice through switch statement and do the appropriate function
		switch (choice)
		{
		case 1:
			//LOOK UP A BOOK

			//Declare variables
			//int lineNumber;

			do
			{
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
				while ((search_choice[0] != '1' && search_choice[0] != '2') && (search_choice.length() > 1))
				{
					std::cout << "Invalid Entry! Value must either be 1 or 2. Please re-enter: ";
					cin >> search_choice;
				}

				//Run user search_choice variable through a switch statement and run appropriate code
				switch (search_choice[0])
				{
				case '1':
					//Declare variables
					bool bookFound;

					//SEARCH BY ISBN
					std::cout << "Please enter the ISBN number of the book you're looking for: ";
					std::cin.ignore();
					getline(std::cin, search_value);

					//Search for book using ISBN
					//Last parameter is 1, because choice 1 = search by value
					bookFound = getBook(search_value, "Inventory.txt", 1);

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
				case '2':
					//SEARCH BY TITLE
					std::cout << "Please enter the title of the book you're looking for: ";
					cin.ignore();
					getline(cin, search_value);

					//Find book using "getBook" function
					//A choice of 2(last parameter in function) allows for a search by Title of book
					bookFound = getBook(search_value, "Inventory.txt", 2);

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

				//Ask user if they would like to search for another book
				std::cout << "Would you like to look up another book?(y = yes, n = no) ?" << endl;
				cin >> do_again;

				//If user elects to search for another book this loop will run again
				if (do_again == 'y')
					again = true;

			} while (again == true);


			break;
		case 2:
			//ADD A BOOK

			//User input "ISBN"
			std::cout << "ISBN-10 or ISBN-13: ";
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

			std::cout << "Author: ";
			getline(cin, author);

			std::cout << "Publisher: ";
			getline(cin, publisher);
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

			//User input
			std::cout << "Quantity On Hand: ";
			cin >> quantity_onHand;

			//VALIDATION for quantity on hand
			while (cin.fail() || quantity_onHand < 0)
			{
				cin.clear();
				std::cout << "Error! Must be numerical value. Please Re-Enter: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n'); //figure out how this works
				cin >> quantity_onHand;

			}

			//********************************
			std::cout << "Wholesale Cost: ";
			cin >> wholesale_cost;
			while (cin.fail() || wholesale_cost < 0)
			{
				cin.clear();
				std::cout << "Error! Must be numerical value. Please Re-Enter: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n'); //figure out how this works
				cin >> wholesale_cost;
			}

			//********************************
			std::cout << "Retail Price: ";
			cin >> retail_price;
			while (cin.fail() || retail_price < 0)
			{
				cin.clear();
				std::cout << "Error! Must be numerical value. Please Re-Enter: ";
				cin.ignore(numeric_limits < streamsize > ::max(), '\n'); //figure out how this works
				cin >> retail_price;

			}

			//Store information into object
			object = { ISBN, title, author, publisher, date_added, quantity_onHand, wholesale_cost, retail_price };

			//Output the entire object(book) into file
			fileObject << endl; //add space between books
			fileObject << object; //Operator overloading allows us to ouput entire object

			break;
		case 3:
			//EDIT A BOOK

			////Display menu for user
			//std::cout << "How would you like to search for the book to edit?" << endl;
			//std::cout << "    1)ISBN" << endl;
			//std::cout << "    2)Title" << endl;
			//std::cout << "Enter your choice: ";
			//cin >> search_choice;

			////Validate the choice to be numeric values of 1 or 2
			////NOTE: If isdigit returns a value of 0, that means that the character passed to it is not numeric && isdigit(search_choice) == 0
			//while ((search_choice[0] != '1' && search_choice[0] != '2') && (search_choice.length() > 1))
			//{
			//	std::cout << "Invalid Entry! Value must either be 1 or 2. Please re-enter: ";
			//	cin >> search_choice;
			//}

			////Convert string into integer
			//if (stoi(search_choice) == 1)
			//{
			//	std::cout << "Please enter the ISBN-10 or ISBN-13 of the book you want to edit: ";
			//	cin.ignore();
			//	getline(cin, book);

			//	getBook(book, "Inventory.txt", 1);


			//}
			//else
			//{
			//	std::cout << "Please enter the Title of the book you want to edit: ";
			//	cin.ignore();
			//	getline(cin, book);

			//	getBook(book, "Inventory.txt", 2);

			//}

			editABook("Inventory.txt", "Camino Island", "TEST TEST TEST Camino Island");

			break;
		case 4:
			//Delete a Book

			//Get ISBN number from user TESTING TESTING TESTING
			std::cout << "Please enter the ISBN-10 or ISBN-13 of the book you want to edit: ";
			getline(cin, book);
			//deleteBookLK("Inventory.txt", book, 1);


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
			break;
		default:
			std::cout << "Invalid choice!";
			break;

		} //END BIG OUTSIDE SWITCH STATEMENT

		//Print 
		std::cout << endl;

		//Close file 
		fileObject.close();

	}//End if statement for Inventory Module

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


bool getBook(string book, string file_name, int type)
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
	lineNo = search(book, file_name);    //lineNo will be x-1 if searched by title // need to implement that 
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
				bookData.setISBN(holder);         //set ISBN
			}
			if (lineNo + 1 == counter)
			{
				bookData.setTitle(holder);        //set Title
			}
			if (lineNo + 2 == counter)
			{
				bookData.setAuthor(holder);       //setAuthor
			}
			if (lineNo + 3 == counter)
			{
				bookData.setPublisher(holder);    //set Publisher
			}
			if (lineNo + 4 == counter)
			{
				bookData.setDate_added(holder);   //set Date
			}
			if (lineNo + 5 == counter)
			{
				int quant = stoi(holder);
				bookData.setQuatity_onHand(quant);   //set quantity after converting string to int 
			}
			if (lineNo + 6 == counter)
			{
				double Wcost = atof(holder.c_str());
				bookData.setWholesale_cost(Wcost);   //set wholesail cost after converting string to char array and then double
			}
			if (lineNo + 7 == counter)
			{
				double price = atof(holder.c_str());
				bookData.setRetail_price(price);     //set retail price after converting string to int
			}
			counter++; // incrementing counter
		}
	}
	
	if (lineNo > -1)
		bookFound = true;
	else
		bookFound = false;

	return bookFound;
	
} //end function "getBook"


//void deleteBookKamal(string file_name, string isbn_input)
//{
//	//Author Kamal
//
//	//What I'm Trying to do in this function
//	// This function accepts an ISBN number as input
//	// I am using two file Objects... 1 for the original file and one for 
//	//the buffer file
//	//While each line of text is input from original file into the object,
//	//if the program matches the ISBN number then skip over that entire section
//	//of text and pick up from the next spot after a blank line
//	//In essence it will kind of jump over an entire book, meaning it won't be
//	//copied into the buffer file. 
//	//I am trying to achieve this somehow using counters... Like if
//	//at line 10 ISBN matches, then skip to line 19 and continue input of text
//
//	//Declare local variables
//	string line;
//	int counter = 0;
//	bool book_erased = false;
//
//	//Create ifstream and ofstream objects
//	fstream origin_fileObject;
//	ofstream destination_fileObject;
//
//	//Open origin file
//	//NOTE: Opened for both input and output to preserve data in the original file
//	origin_fileObject.open(file_name, ios::in);
//
//	//Open the destination file that the origin file will be copied into
//	destination_fileObject.open("buffer.txt");
//
//	//Read in origin file line by line and overwrite book 
//	//with blank strings if found
//	while (getline(origin_fileObject, line))
//	{
//		//Increments letting us know what line we are on
//		destination_fileObject << line << endl;
//
//		if (line == isbn_input)
//		{
//			//TESTING TESTING TESTING Display output to see if program enters into if statement TESTING TESTING TESTING
//			std::cout << "Book found" << endl;
//
//			while (getline(origin_fileObject, line))
//			{
//				if (line != "")
//				{ 
//					counter++;
//				}
//				else
//				{
//					counter++;
//					break;
//				}
//					
//					
//			} //end inner while-loop
//
//		} //end if statement
//
//	} //End while loop
//
//	//Output data to second buffer/destination file TESTING TESTING TESTING
//
//	origin_fileObject.close();
//	destination_fileObject.close();
//
//} //End function "deleteBookKamal"

//} //End function "deleteBookKamal"

//void deleteBook(string file_name, Inventory &bookData)
//
//void deleteBook(string file_name, Inventory &bookData)
//{
//	string read;
//	ifstream origin;
//	ofstream buffer;
//	buffer.open("buffer.txt");
//	
//	origin.open(file_name);
//	//getBook(book_name, file_name, );
//	
//	int counter = 0;
//	//	string title = bookData.getTitle; delete -L
//
//	/*
//	while (getline(origin, read))
//	{
//		if (read == bookData.getTitle || read == bookData.getISBN &&
//			getline(origin, read) == bookData.getAuthor && getline(origin, read) && bookData.getPublisher &&
//			getline(origin, read) == bookData.getDate_added && getline(origin, read) && bookData.getRetail_price &&
//		getline(origin, read) == bookData.getWholesale_cost )
//		{
//		buffer << read <<endl;
//		}             /////////////NEEDS FIXING////////////////////////////
//		else
//		{
//		origin.clear();
//		origin.ignore();
//		}
//		//	counter++;
//	}
//	*/
//
//	buffer.close();
//	origin.close();
//	remove(file_name.c_str());
//	rename("buffer.txt", file_name.c_str());
//}

void deleteBookLK(string fileName, string book, int by)
{
	Inventory *bookptr = new Inventory;
	getBook(book,fileName, by);
	ifstream originalFile;
	originalFile.open(fileName);
	ifstream bufferfile;
	bufferfile.open("buffer.txt");
	
	while (!originalFile.eof())
	{
		cin >> bookData;
		cout << bookData;
	}


	delete bookptr;
}

//REPORT MODULE FUNCTIONS
int totalBook()
{
	ifstream test;
	test.open("Inventory.txt");
	int total = 0;
	int counter = 0;
	if (test.is_open())
	{
		int length;
		string temp;
		while (test >> temp)
		{
			temp.c_str();
			length = temp.length();
			int x = 0;
			if (length > 9 && length < 14)
			{
				while (x < length)
				{
					if (isdigit(temp[x]) != 0)
					{
						x++;
						counter++;
						if (x == (length - 1))	total++;
					}
					else break;
				}
			}
		}
	}
	test.close();
	const int temp = total;
	return temp;
}


void getAllBook(std::string file_name, int total, Report object[])
{
	std::fstream fileObject;
	fileObject.open(file_name, std::ios::in); // opening file in input mode
	std::string holder;

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

		fileObject >> holder;						//last line
	}
}

void editABook(string file_name, string term2replace, string with) // a function that replaces a certain parameter 
{
	fstream inventoryfile(file_name, ios::in | ios::out);
	if (inventoryfile.fail())
	{
		cout << "File didnt open!!!";
	}
	string input;
	while (getline(inventoryfile, input))
	{
		//cout << "WHILE LOOP RUNS!";

		if (input == term2replace)
		{
			cout << "IF LOOP RAN!";
			inventoryfile << with;
		}
		else
		{
			inventoryfile << input;

		}
	}
	cout << "IT RAN, IT RAN, IT RAN!";
	inventoryfile.close();
}
