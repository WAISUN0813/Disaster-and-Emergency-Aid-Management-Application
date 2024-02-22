/* Citation and Sources...
Final Project Milestone 5
Module: AidMan
Filename: AidMan.cpp
Version 1.5
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/13 Initial of AidMan module file.
2023/11/28 Modify AidMan module for Milestone 5.1.
2023/11/29 Modify AidMan module for Milestone 5.2.
2023/12/29 Modify AidMan module for Milestone 5.3.
2023/12/01 Modify AidMan module for Milestone 5.4.
2023/12/02 Modify AidMan module for Milestone 5.5.
2023/12/02 Modify AidMan module for Milestone 5.6.
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
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Perishable.h"
#include "Item.h"
#include "AidMan.h"
#include "Utils.h"
#include "Date.h"


using namespace std;
namespace sdds
{

    AidMan::AidMan() : m_filename(nullptr), numOfProducts(0), mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database\n---------------------------------")
    {

        for (int i = 0; i < sdds_max_num_items; i++)
        {
            productArray[i] = nullptr;
        };
    }


    AidMan::~AidMan()
    {
        delete[] m_filename;
        deallocate();
    }

    unsigned int AidMan::menu() const
    {
        cout << "Aid Management System" << endl;
        cout << "Date: " << Date() << endl;
        cout << "Data file: ";
        if (m_filename == nullptr)
        {
            cout << "No file" << endl;
        }
        else
        {
            cout << m_filename << endl;
        }
        cout << "---------------------------------" << endl;
        return mainMenu.run();
    }


    void AidMan::run()
    {
        bool done = false;
        unsigned int selection;
        do
        {
            selection = menu();

            if (selection != 0 && m_filename == nullptr && selection != 7)
            {
                selection = 7;
            }

            if (selection == 0)
            {
                done = true;
            }
            else if (selection == 1)
            {
                cout << endl << "****List Items****" << endl;
                int numOfItemsListed = list();//list all items
                cin.ignore(10000, '\n'); //ignore newline
                cout << "Enter row number to display details or <ENTER> to continue:\n> ";
                if (cin.peek() != '\n') //if user enters a row number
                {
                    int choice = ut.getint(1, numOfItemsListed);//get row number
                    productArray[choice - 1]->linear(false);//display in non-linear format
                    productArray[choice - 1]->display(cout) << endl;//display the product
                }
                cout << endl;
            }
            else if (selection == 2)
            {
                cout << "\n****Add Item****\n";
                if (numOfProducts >= sdds_max_num_items)//if database is full
                {
                    cout << "Database full!" << endl;
                }
                else
                {
                    Menu productTypeMenu("Perishable\tNon-Perishable\n-----------------");
                    int choice = productTypeMenu.run();//get user's choice

                    if (choice == 0)//if user chooses to exit
                    {
                        cout << "Aborted" << endl;
                    }
                    else
                    {
                        iProduct* newProduct = nullptr;//create a new product
                        if (choice == 1) //if user chooses perishable
                        {
                            newProduct = new Perishable();//create new perishable
                        }
                        else if (choice == 2)//if user chooses non-perishable
                        {
                            newProduct = new Item();//create new item
                        }

                        if (newProduct)//if newProduct is not nullptr
                        {
                            int newSKU = newProduct->readSku(cin);//read SKU

                            if (search(newSKU) != -1) //if SKU already exists
                            {
                                cout << "Sku: " << newSKU << " is already in the system, try updating quantity instead." << endl << endl;//display error message
                                delete newProduct;//delete newProduct
                            }
                            else
                            {
                                newProduct->read(cin);//read the product
                                if (*newProduct) //if product is not empty
                                {
                                    productArray[numOfProducts++] = newProduct;//add newProduct to productArray
                                }
                                else
                                {
                                    newProduct->display(cout);//display the product
                                    delete newProduct;//delete newProduct
                                }
                            }
                        }
                    }
                }
            }
            else if (selection == 3)
            {
                cout << "\n****Remove Item****\n";
                cout << "Item description: ";
                char desc[100];//create a char array to hold description
                cin.ignore();//ignore newline
                cin.getline(desc, 100, '\n');//get description
                int itemsListed = list(desc);//list all items with the same description
                if (itemsListed > 0)//if there are items with the same description
                {
                    cout << "Enter SKU: ";
                    int sku = ut.getint(10000, 99999);//get SKU
                    int index = search(sku);//search for SKU
                    if (search(sku) == -1)//if SKU is not found
                    {
                        cout << "SKU not found!" << endl;
                    }
                    else
                    {
                        cout << "Following item will be removed: " << endl;
                        productArray[index]->linear(false);//display in non-linear format
                        productArray[index]->display(cout) << endl;//display the product
                        cout << "Are you sure?" << endl;
                        Menu confirmMenu("Yes!");//create a menu
                        int choice = confirmMenu.run();//get user's choice
                        if (choice == 1)
                        {
                            remove(index);
                            cout << "Item removed!" << endl << endl;
                        }
                        else
                        {
                            cout << "Aborted!" << endl;
                        }
                    }
                }
            }
            else if (selection == 4)
            {
                cout << "\n****Update Quantity****\n";
                cout << "Item description: ";
                char desc[100];//create a char array to hold description
                cin.ignore();//ignore newline
                cin.getline(desc, 100, '\n');//get description
                int itemsListed = list(desc);//list all items with the same description
                if (itemsListed > 0)//if there are items with the same description
                {
                    cout << "Enter SKU: ";
                    int sku = ut.getint(10000, 99999);//get SKU
                    int index = search(sku);//search for SKU
                    if (search(sku) == -1)//if SKU is not found
                    {
                        cout << "SKU not found!" << endl;
                    }
                    else
                    {
                        Menu quantityMenu("Add\tReduce");
                        int choice = quantityMenu.run();

                        if (choice == 1) // Add
                        {
                            // Check if there's quantity needed to add
                            if (productArray[index]->qtyNeeded() > productArray[index]->qty())
                            {
                                cout << "Quantity to add: ";
                                int addable = productArray[index]->qtyNeeded() - productArray[index]->qty();
                                int quantity = ut.getint(1, addable);
                                *productArray[index] += quantity;//add quantity to productArray[index]
                                cout << quantity << " items added!" << endl << endl;
                            }
                            else
                            {
                                cout << "Quantity Needed already fulfilled!" << endl << endl;
                            }
                        }
                        else if (choice == 2)
                        {  // Reduce
                            // Check if there's quantity available to reduce
                            if (productArray[index]->qty() > 0)
                            {
                                cout << "Quantity to reduce: ";
                                int quantity = ut.getint(1, productArray[index]->qty());
                                *productArray[index] -= quantity;//reduce quantity from productArray[index]
                                cout << quantity << " items removed!" << endl << endl;
                            }
                            else
                            {
                                cout << "Quantity on hand is 0!" << endl << endl;
                            }
                        }
                        else if (choice == 0)
                        {
                            cout << "Aborted!" << endl << endl;
                        }
                    }
                }
            }
            else if (selection == 5)
            {
                cout << "\n****Sort****\n";
                sort();
            }
            else if (selection == 6)
            {
                cout << "\n****Ship Items****\n";
                shipItems();

            }
            else if (selection == 7)
            {
                cout << "\n****New/Open Aid Database****\n";
                load();
            }

        } while (!done);

        if (m_filename != nullptr)
        {
            save();
            deallocate();
        }

        cout << "Exiting Program!" << endl;
    }


    void AidMan::save()
    {
        if (m_filename != nullptr)
        {
            ofstream file(m_filename);
            for (int i = 0; i < numOfProducts; ++i)
            {
                productArray[i]->save(file);
                file << endl;
            }
            file.close();
        }
    }

    void AidMan::deallocate()
    {
        for (int i = 0; i < numOfProducts; ++i)
        {
            delete productArray[i];
            productArray[i] = nullptr;
        }
        numOfProducts = 0;
    }

    void AidMan::load()
    {
        save();
        deallocate();

        cout << "Enter file name: ";
        char filename[50];
        cin >> ws;//remove whitespace
        cin.getline(filename, 50);

        m_filename = new char[strlen(filename) + 1];
        strcpy(m_filename, filename);

        ifstream file(m_filename);//open file
        if (!file) //if file does not exist
        {
            cout << "Failed to open " << m_filename << " for reading!" << endl;
            cout << "Would you like to create a new data file?" << endl;
            cout << "1- Yes!" << endl;
            cout << "0- Exit" << endl;
            int selection;
            cin >> selection;
            if (selection == 1)
            {
                ofstream file(m_filename);//create file
                file.close();//close file
            }
            else {
                exit(0);//exit program
            }
        }
        else {
            char type;
            while (file >> type) //while file is not empty
            {
                file.unget();  //put back the character

                if (type >= '1' && type <= '3') //if type is perishable
                {
                    productArray[numOfProducts] = new Perishable();//create new perishable
                }
                else if (type >= '4' && type <= '9') //if type is non-perishable
                {
                    productArray[numOfProducts] = new Item();//create new item
                }
                else
                {
                    file.setstate(ios::failbit);//set failbit
                    break;
                }

                if (file && productArray[numOfProducts]->load(file)) //if file is not empty and load is successful
                {
                    numOfProducts++;
                }
                else {
                    delete productArray[numOfProducts];
                    productArray[numOfProducts] = nullptr;
                }
            }
            if (numOfProducts > 0)
            {
                cout << numOfProducts << " records loaded!" << endl << endl;

            }
        }
    }

    int AidMan::list(const char* sub_desc)
    {
        int numOfItemsListed = 0;
        cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
        cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

        for (int i = 0; i < numOfProducts; i++)
        {
            if (!sub_desc || *productArray[i] == sub_desc)//if sub_desc is nullptr or productArray[i] contains sub_desc
            {
                productArray[i]->linear(true);  //display in linear format
                cout << setfill(' ') << setw(4) << i + 1 << " | ";
                productArray[i]->display(cout); //display the product
                cout << endl;
                numOfItemsListed++;
            }
        }

        if (numOfItemsListed == 0)//if no items are listed
        {
            cout << "The list is empty!" << endl;
        }

        cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        return numOfItemsListed;
    }

    int AidMan::search(int sku) const //search for sku
    {
        for (int i = 0; i < numOfProducts; ++i)
        {
            if (*productArray[i] == sku)
            {
                return i;
            }
        }
        return -1;
    }

    void AidMan::remove(int index)
    {
        delete productArray[index];  // Delete the product at the index
        for (int i = index; i < numOfProducts - 1; ++i) {
            productArray[i] = productArray[i + 1];  // Shift elements to the left
        }
        productArray[numOfProducts - 1] = nullptr;  // Nullify the last element
        numOfProducts--;  // Decrease the count of products
    }

    void AidMan::sort()
    {
        for (int i = 1; i < numOfProducts; i++) //for each product in the array
        {
            iProduct* diff = productArray[i];//get the product at index i

            int j = i - 1;//get the index of the previous product
            while (j >= 0 && (productArray[j]->qtyNeeded() - productArray[j]->qty()) < (diff->qtyNeeded() - diff->qty()))
            {
                productArray[j + 1] = productArray[j];//move the previous product to the next index
                j = j - 1;//decrease j by 1
            }
            productArray[j + 1] = diff;//insert the current product into the sorted sequence
        }

        cout << "Sort completed!" << endl << endl;
    }


    void AidMan::shipItems() 
    {
        ofstream outFile("shippingOrder.txt");
     
        Date date;
        outFile << "Shipping Order, Date: " << date << endl;
        outFile << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
        outFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

        int row = 1;
        int count = 0;
        for (int i = 0; i < numOfProducts; ++i) 
        {
            if (productArray[i]->qtyNeeded() == productArray[i]->qty()) //if quantity needed is equal to quantity on hand
            {
                    productArray[i]->linear(true);
                    outFile << setfill(' ') << setw(4) << row++ << " | ";
                    productArray[i]->display(outFile);
                    outFile << endl;
                    delete productArray[i];//delete productArray[i]
                    productArray[i] = nullptr;//set productArray[i] to nullptr
                    count++;//increment shippedCount
            }
        }

        int index = 0;
        for (int i = 0; i < numOfProducts; ++i) //for each product in productArray
        {
            if (productArray[i] != nullptr) //if productArray[i] is not nullptr
            {
                productArray[index++] = productArray[i];//move productArray[i] to productArray[index]
            }
        }
        numOfProducts = index;//set numOfProducts to index

        outFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        outFile.close();

        cout << "Shipping Order for " << count << " times saved!" << endl << endl;
    }
}