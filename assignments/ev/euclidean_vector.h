#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <cassert>
#include <cmath>
#include <exception>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // constructor
  explicit EuclideanVector(int i = 1);
  EuclideanVector(int, double);
  EuclideanVector(std::vector<double>::const_iterator, std::vector<double>::const_iterator);

  // copy and move constructor and assignment
  EuclideanVector(const EuclideanVector&);
  EuclideanVector(EuclideanVector&&) noexcept;
  EuclideanVector& operator=(const EuclideanVector&);
  EuclideanVector& operator=(EuclideanVector&&) noexcept;

  // destructor
  ~EuclideanVector() = default;

  // member operator functions
  double operator[](int i) const;  // [] getter
  double& operator[](int i);       // [] modifier
  EuclideanVector& operator+=(const EuclideanVector&);
  EuclideanVector& operator-=(const EuclideanVector&);
  EuclideanVector& operator*=(double);
  EuclideanVector& operator/=(double);

  // type conversion operator
  explicit operator std::vector<double>() const;
  explicit operator std::list<double>() const;

  // methods
  int GetNumDimensions() const;
  double at(int) const;
  double& at(int);
  double GetEuclideanNorm() const;
  EuclideanVector CreateUnitVector() const;

  // friend operator functions
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);
  friend bool operator==(const EuclideanVector&, const EuclideanVector&);
  friend bool operator!=(const EuclideanVector&, const EuclideanVector&);
  friend EuclideanVector operator+(const EuclideanVector&, const EuclideanVector&);
  friend EuclideanVector operator-(const EuclideanVector&, const EuclideanVector&);
  friend double operator*(const EuclideanVector&, const EuclideanVector&);  // dot product
  friend EuclideanVector operator*(const EuclideanVector&, double);         // scalar multiplication
  friend EuclideanVector operator/(const EuclideanVector&, double);         // scalar division

 private:
  int dimension_;
  std::unique_ptr<double[]> magnitudes_;
};

std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);
bool operator==(const EuclideanVector&, const EuclideanVector&);
bool operator!=(const EuclideanVector&, const EuclideanVector&);
EuclideanVector operator+(const EuclideanVector&, const EuclideanVector&);
EuclideanVector operator-(const EuclideanVector&, const EuclideanVector&);
double operator*(const EuclideanVector&, const EuclideanVector&);  // dot product
EuclideanVector operator*(const EuclideanVector&, double);         // scalar multiplication
EuclideanVector operator/(const EuclideanVector&, double);         // scalar division

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
