#include "assignments/ev/euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm
#include <iostream>

EuclideanVector::EuclideanVector(int i)
  : dimension_{i}, magnitudes_{std::make_unique<double[]>(i)} {
  //    std::cout << "default constructor\n";
}

EuclideanVector::EuclideanVector(int i, double magnitude)
  : dimension_{i}, magnitudes_{std::make_unique<double[]>(i)} {
  for (int j = 0; j < i; j++) {
    magnitudes_[j] = magnitude;
  }
}
EuclideanVector::EuclideanVector(std::vector<double>::const_iterator begin,
                                 std::vector<double>::const_iterator end) {
  // initialize dimension
  dimension_ = end - begin;
  magnitudes_ = std::make_unique<double[]>(dimension_);

  int i = 0;
  for (; begin != end; ++begin) {
    magnitudes_[i] = *begin;
    ++i;
  }
}

EuclideanVector::EuclideanVector(const EuclideanVector& old)
  : dimension_{old.dimension_}, magnitudes_{std::make_unique<double[]>(dimension_)} {
  //    std::cout << "copy constructor there\n";
  // copy the content of old
  for (int i = 0; i < dimension_; ++i) {
    this->magnitudes_[i] = old.magnitudes_[i];
  }
}

EuclideanVector::EuclideanVector(EuclideanVector&& old) noexcept
  : dimension_{old.dimension_}, magnitudes_{std::move(old.magnitudes_)} {
  //    std::cout << "move constructor there\n";
  old.dimension_ = 0;
  old.magnitudes_ = std::make_unique<double[]>(0);
}
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& old) {
  //    std::cout << "copy assignment there\n";
  // avoid self assignment
  if (&old != this) {
    if (this->dimension_ != old.dimension_) {
      this->dimension_ = old.dimension_;
      this->magnitudes_ = std::make_unique<double[]>(dimension_);  // free before assignment
    }

    // copy the content of old
    for (int i = 0; i < dimension_; ++i) {
      this->magnitudes_[i] = old.magnitudes_[i];
    }
  }

  return *this;
}

EuclideanVector& EuclideanVector::operator=(EuclideanVector&& old) noexcept {
  //    std::cout << "move assignment there\n";
  // avoid self assignment
  if (&old == this)
    return *this;

  this->dimension_ = std::exchange(old.dimension_, 0);
  this->magnitudes_ = std::exchange(old.magnitudes_, std::make_unique<double[]>(0));

  return *this;
}

double EuclideanVector::operator[](int i) const {
  assert(i >= 0 && i < dimension_);  // check valid index
  return this->magnitudes_[i];
}

double& EuclideanVector::operator[](int i) {
  assert(i >= 0 && i < dimension_);  // check valid index
  return this->magnitudes_[i];
}

int EuclideanVector::GetNumDimensions() const {
  return dimension_;
}

EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& v) {
  if (v.GetNumDimensions() != this->GetNumDimensions()) {
    std::stringstream err;
    err << "Dimensions of LHS(" << this->GetNumDimensions() << ") and RHS(" << v.GetNumDimensions()
        << ") do not match";
    throw EuclideanVectorError{err.str()};
  }

  for (int i = 0; i < dimension_; ++i) {
    this->magnitudes_[i] += v.magnitudes_[i];
  }

  return *this;
}
EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& v) {
  if (v.GetNumDimensions() != this->GetNumDimensions()) {
    std::stringstream err;
    err << "Dimensions of LHS(" << this->GetNumDimensions() << ") and RHS(" << v.GetNumDimensions()
        << ") do not match";
    throw EuclideanVectorError{err.str()};
  }

  for (int i = 0; i < dimension_; ++i) {
    this->magnitudes_[i] -= v.magnitudes_[i];
  }

  return *this;
}

EuclideanVector& EuclideanVector::operator*=(double b) {
  for (int j = 0; j < dimension_; ++j) {
    this->magnitudes_[j] *= b;
  }

  return *this;
}

EuclideanVector& EuclideanVector::operator/=(double b) {
  if (b == 0) {
    throw EuclideanVectorError{"Invalid vector division by 0"};
  }

  for (int j = 0; j < dimension_; ++j) {
    this->magnitudes_[j] /= b;
  }

  return *this;
}
EuclideanVector::operator std::vector<double>() const {
  std::vector<double> vec;

  for (int i = 0; i < dimension_; ++i) {
    vec.push_back(this->magnitudes_[i]);
  }

  return vec;
}

