/* Citation and Sources...
Final Project Milestone 5
Module: Item
Filename: Item.h
Version 1.0
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/19 Initial of Item header file.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "iProduct.h"
#include "Status.h"
namespace sdds
{
	class Item : public iProduct
	{
		double price{};
		int quantity{};
		int needed{};
		char* description{};
		bool isLinear{};
	protected:
		Status state;
		int sku;
		bool linear() const;
	public:
		Item();
		Item(const Item& src);
		Item& operator=(const Item& other);
		~Item();
		int qtyNeeded() const;
		int qty() const;
		operator double() const;
		operator bool() const;
		int operator-=(int qty);
		int operator+=(int qty);
		void linear(bool IsLinear);
		void clear();
		bool operator==(int Sku) const;
		bool operator==(const char* Description) const;
		int readSku(std::istream& istr);
		virtual std::ofstream& save(std::ofstream& ofstr) const;
		virtual std::ifstream& load(std::ifstream& ifstr);
		virtual std::ostream& display(std::ostream& ostr) const;
		virtual std::istream& read(std::istream& istr);
	};
}
#endif


