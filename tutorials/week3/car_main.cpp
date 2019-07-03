#include <iostream>
#include <utility>

#include "tutorials/week3/car.h"

int main() {
  Car one;
  Car two{"Toyota", 5};
  Car three = two;
  //Car three{two};

  Car four = std::move(one);
//
//  Car five{std::move(two)};
//
//  three = five;
//
//  four = std::move(five);

    return 0;
}
