#ifndef TUTORIALS_TEMP_CAR_H_
#define TUTORIALS_TEMP_CAR_H_

#include <string>

class Car {
 public:
    Car(){}
    const std::string& getManufacturer() const;
    int getNumSeats() const;
  Car(std::string, int num);
//    virtual ~Car() noexcept;
    //copy constructor
    Car(const Car& );

    //copy assignment
    Car& operator=(const Car&);

    //move constructor
    Car(Car&&) noexcept;

    //move assignment
    Car& operator=(Car&&) noexcept ;

 private:
  std::string manufacturer_;
  int num_seats_;
};

#endif  // TUTORIALS_TEMP_CAR_H_
