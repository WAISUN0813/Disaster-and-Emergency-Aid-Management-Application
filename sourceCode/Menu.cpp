/* Citation and Sources...
Final Project Milestone 5
Module: Menu
Filename: Menu.cpp
Version 1.1
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/13 Initial of Menu module file.
2023/11/29 Modify Menu module for Milestone 5.2.
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
#include "Menu.h"
#include <iostream>
#include <cstring>
#include <limits>


using namespace std;
namespace sdds
{

    Menu::Menu(const char* MenuContext)// Constructor
    {
        if (MenuContext == nullptr)// If the argument is null, set to invalid
        {
            menuContext = nullptr;
            numOptions = 0;
        }
        else
        {
            numOptions = 1;// At least one option
            for (const char* ptr = MenuContext; *ptr != '\0'; ptr++) // Count number of tabs
            {
                if (*ptr == '\t') numOptions++;
            }
            // If more than 15 options, set to invalid
            if (numOptions > 15)
            {
                menuContext = nullptr;
                numOptions = 0;
            }
            else
            {
                menuContext = new char[strlen(MenuContext) + 1];
                strcpy(menuContext, MenuContext);
            }
        }
    }

    Menu::~Menu()// Destructor
    {
        delete[] menuContext;
    };


    unsigned Menu::run() const// Display menu and return user selection
    {
        if (!menuContext)
        {
            cout << "Invalid Menu!\n";
            return 0;
        }

        const char* temp = menuContext;
        for (unsigned int i = 0; i < numOptions; i++)
        {
            cout << i + 1 << "- "; // Display option number
            while (*temp && *temp != '\t')
            {
                cout << *temp; // Display the option text
                ++temp;
            }
            if (*temp == '\t') ++temp; // Skip the tab character
            cout << endl;
        }
        cout << "0- Exit\n> ";
        unsigned int selectedOption;
        bool validInput = false;

        do {
            cin >> selectedOption;// Get user input

            if (cin.fail()) // If input is not an integer
            {
                cin.clear(); // Clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cout << "Invalid Integer, retry: ";
            }
            else if (selectedOption > numOptions || selectedOption < 0) // If input is out of range
            {
                cout << "Value out of range [0<=" << "val" << "<=" << numOptions << "]: ";
            }
            else
            {
                validInput = true;
            }
        } while (!validInput);

        return selectedOption;
    }
}

