/* Citation and Sources...
Final Project Milestone 5
Module: Date
Filename: Date.h
Version 1.0
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/04 Initial of Date header file.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include "Status.h"
#include "Utils.h"

namespace sdds {
    const int MAX_YEAR_VALUE = 2030;
    class Date {
        int year, month, day;
        Status State;
        bool Formatted;
        bool validate();
        int uniqueDateValue() const;
    public:
        Date();
        Date(int y, int m, int d);
        Date& formatted(bool flag);
        const Status& state() const;
        bool operator==(const Date& rhs) const;
        bool operator!=(const Date& rhs) const;
        bool operator<(const Date& rhs) const;
        bool operator>(const Date& rhs) const;
        bool operator<=(const Date& rhs) const;
        bool operator>=(const Date& rhs) const;
        operator bool() const;
        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);
    };

    std::ostream& operator<<(std::ostream& os, const Date& date);
    std::istream& operator>>(std::istream& is, Date& date);
}

#endif // SDDS_DATE_H

