/*
Name: Jingwen Chen
Date: 10/19/2023
Assignment 2 
Course: COSC 5340 
Description: The program is designed in C++ to implement an abstract data type called "bigInt" 
that handles unsigned integers of up to 64-bit length. 
It takes pairs of unsigned hexadecimal constants, each with a length of up to 16 hex digits, 
from an input file. For each pair, the program prints the two constants, their sum, 
and their product to an output file. Leading zeros in the input are optional.
*/

// Include the header file for the bigInt class.
#include "bigInt.h"

// Include the header files for the standard input and output streams.
#include <fstream>
#include <iostream>

// Main function
int main() {
  // Declare variables to store the input big integers, the sum of the two big integers, and the product of the two big integers.
  bigInt x, y, sum, prod;

  // Open the input file.
  std::ifstream inputFile("input.txt");

  // Open the output file.
  std::ofstream outputFile("output.txt");
  

  // Read the input big integers from the input file until the end of file is reached.
  while (!inputFile.eof()) {
    // Read the first input big integer.
    inputFile >> x;
    if (inputFile.fail()) { //checks if the input file has failed to read data
      break;
    }

    // Read the second input big integer.
    inputFile >> y;
    if (inputFile.fail()) {
      break;
    }

    // Write the two input big integers to the output file.
    outputFile << x << '\n';
    outputFile << y << '\n';

    // Calculate the sum and product of the two input big integers.
    sum = x + y;
    prod = x * y;

    // Write the sum and product of the two input big integers to the output file.
    outputFile << "Sum equals " << sum << '\n';
    outputFile << "Product equals " << prod << '\n';
  }

  // Close the input and output files.
  inputFile.close();
  outputFile.close();

  // Exit the program successfully.
  return 0;
}
