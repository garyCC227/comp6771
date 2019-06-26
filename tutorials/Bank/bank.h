//
// Created by garycc227 on 24/06/19.
//

#ifndef COMP6771_BANK_H
#define COMP6771_BANK_H

#include <iostream>
#include <string>

class Bank {
    public:
       Bank();
       explicit Bank(std::string,int acno, double deposite);
       //copy constructor and assignment
       Bank(const Bank&);
       Bank& operator=(const Bank&);

       //move constructor and assignment
       Bank(Bank&&) noexcept;
       Bank& operator=(Bank&&) noexcept;

       //basic function for bank system
       void ShowAccount() const;
       void Withdraw(const float& amount);
       void Deposite(const float& amount);


    private:
        int account_number_;
        double deposite_;
        std::string account_name_;

};


#endif //COMP6771_BANK_H
