/* Citation and Sources...
Final Project Milestone 5
Module: Utils
Filename: Utils.cpp
Version 1.1
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/04 Initial of Utils module file.
2023/11/19 Modify Utils module for Milestone 3.
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
#include <iomanip>
#include <ctime>
#include "Utils.h"
using namespace std;
namespace sdds
{
    Utils ut;
    void Utils::testMode(bool testmode)
    {
        m_testMode = testmode;
    }
    void Utils::getSystemDate(int* year, int* mon, int* day)
    {
        if (m_testMode)
        {
            if (day) *day = sdds_testDay;
            if (mon) *mon = sdds_testMon;
            if (year) *year = sdds_testYear;
        }
        else
        {
            time_t t = std::time(NULL);
            tm lt = *localtime(&t);
            if (day) *day = lt.tm_mday;
            if (mon) *mon = lt.tm_mon + 1;
            if (year) *year = lt.tm_year + 1900;
        }
    }
    int Utils::daysOfMon(int month, int year)const
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    int Utils::getint(int minValue, int maxValue, const char* prompt, const char* errMes)
    {
        int returnValue;
        bool keepAsking = true;
        do
        {
            if (prompt) cout << prompt;
            cin >> returnValue;
            if (cin.fail())
            {
                cin.clear();
                while (cin.get() != '\n');
                cout << "Invalid Integer, retry: ";
            }
            else
            {
                char nextChar = cin.peek();
                if (nextChar != '\n')
                {
                    cout << "Invalid Integer, retry: ";
                    while (cin.get() != '\n');
                }
                else if (returnValue < minValue || returnValue > maxValue)
                {
                    if (errMes)
                    {
                        cout << errMes << ", retry: ";
                    }
                    else
                    {
                        cout << "Value out of range [" << minValue << "<=val<=" << maxValue << "]: ";
                    }
                    cin.ignore();
                }
                else
                {
                    keepAsking = false;
                }
            }
        } while (keepAsking);

        return returnValue;
    }


    double Utils::getdouble(double minValue, double maxValue, const char* prompt, const char* errMes)
    {
        double returnValue;
        bool keepAsking = true;
        do
        {
            if (prompt) cout << prompt;
            cin >> returnValue;
            if (cin.fail())
            {
                cin.clear();
                while (cin.get() != '\n');
                cout << "Invalid number, retry: ";
            }
            else
            {
                char nextChar = cin.peek();
                if (nextChar != '\n')
                {
                    cout << "Invalid number, retry: ";
                    while (cin.get() != '\n');
                }
                else if (returnValue < minValue || returnValue > maxValue)
                {
                    if (errMes)
                    {
                        cout << errMes << ", retry: ";
                    }
                    else
                    {
                        cout << "Value out of range [" << fixed << setprecision(2) << minValue << "<=val<=" << fixed << setprecision(2) << maxValue << "]: ";
                    }
                    cin.ignore();
                }
                else
                {
                    keepAsking = false;
                }
            }
        } while (keepAsking);

        return returnValue;
    }

};



