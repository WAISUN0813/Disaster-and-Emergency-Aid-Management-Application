/* Citation and Sources...
Final Project Milestone 5
Module: Status
Filename: Status.cpp
Version 1.0
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/04 Initial of Status module file.
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
#include "Status.h"
#include "Utils.h"
#include <cstring>

using namespace std;

namespace sdds {

    Status::Status(const char* desc, int c) : description(nullptr), code(c) // 2 argument constructor
    {
        if (desc)
        {
            description = new char[strlen(desc) + 1];
            strcpy(description, desc);
        }
    }

    Status::Status(const Status& other) : description(nullptr), code(other.code) // Copy constructor
    {
        if (other.description)
        {
            description = new char[strlen(other.description) + 1];
            strcpy(description, other.description);
        }
    }

    Status& Status::operator=(const Status& other) // Copy assignment operator
    {
        if (this != &other)
        {
            delete[] description; // free existing memory
            description = nullptr;
            code = other.code;
            if (other.description)
            {
                description = new char[strlen(other.description) + 1];
                strcpy(description, other.description);
            }
        }
        return *this;
    }

    Status::~Status() // Destructor
    {
        delete[] description;
    }

    Status& Status::operator=(int value) // Integer assignment operator
    {
        code = value;
        return *this;
    }

    Status& Status::clear() // Clear the status
    {
        delete[] description;
        description = nullptr;
        code = 0;
        return *this;
    }

    Status::operator int() const // Integer conversion operator
    {
        return code;
    }

    Status::operator const char* () const // String conversion operator
    {
        return description;
    }

    Status::operator bool() const // Boolean conversion operator
    {
        return description == nullptr;
    }

    ostream& operator<<(ostream& out, const Status& status) // Output operator
    {
        if (!status)
        {
            if (status.code != 0)
            {
                out << "ERR#" << status.code << ": ";
            }
            out << status.description;
        }
        return out;
    }
};

