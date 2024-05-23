#ifndef COIN_H
#define COIN_H

// Coin.h defines the coin structure for managing currency in the system. 
#define DELIM ","  // delimiter 

#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>  
#include <iostream>
#include <algorithm>

// enumeration representing the various types of currency available in the system. 
enum Denomination
{
    FIVE_CENTS = 5,
    TEN_CENTS = 10,
    TWENTY_CENTS = 20,
    FIFTY_CENTS = 50, 
    ONE_DOLLAR = 100, 
    TWO_DOLLARS = 200, 
    FIVE_DOLLARS = 500, 
    TEN_DOLLARS = 1000, 
    TWENTY_DOLLARS = 2000,
    FIFTY_DOLLARS = 5000
};


// Represents a coin type stored in the cash register perhaps. Each demonination
// Will have exactly one of these in the cash register.
class Coin
{
public:
    // the denomination type
    enum Denomination denom;
    
    // the count of how many of these are in the cash register
    unsigned count;

    // Function to load coin data from a file
    static std::vector<Coin> loadCoinData(const std::string& filename, bool betterMessage);

    void addCount(int amount);
};

#endif // COIN_H
