/*
Name: Jingwen Chen
Assignment 2 
Course: COSC 5340 
Date: 10/19/2023
Description: source file of bigInt containing implementation of the class methods (with header file included)
*/

#include "bigInt.h"
#include <iostream>
#include <fstream>
#include <iomanip>

bigInt::bigInt() : loworder(0), highorder(0), overflow(0) {}    

bigInt bigInt::operator+(const bigInt &b) const
{

    bigInt c;
    unsigned int u = 0xFFFF;
    unsigned int v = 0xFFFF0000;
    unsigned int w, z;
    int carry;

    w = (this->loworder & u) + (b.loworder & u); // w <= (loworder BITWISE AND u) + (b.loworder carry <= (w BITWISE AND v) 
    carry = (w & v) >> 16; // SHIFTED RIGHT 16 
    c.loworder = w & u; //c.loworder <= w BITWISE AND u 

//  w <= loworder BITWISE AND v
//  z <= b.loworder BITWISE AND v
//  w <= w SHIFTED RIGHT 16 bits
//  z <= z SHIFTED RIGHT 16 bits
//  w <= w+z+carry
    w = this->loworder & v; 
    z = b.loworder & v;
    w = w >> 16;
    z = z >> 16;
    w = w + z + carry;
    
    // carry <= (w BITWISE AND v) SHIFTED RIGHT 16  
    carry = (w & v) >> 16;
    z = (w & u) << 16; //z <= (w BITWISE AND u) SHIFTED LEFT 16 bits
    c.loworder = c.loworder | z; //c.loworder <= c.loworder BITWISE OR z 

    w = (this->highorder & u) + (b.highorder & u) + carry; //w <= (highorder BITWISE AND u) + (b.highorder BITWISE AND u) + carry 
    carry = (w & v) >> 16; //carry <= (w BITWISE AND v) SHIFTED RIGHT 16 bits
    c.highorder = w & u; //c.highorder <= w BITWISE AND u 


// w <= highorder BITWISE AND v
// z <= b.highorder BITWISE AND v
// w <= w SHIFTED RIGHT 16 bits
// z <= z SHIFTED RIGHT 16 bits
// w <= w+z+carry
    w = this->highorder & v;
    z = b.highorder & v;
    w = w >> 16;
    z = z >> 16;
    w = w + z + carry;
    carry = (w & v) >> 16; //carry <= (w BITWISE AND v) SHIFTED RIGHT 16 bits  c.highorder <= c.highorder BITWISE OR z 
    z = (w & u) << 16; //z <= (w BITWISE AND u) SHIFTED LEFT 16 bits
    c.highorder = c.highorder | z; //c.highorder <= c.highorder BITWISE OR z 

    c.overflow = carry; //c.overflow <= carry 

    return c;
}


// founction "*"
bigInt bigInt::operator*(const bigInt &b) const
{
    //DECLARE product,d1,acc,f:
        // bit, sw, n: k, m: 

    bigInt product, d1, acc, f;
    int bit, sw, n;
    unsigned int k, m = 0x00000001; //k,m <= 0x00000001

    
//     product.loworder <= 0
//     product.highorder <= 0

    product.loworder = 0;
    product.highorder = 0;


    acc.loworder = 0;
    acc.highorder = 0;

//  d1.loworder <= loworder
//  d1.highorder <= highorder
    d1.loworder = loworder;
    d1.highorder = highorder;

    sw = 0; //sw <= 0

// FOR(n <= 31;nGREATERTHANOREQUALTO0;n <= n-1) 
// bit <= product.highorder SHIFTED RIGHT 31 bits IF (bit IS NON-ZERO) 
// sw <= 1 END IF 
//     product.shiftLeft(1)
//     acc.shiftLeft(1)

    for (n = 31; n >= 0; --n)
    {
        bit = product.highorder >> 31;

        if (bit)
        {
            sw = 1;
        }

        product.shiftLeft(1);
        acc.shiftLeft(1);

        k = (b.highorder >> n) & m; //k <= (e.highorder SHIFTED RIGHT n bits) BITWISE AND m IF (k IS NON-ZERO) 

        if (k)
        { //product <= d1 + acc acc.loworder <= product.loworder 
            product = d1 + acc;

            //acc.highorder <= product.highorder IF (product.overflow IS NON-ZERO) 
            acc.loworder = product.loworder;
            acc.highorder = product.highorder;

            if (product.overflow)
            {
                sw = 1; //sw <= 1 END IF 
            }
        }
    }

// FOR(n <= 31;n GREATER THAN OR EQUAL TO 0;n <= n-1) bit <= product.highorder SHIFTED RIGHT 31 bits
// IF (bit IS NON-ZERO) 
// sw <= 1 END IF 

    for (n = 31; n >= 0; --n)
    {
        bit = product.highorder >> 31;

        if (bit)
        {
            sw = 1;
        }

        product.shiftLeft(1);
        acc.shiftLeft(1);

        k = (b.loworder >> n) & m; //k <= (e.loworder SHIFTED RIGHT n bits) BITWISE AND m IF (k IS NON-ZERO) 

        if (k)
        {
            product = d1 + acc;
            acc.loworder = product.loworder;
            acc.highorder = product.highorder; //acc.highorder <= product.highorder IF (product.overflow IS NON-ZERO) 

            if (product.overflow)
            {
                sw = 1;
            }
        }
    }

    f.loworder = acc.loworder;
    f.highorder = acc.highorder; //f.loworder <= acc.loworder f.highorder <= acc.highorder 
    f.overflow = sw;

    return f;
}

  

