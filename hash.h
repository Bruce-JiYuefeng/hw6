#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long wValues[5] = {0, 0, 0, 0, 0};
        int segmentLength = 6;
        int numSegments = (k.length() + segmentLength - 1) / segmentLength;
        unsigned long long segmentValue = 0;
        unsigned long long basePower = 1;
        unsigned long long hashValue = 0;
        unsigned long long value;
        char c;
        

        for (int segment = 0; segment < numSegments; segment++) {
            int startIdx = k.length() - segment * segmentLength - 1;
            int endIdx = std::max((int)k.length() - (segment + 1) * segmentLength, 0);
            segmentValue = 0;
            basePower = 1;

            for (int idx = startIdx; idx >= endIdx; idx--) {
                c = k[idx];
                value = letterDigitToNumber(c);
                segmentValue += value * basePower;
                basePower *= 36;
            }
            wValues[4 - segment] = segmentValue;
        }

        for (int i = 0; i < 5; i++) {
            hashValue += rValues[i] * wValues[i];
        }
        return hashValue;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= '0' && letter <= '9') return 26 + (letter - '0');
        letter = tolower(letter);  // Convert uppercase to lowercase
        if (letter >= 'a' && letter <= 'z') return letter - 'a';
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
