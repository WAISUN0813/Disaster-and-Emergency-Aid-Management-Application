/* Citation and Sources...
Final Project Milestone 5
Module: AidMan
Filename: AidMan.h
Version 1.2
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/13 Initial of AidMan header file.
2023/11/28 Modify of AidMan header file.
2023/11/29 Modify of AidMan header file.
2023/12/02 Modify of AidMan header file.
2023/12/02 Modify of AidMan header file.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include "Menu.h"
#include "iProduct.h"

namespace sdds {
    const int sdds_max_num_items = 100;
    class AidMan {
        char* m_filename; // Dynamically holds the name of the data file
        int numOfProducts; // Number of products read from the data file
        Menu mainMenu;  // Menu object for the main menu
        iProduct* productArray[sdds_max_num_items]; // Dynamically holds the products
        // Private method to display the menu and get user's selection
        unsigned menu() const;

    public:
        // One-argument constructor that initializes the main menu
        AidMan();
        // Destructor to prevent memory leak
        ~AidMan();
        // Preventing copying and assignment
        AidMan(const AidMan&) = delete;
        AidMan& operator=(const AidMan&) = delete;

        // Public method to run the application
        void run();
        void save();
        void deallocate();
        void load();
        int list(const char* sub_desc = nullptr);
        int search(int sku) const;
        void remove(int index);
        void sort();
        void shipItems();
    };
}

#endif // SDDS_AIDMAN_H