std::ostream &operator<<(std::ostream &os, const bigInt &c) //FUNCTION “<<”(PARAMETER c: REFERENCE TO bigInt)
{
    unsigned int t, x, z; //t,x,z: unsigned integers
    x = 0x0000000F;  //x <= 0x0000000f

    for (int n = 28; n >= 0; n -= 4) //FOR(n <= 28;n GREATER THAN OR EQUAL TO 0 FOR(n <= 28;n GREATER THAN OR EQUAL TO 0;n <= n-4) ;n <= n-4) 
    {
        //t <= c.highorder SHIFTED RIGHT n bits z <= t BITWISE AND x
        t = c.highorder >> n;
        z = t & x;
        os << std::hex << std::setfill('0') << std::setw(1) << z; //OUTPUT z to file as one hex digit 
    }

    // FOR(n <= 28;n GREATER THAN OR EQUAL TO 0;n <= n-4) 
    for (int n = 28; n >= 0; n -= 4)
    {
        t = c.loworder >> n; //t <= c.loworder SHIFTED RIGHT n bits 
        z = t & x; //z <= t BITWISE AND x 
        os << std::hex << std::setfill('0') << std::setw(1) << z; //OUTPUT z to file as one hex digit
    } //end for 

    if (c.overflow) //IF (c.overflow) OUTPUT ‘T’ to file
    {
        os << 'T';
    }

    return os;
} // end "<<"

//FUNCTION shiftLeft(PARAMETER n: integer)
void bigInt::shiftLeft(int n)
{
    unsigned int temp = 0; //DECLARE temp: unsigned integer


    if (n > 0 && n < 32) //IF ((0 LESS THAN n ) LOGICAL AND (n LESS THAN 32))
    {
        temp = loworder >> (32 - n); //temp <= loworder SHIFTED RIGHT (32 - n) bits 
        loworder <<= n; //loworder <= loworder SHIFTED LEFT n bits 
        highorder <<= n; //highorder <= highorder SHIFTED LEFT n bits 
        highorder |= temp; //highorder <= highorder BITWISE OR temp 
    }
    else if (n >= 32 && n < 64) //ELSE IF ((32 LESS THAN OR EQUAL TO n) LOGICAL AND (n LESS THAN 64)) 
    {
        highorder = loworder << (n - 32); //highorder <= loworder SHIFTED LEFT (n - 32) bits
        loworder = 0; //loworder <= 0 
    }
} // end shiftleft


std::istream &operator>>(std::istream &in, bigInt &b) //FUNCTION “>>”(PARAMETER x: REFERENCE TO bigInt)
{
// DECLARE digit: character
//         acc:     bigInt
//         number:  unsigned integer
    char digit;
    bigInt acc;

    acc.loworder = 0; //acc.loworder <= 0 
    acc.highorder = 0;//acc.highorder <= 0
    acc.overflow = 0; //acc.overflow <= 0

    while (true) //WHILE (digit is valid)
    {
        in.get(digit); //number <= numeric value of digit 

        if (digit == ' ' || digit == '\n' || !in)
        {
            break;
        // Check if the character is a valid hexadecimal digit.
        }

        if (std::isxdigit(digit))
        {
            unsigned int number = (digit <= '9') ? digit - '0' : std::tolower(digit) - 'a' + 10;
            acc.shiftLeft(4); //  acc.shiftLeft(4)
            acc.loworder |= number;
        }
    }
    // Copy the accumulator to the big integer object.
    b.loworder = acc.loworder;
    b.highorder = acc.highorder;
    b.overflow = 0;

    return in; // Return the input stream.
}





