/* Citation and Sources...
Final Project Milestone 5
Module: Status
Filename: Status.h
Version 1.0
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/04 Initial of Status header file.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

#include <iostream>

namespace sdds {
    class Status {
        char* description;
        int code;

    public:
        Status() : description(nullptr), code(0) {};
        Status(const char* desc, int c = 0);
        Status(const Status& other);
        Status& operator=(const Status& other);
        ~Status();
        Status& operator=(int value);



        Status& clear();
        operator int() const;
        operator const char* () const;
        operator bool() const;

        friend std::ostream& operator<<(std::ostream& out, const Status& status);
    };
}
#endif // SDDS_STATUS_H

