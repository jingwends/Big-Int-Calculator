/*
Name: Jingwen Chen
Assignment 2 
Course: COSC 5340 
Date: 10/19/2023
Description: header file for the program 
*/

#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <fstream>

// Declare the bigInt class.
class bigInt {
private:
  // Two 32-bit unsigned integers to store the low-order and high-order bits of the big integer.
  unsigned int loworder;
  unsigned int highorder;

  // A flag to indicate whether the big integer has overflowed.
  int overflow;

public:
  // Default constructor.
  bigInt();

  // Overloaded `>>` operator for custom input.
  friend std::istream &operator>>(std::istream &in, bigInt &b);

  // Overloaded `<<` operator for custom output.
  friend std::ostream &operator<<(std::ostream &out, const bigInt &b);

  // Overloaded `+` operator for addition.
  bigInt operator+(const bigInt &b) const;

  // Overloaded `*` operator for multiplication.
  bigInt operator*(const bigInt &b) const;

private:
  // Shifts the bits of the big integer to the left by a specified number of positions.
  void shiftLeft(int);
};

#endif // BIGINT_H