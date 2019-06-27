#include "tutorials/week3/car.h"

#include <iostream>
// TODO(tutorial): fill me in

Car::Car(std::string input, int num):manufacturer_{input},num_seats_{num} {

}
Car::Car(const Car& old_car) :manufacturer_{old_car.manufacturer_}, num_seats_{old_car.num_seats_}{
    //dsa
    std::cout << "I am copy constructor\n";
}
Car& Car::operator=(const Car& old_car) {
    std::cout << "I am copy assignement\n";

    if(&old_car == this){
        return *this;
    }
    this->manufacturer_ = old_car.manufacturer_;
    this->num_seats_ = old_car.num_seats_;

    return *this;
}
Car::Car( Car&& old_car) noexcept :manufacturer_{old_car.manufacturer_}, num_seats_{old_car.num_seats_}{
    std::cout << "I am move constructor\n";


    old_car.manufacturer_ = "";
    old_car.num_seats_ = 0;

}
Car& Car::operator=(Car&& old_car) noexcept{

    std::cout <<"I am move assignment\n";
    //avoid self assignment
    if(&old_car == this){
        return *this;
    }

    this->manufacturer_ = old_car.manufacturer_;
    this->num_seats_ = old_car.num_seats_;

    old_car.manufacturer_ = "";
    old_car.num_seats_ = 0;

    return *this;
}
