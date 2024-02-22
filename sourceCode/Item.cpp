/* Citation and Sources...
Final Project Milestone 5
Module: Item
Filename: Item.cpp
Version 1.1
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/19 Initial of Item moduel file.
2023/11/24 Modify Item module for Milestone 4.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip> 
#include "Item.h"
#include "Utils.h"

using namespace std;
namespace sdds {

	bool Item::linear() const // Returns the value of isLinear
	{
		return isLinear;
	}

	Item::Item() : price(0.0), quantity(0), needed(0), description(nullptr), isLinear(false), sku(0) {}

	Item::Item(const Item& src)
	{
		*this = src;
	}

	Item& Item::operator=(const Item& other) // Copy assignment operator
	{
		if (this != &other) // Self-assignment check
		{
			delete[] description;
			if (other.description != nullptr)
			{
				description = new char[strlen(other.description) + 1];
				strcpy(description, other.description);
			}
			else
			{
				description = nullptr;
			}
			price = other.price;
			quantity = other.quantity;
			needed = other.needed;
			isLinear = other.isLinear;
			state = other.state;
			sku = other.sku;
		}
		return *this;
	}

	Item::~Item() // Destructor
	{
		delete[] description;
	}

	int Item::qtyNeeded() const // Returns the value of needed
	{
		return needed;
	}

	int Item::qty() const // Returns the value of quantity
	{
		return quantity;
	}

	Item::operator double() const// Returns the value of price
	{
		return price;
	}

	Item::operator bool() const // Returns true if the object is not in a safe empty state
	{
		return state.operator bool() && sku > 0;
	}

	int Item::operator-=(int qty) // Subtracts qty from quantity and returns the result
	{
		quantity -= qty;
		return quantity;
	}

	int Item::operator+=(int qty)// Adds qty to quantity and returns the result
	{
		quantity += qty;
		return quantity;
	}

	void Item::linear(bool IsLinear) // Sets the isLinear flag for the current object to the value of the parameter
	{
		isLinear = IsLinear;
	}

	void Item::clear()
	{
		state.clear();
	}

	bool Item::operator==(int Sku) const// Returns true if the sku of the current object is equal to the parameter
	{
		return sku == Sku;
	}

	bool Item::operator==(const char* Description) const//
	{
		return Description && description && strstr(description, Description) != nullptr;
	}

	int Item::readSku(std::istream& istr) // Reads the sku from the parameter and returns the result
	{
		cout << "SKU: ";
		sku = ut.getint(40000, 99999);
		return sku;
	}

	std::ofstream& Item::save(std::ofstream& ofstr) const// Writes the current object to a file
	{
		if (*this)// Assuming *this checks the state of the item
		{
			ofstr << sku << "\t" << description << "\t" << quantity << "\t"
				<< needed << "\t";
			ofstr.setf(ios::fixed);
			ofstr.precision(2);
			ofstr << price;
		}
		return ofstr;
	}

	std::ifstream& Item::load(std::ifstream& ifstr) // Reads the current object from a file
	{
		delete[] description;
		description = nullptr;

		ifstr >> sku;
		ifstr.ignore();

		char tempDescription[1001];
		ifstr.getline(tempDescription, 1000, '\t');// Assuming the description is no longer than 1000 characters
		description = new char[strlen(tempDescription) + 1];// Allocate memory for the description
		strcpy(description, tempDescription);// Copy the string into the allocated memory

		ifstr >> quantity;
		ifstr.ignore();
		ifstr >> needed;
		ifstr.ignore();
		ifstr >> price;
		ifstr.ignore();
		if (!ifstr)
		{
			state = "Input file stream read failed!";
		}

		return ifstr;
	}

	std::ostream& Item::display(std::ostream& ostr) const // Writes the current object to the console
	{
		if (*this) // Assuming *this checks the state of the item
		{
			if (isLinear) // Assuming isLinear is set correctly
			{
				ostr << sku << " | ";
				ostr.width(35);
				ostr.fill(' ');
				ostr.setf(ios::left);
				if (description)// Assuming description is not nullptr
				{
					if (strlen(description) > 35)// Assuming description is longer than 35 characters
					{
						ostr << string(description).substr(0, 35) << " | ";
					}
					else// Assuming description is not longer than 35 characters
					{
						ostr << description << " | ";
					}
				}
				ostr.unsetf(ios::left);//
				ostr.width(4);
				ostr.setf(ios::right);
				ostr << quantity << " | "; ostr.width(4);
				ostr << needed << " | ";
				ostr.width(7);
				ostr.setf(ios::fixed);
				ostr.precision(2);
				ostr << price << " |";
				ostr.unsetf(ios::right);
				ostr.unsetf(ios::fixed);
			}
			else
			{
				ostr << "AMA Item:" << endl;
				ostr << sku << ": " << description << endl;
				ostr << "Quantity Needed: " << needed << endl;
				ostr << "Quantity Available: " << quantity << endl;
				ostr << "Unit Price: $";
				ostr.setf(ios::fixed);
				ostr.precision(2);
				ostr << price << std::endl; ostr << "Needed Purchase Fund: $";
				ostr.precision(2);
				double value = (needed - quantity) * price;
				ostr << value << endl;
			}
		}
		else// Assuming state can be output directly
		{
			ostr << state;
		}
		return ostr;
	}

	std::istream& Item::read(std::istream& istr) // Reads the current object from the console
	{
		char tempDescription[1001];
		cout << "AMA Item:\n" << "SKU: " << sku << '\n';
		istr.ignore();
		if (istr)
		{
			cout << "Description: ";
			istr.getline(tempDescription, 1000);
			if (tempDescription[0 != '\0']) // Assuming the description is not empty
			{
				delete[] description; // Deallocate old description
				description = new char[strlen(tempDescription) + 1]; // Allocate memory for new description
				strcpy(description, tempDescription); // Copy the string into the allocated memory

				cout << "Quantity Needed: ";
				needed = ut.getint(1, 9999);
				cout << "Quantity On Hand: ";
				quantity = ut.getint(0, needed);
				cout << "Unit Price: $";
				price = ut.getdouble(0.0, 9999.0);
			}
		}
		else
		{
			state = "Console Entry failed";//
		}
		return istr;
	}

}