EuclideanVector::operator std::list<double>() const {
  std::list<double> l;

  for (int i = 0; i < dimension_; ++i) {
    l.push_back(this->magnitudes_[i]);
  }

  return l;
}

double EuclideanVector::at(int i) const {
  if (i < 0 || i >= dimension_) {
    std::stringstream err;
    err << "Index " << i << " is not valid for this EuclideanVector object";
    throw EuclideanVectorError{err.str()};
  }

  return this->magnitudes_[i];
}

double& EuclideanVector::at(int i) {
  if (i < 0 || i >= dimension_) {
    std::stringstream err;
    err << "Index " << i << " is not valid for this EuclideanVector object";
    throw EuclideanVectorError{err.str()};
  }

  return this->magnitudes_[i];
}

double EuclideanVector::GetEuclideanNorm() const {
  if (dimension_ == 0) {
    throw EuclideanVectorError{"EuclideanVector with no dimensions does not have a norm"};
  }

  double norm{0};

  for (int i = 0; i < dimension_; ++i) {
    norm += pow(this->magnitudes_[i], 2);
  }

  return sqrt(norm);
}
EuclideanVector EuclideanVector::CreateUnitVector() const {
  if (dimension_ == 0) {
    throw EuclideanVectorError{"EuclideanVector with no dimensions does not have a unit vector"};
  } else if (this->GetEuclideanNorm() == 0) {
    throw EuclideanVectorError{
        "EuclideanVector with euclidean normal of 0 does not have a unit vector"};
  }

  EuclideanVector unit_vec{*this};
  double norm = this->GetEuclideanNorm();

  unit_vec /= norm;

  return unit_vec;
}

std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) {
  os << '[';

  for (int i = 0; i < v.dimension_; ++i) {
    os << v.magnitudes_[i];
    if (i != (v.dimension_ - 1)) {
      os << ' ';
    }
  }

  os << ']';

  return os;
}

bool operator==(const EuclideanVector& v1, const EuclideanVector& v2) {
  if (v1.dimension_ != v2.dimension_) {
    return false;
  }

  for (int i = 0; i < v1.dimension_; ++i) {
    if (v1.magnitudes_[i] != v2.magnitudes_[i])
      return false;
  }

  return true;
}
bool operator!=(const EuclideanVector& v1, const EuclideanVector& v2) {
  return !(v1 == v2);
}

EuclideanVector operator+(const EuclideanVector& v1, const EuclideanVector& v2) {
  if (v1.dimension_ != v2.dimension_) {
    std::stringstream err;
    err << "Dimensions of LHS(" << v1.GetNumDimensions() << ") and RHS(" << v2.GetNumDimensions()
        << ") do not match";
    throw EuclideanVectorError{err.str()};
  }

  EuclideanVector result{v1};
  result += v2;

  return result;
}

EuclideanVector operator-(const EuclideanVector& v1, const EuclideanVector& v2) {
  if (v1.dimension_ != v2.dimension_) {
    std::stringstream err;
    err << "Dimensions of LHS(" << v1.GetNumDimensions() << ") and RHS(" << v2.GetNumDimensions()
        << ") do not match";
    throw EuclideanVectorError{err.str()};
  }

  EuclideanVector result{v1};
  result -= v2;

  return result;
}

double operator*(const EuclideanVector& v1, const EuclideanVector& v2) {
  if (v1.dimension_ != v2.dimension_) {
    std::stringstream err;
    err << "Dimensions of LHS(" << v1.GetNumDimensions() << ") and RHS(" << v2.GetNumDimensions()
        << ") do not match";
    throw EuclideanVectorError{err.str()};
  }

  double dot_product = 0;
  for (int i = 0; i < v1.dimension_; ++i) {
    dot_product += (v1.magnitudes_[i] * v2.magnitudes_[i]);
  }
  return dot_product;
}

EuclideanVector operator*(const EuclideanVector& v1, double i) {
  EuclideanVector result{v1};
  return (result *= i);
}

EuclideanVector operator/(const EuclideanVector& v1, double i) {
  if (i == 0) {
    throw EuclideanVectorError{"Invalid vector division by 0"};
  }

  EuclideanVector result{v1};
  return (result /= i);
}
