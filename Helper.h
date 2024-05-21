#ifndef HELPER_H
#define HELPER_H
#include "Coin.h"
#include <string>

// Declaration of readInput function
std::string readInput();

// Declaration of isDivisibleByFiveCents function
bool isDivisibleByFiveCents(const std::string& price_str);

// Declaration of isNumber function
bool isNumber(std::string s);

// Declaration of compareCoins function
bool compareCoins(const Coin& coin1, const Coin& coin2);

#endif  // HELPER_H