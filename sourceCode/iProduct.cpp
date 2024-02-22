/* Citation and Sources...
Final Project Milestone 5
Module: iProduct
Filename: iProduct.cpp
Version 1.0
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/19 Initial of iProduct module file.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#include "iProduct.h"
namespace sdds
{
	std::ostream& operator<<(std::ostream& os, const iProduct& i)
	{
		return i.display(os);
	}
	std::istream& operator>>(std::istream& is, iProduct& i)
	{
		return i.read(is);
	}
}

