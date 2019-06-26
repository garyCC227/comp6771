//
// Created by garycc227 on 24/06/19.
//

#include "tutorials/Bank/bank.h"

#include <iostream>
Bank::Bank(){}  // default constructor... dont use it, since we dont have setter and wont;

Bank::Bank(std::string acname, int acno, double deposite)
  : account_number_{acno}, deposite_{deposite}, account_name_{acname} {}
Bank::Bank(const Bank& old_bank)
  : account_number_{old_bank.account_number_}, deposite_{old_bank.deposite_},
    account_name_{old_bank.account_name_} {
    std::cout << "I am copy constructor \n";
}

Bank& Bank::operator=(const Bank& old_bank) {
    std::cout << "I am copy assignment\n";
  if(&old_bank == this)
      return *this;

  this->account_name_ = old_bank.account_name_;
  this->account_number_ = old_bank.account_number_;
  this->deposite_ = old_bank.deposite_;

  return *this;
}
Bank::Bank(Bank&&) noexcept {}
Bank& Bank::operator=(Bank&&) noexcept {
  return <#initializer #>;
}
void Bank::ShowAccount() const {}
void Bank::Withdraw(const float& amount) {}
void Bank::Deposite(const float& amount) {}
