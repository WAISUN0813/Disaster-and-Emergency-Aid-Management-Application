/* Citation and Sources...
Final Project Milestone 5
Module: iProduct
Filename: iProduct.h
Version 1.0
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/19 Initial of iProduct header file.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SDDS_IPRODUCT_H
#define SDDS_IPRODUCT_H
#include <iostream>
namespace sdds
{
	class iProduct
	{
	public:
		virtual int readSku(std::istream& istr) = 0;//read the sku from the istream
		virtual int operator-=(int qty) = 0;//subtract the qty from the current object
		virtual int operator+=(int qty) = 0;//add the qty to the current object
		virtual operator double() const = 0;//return the total cost of the product
		virtual operator bool() const = 0;//return true if the object is not empty
		virtual int qtyNeeded() const = 0;//return the qty needed
		virtual int qty() const = 0;//return the qty on hand
		virtual void linear(bool isLinear) = 0;//set the linear flag
		virtual std::ofstream& save(std::ofstream& ofstr) const = 0;//save the product to the file
		virtual std::ifstream& load(std::ifstream& ifstr) = 0;//load the product from the file
		virtual std::ostream& display(std::ostream& ostr) const = 0;//display the product
		virtual std::istream& read(std::istream& istr) = 0;//read the product from the istream
		virtual bool operator==(int sku) const = 0;//return true if the sku is the same as the object
		virtual bool operator==(const char* description) const = 0;//return true if the description is the same as the object
		virtual ~iProduct() {};//virtual destructor
	};
	std::ostream& operator<<(std::ostream& os, const iProduct& i);
	std::istream& operator>>(std::istream& is, iProduct& i);
}
#endif




