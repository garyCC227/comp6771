#include <iostream>
#include <utility>

#include "tutorials/temp/car.h"

int main() {
  Car one;
  Car two{"Toyota", 5};

  Car three{two};

  Car four = std::move(one);

  Car five{std::move(two)};

  three = five;

  four = std::move(five);
  std::cout << four.getNumSeats() << '\n';
    return 0;
}
