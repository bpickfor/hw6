#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash
{
    HASH_INDEX_T rValues[5];
    MyStringHash(bool debug = true)
    {
        if (debug)
        {
            rValues[0] = 983132572;
            rValues[1] = 1468777056;
            rValues[2] = 552714139;
            rValues[3] = 984953261;
            rValues[4] = 261934300;
        }
        else if (false == debug)
        {
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string &k) const
    {
        // Add your code here
        unsigned long long w[5] = {0}; // init array for group of 6 chars
        //^unsigned long long used to hold large base 36 vals
        // array w[5] stores up to 5 groups of base 36 nums

        int len = k.length();
        // len is length of input string, determines how many groups needed
        int index = 4; // start filling from last ele of w array (bc walk backwards when filling)

        for (int i = len - 1; i >= 0; i -= 6) // loop through back to front in groups of 6 chars
        {
            unsigned long long val = 0; // accumlates base-36 val for 1 group
            int base = 1;               // multiplier for each position in group, ex: 36^1

            for (int j = 0; j < 6 && i - j >= 0; ++j) // conv chars in group to base 36 val
            {
                val += base * letterDigitToNumber(k[i - j]);
                base *= 36; // increase base
            }

            w[index] = val; // store converted val
            --index;        // move to next position
        }

        HASH_INDEX_T h = 0;         // init final hash val to 0
        for (int i = 0; i < 5; ++i) // walk thru each group
        {                           // compute hash
            h += rValues[i] * w[i]; // multiplies each base 36 val in w with its rVal, and sums to get hash
        }

        return h; // returns final hash val
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'a' && letter <= 'z')
        {
            return letter - 'a';
        }
        else if (letter >= 'A' && letter <= 'Z')
        {
            return letter - 'A';
        }
        else if (letter >= '0' && letter <= '9')
        {
            return 26 + (letter - '0');
        }
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed); // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for (int i{0}; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
