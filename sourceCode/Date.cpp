/* Citation and Sources...
Final Project Milestone 5
Module: Date
Filename: Date.cpp
Version 1.1
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/04 Initial of Date module file.
2023/11/24 Modify Date module for Milestone 4.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#include "Date.h"
#include <ctime>  
#include <iomanip>
#include <iostream>
#include "Utils.h"
#include "Status.h"

using namespace sdds;

namespace sdds {


    Date::Date() // Default constructor
    {
        ut.getSystemDate(&year, &month, &day); // Set the date to the current system date
        Formatted = true; // Formatted date
        validate(); // Validate the date
    }

    Date::Date(int y, int m, int d) : year(y), month(m), day(d), Formatted(true) // 3 argument constructor
    {
        validate();// validate the date
    }

    bool Date::validate() // Validate the date
    {
        int currentYear; // Current system year
        sdds::ut.getSystemDate(&currentYear); // Set current system year

        if (year < currentYear || year > MAX_YEAR_VALUE) // Check if the year is valid
        {
            State = Status("Invalid year in date", 1);
            return false;
        }

        if (month < 1 || month > 12) // Check if the month is valid
        {
            State = Status("Invalid month in date", 2);
            return false;
        }

        if (day < 1 || day > sdds::ut.daysOfMon(month, year)) // Check if the day is valid
        {
            State = Status("Invalid day in date", 3);
            return false;
        }

        State.clear(); // No errors
        return true;
    }

    int Date::uniqueDateValue() const // Unique date value
    {
        return year * 372 + month * 31 + day;
    }

    // Comparison Operators
    bool Date::operator==(const Date& rhs) const // Equal to operator
    {
        return uniqueDateValue() == rhs.uniqueDateValue();
    }

    bool Date::operator!=(const Date& rhs) const // Not equal to operator
    {
        return uniqueDateValue() != rhs.uniqueDateValue();
    }

    bool Date::operator<(const Date& rhs) const // Less than operator
    {
        return uniqueDateValue() < rhs.uniqueDateValue();
    }

    bool Date::operator>(const Date& rhs) const // Greater than operator
    {
        return uniqueDateValue() > rhs.uniqueDateValue();
    }

    bool Date::operator<=(const Date& rhs) const // Less than or equal to operator
    {
        return uniqueDateValue() <= rhs.uniqueDateValue();
    }

    bool Date::operator>=(const Date& rhs) const // Greater than or equal to operator
    {
        return uniqueDateValue() >= rhs.uniqueDateValue();
    }

    // Modifier for formatted
    Date& Date::formatted(bool format) // Formatted setter
    {
        this->Formatted = format; // Set the format
        return *this;
    }

    const Status& Date::state() const // State getter
    {
        return State;
    }

    Date::operator bool() const
    {
        return State;
    }

    //This function writes a date in the following format YYYY/MM/DD
    std::ostream& Date::write(std::ostream& os) const
    {
        if (Formatted) //If is valid, then print in the format.
        {
            os << std::setfill('0') << std::setw(4) << year << "/"
                << std::setw(2) << month << "/"
                << std::setw(2) << day;
        }
        else // If is not valid, then print in the format.
        {
            os << std::setfill('0') << std::setw(2) << year % 100 // YYMMDD format
                << std::setw(2) << month
                << std::setw(2) << day;
        }
        return os;
    }

    std::istream& Date::read(std::istream& is) // Read the date
    {
        int dateValue;
        is >> dateValue;

        if (is)
        {
            if (dateValue >= 100000) // YYMMDD format
            {
                year = 2000 + dateValue / 10000;
                month = (dateValue / 100) % 100;
                day = dateValue % 100;
            }
            else if (dateValue >= 1000) // MMDD format
            {
                sdds::ut.getSystemDate(&year); // Set the current system year
                month = dateValue / 100;
                day = dateValue % 100;
            }
            else
            {
                std::cout << "ERR#2: Invalid month in date";
                is.setstate(std::ios::failbit);
                return is;
            }

            if (!validate())
            {
                is.setstate(std::ios::failbit);
            }
        }
        else
        {
            is.setstate(std::ios::failbit);
            State = "Invalid date value";
        }
        return is;

    }

    std::ostream& operator<<(std::ostream& os, const Date& d) // Overload helper operator "<<". This function will call write function.
    {
        return d.write(os);
    }

    std::istream& operator>>(std::istream& is, Date& d) // Overload helper operator ">>". This function will call read function.
    {
        return d.read(is);
    }

}

