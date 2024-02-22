/* Citation and Sources...
Final Project Milestone 5
Module: Menu
Filename: Menu.h
Version 1.0
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/13 Initial of Menu module file.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds {
    class Menu {

        char* menuContext;
        unsigned int numOptions;

    public:
        Menu(const char* MenuContext);
        ~Menu();
        Menu(const Menu&) = delete; // Prevent copying
        Menu& operator=(const Menu&) = delete; // Prevent assignment
        unsigned int run() const; // Displays menu and prompts for input
    };

}

#endif // SDDS_MENU_H
