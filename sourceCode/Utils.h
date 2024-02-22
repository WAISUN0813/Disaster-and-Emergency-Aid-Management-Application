/* Citation and Sources...
Final Project Milestone 5
Module: Utils
Filename: Utils.h
Version 1.1
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/04 Initial of Utils header file.
2023/11/19 Modify Utils header for Milestone 3.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
namespace sdds {
    const int sdds_testYear = 2023;
    const int sdds_testMon = 12;
    const int sdds_testDay = 9;
    class Utils {
        bool m_testMode = false;
    public:
        void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
        int daysOfMon(int mon, int year)const;
        void testMode(bool testmode = true);
        int getint(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);
        double getdouble(double minValue, double maxValue, const char* prompt = nullptr, const char* errMes = nullptr);
    };
    extern Utils ut;
}

#endif // !SDDS_UTILS_H

