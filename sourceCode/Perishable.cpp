/* Citation and Sources...
Final Project Milestone 5
Module: Perishable
Filename: Perishable.cpp
Version 1.0
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/24 Initial of Perishable module file.
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
#include <fstream>
#include <cstring>
#include "Perishable.h"
#include "Utils.h"

using namespace std;
namespace sdds
{
	Perishable::Perishable() : Item(), m_handling(nullptr) {}// Default constructor

	Perishable::Perishable(const Perishable& other) : Item(other), m_handling(nullptr)// Copy constructor
	{
		*this = other;
	}

	Perishable& Perishable::operator=(const Perishable& other) // Copy assignment operator
	{
		if (this != &other) {
			Item::operator=(other);  // Call the base class assignment operator
			m_expiryDate = other.m_expiryDate;
			delete[] m_handling;
			m_handling = nullptr;
			if (other.m_handling && other.m_handling[0])
			{
				m_handling = new char[strlen(other.m_handling) + 1];
				strcpy(m_handling, other.m_handling);
			}
		}
		return *this;
	}

	Perishable::~Perishable() // Destructor
	{
		delete[] m_handling;
		m_handling = nullptr;
	}

	const Date& Perishable::expiry() const // Returns the expiry date
	{
		return m_expiryDate;
	}

	int Perishable::readSku(std::istream& istr) // Reads the SKU from the istream object
	{
		cout << "SKU: ";
		sku = ut.getint(10000, 39999);
		return sku;
	}

	std::ofstream& Perishable::save(std::ofstream& ofstr) const // Writes the SKU, name, price, quantity, needed, and expiry date to the ofstream object
	{
		if (*this)
		{
			Item::save(ofstr);// Call the base class save function
			ofstr << '\t';
			if (m_handling && m_handling[0])
			{
				ofstr << m_handling;
			}
			ofstr << '\t';
			Date date = m_expiryDate;// Write the expiry date
			date.formatted(false);// Set the date to YYYY/MM/DD format
			ofstr << date;// Write the date to the ofstream object
		}
		return ofstr;
	}

	std::ifstream& Perishable::load(std::ifstream& ifstr) // Reads the SKU, name, price, quantity, needed, and expiry date from the ifstream object
	{
		state.clear();// Clear the error state
		Item::load(ifstr);// Call the base class load function
		char temp[1000];
		ifstr.getline(temp, 1000, '\t');// Read the handling instructions
		m_expiryDate.read(ifstr);// Read the expiry date
		delete[] m_handling;
		m_handling = nullptr;
		m_handling = new char[strlen(temp) + 1];
		strcpy(m_handling, temp);
		if (!ifstr)
		{
			state = ("Input file stream read (perishable) failed!");
		}
		return ifstr;
	}

	std::ostream& Perishable::display(std::ostream& ostr) const
	{
		if (*this)
		{
			if (linear())
			{
				Item::display(ostr);// Call the base class display function
				if (m_handling && m_handling[0])
				{
					ostr << '*';
				}
				else
				{
					ostr << ' ';
				}

				ostr << m_expiryDate;
			}
			else
			{
				ostr << "Perishable ";
				Item::display(ostr);// Call the base class display function
				ostr << "Expiry date: ";
				ostr << m_expiryDate << endl;
				if (m_handling && m_handling[0])
				{
					ostr << "Handling Instructions: " << m_handling << endl;
				}
			}
		}
		else
		{
			ostr << state;
		}
		return ostr;
	}

	std::istream& Perishable::read(std::istream& istr)
	{
		Item::read(istr);// Call the base class read function
		delete[] m_handling;
		m_handling = nullptr;
		char temp[1000];
		cout << "Expiry date (YYMMDD): ";
		istr >> m_expiryDate;// Read the expiry date
		istr.ignore();
		cout << "Handling Instructions, ENTER to skip: " << endl;
		if (istr.peek() != '\n')// Read the handling instructions
		{
			istr.getline(temp, 1000, '\n');
			m_handling = new char[strlen(temp) + 1];
			strcpy(m_handling, temp);
		}
		else
		{
			istr.clear();
		}
		if (!istr)
		{
			state = ("Perishable console date entry failed!");
		}
		return istr;
	}


}

