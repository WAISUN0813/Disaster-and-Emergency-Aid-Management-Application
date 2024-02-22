/* Citation and Sources...
Final Project Milestone 5
Module: Perishable
Filename: Perishable.h
Version 1.0
Author	WAI SUN LAM
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/24 Initial of Perishable header file.
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h" 

namespace sdds {

    class Perishable : public Item {
    private:
        Date m_expiryDate;
        char* m_handling;

    public:
        Perishable();
        Perishable(const Perishable& other);
        Perishable& operator=(const Perishable& other);
        ~Perishable();
        const Date& expiry() const;
        int readSku(std::istream& istr);
        std::ofstream& save(std::ofstream& ofstr) const;
        std::ifstream& load(std::ifstream& ifstr);
        std::ostream& display(std::ostream& ostr) const;
        std::istream& read(std::istream& istr);
    };

} // namespace sdds

#endif // SDDS_PERISHABLE_H
