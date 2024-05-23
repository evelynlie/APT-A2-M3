#ifndef HELPER_H
#define HELPER_H
#define DEFAULT_MAIN_MENU "Main Menu: \n"\
                  "   1. Display Meal Options \n"\
                  "   2. Purchase Meal\n"\
                  "   3. Save and Exit\n"\
                  "Administrator-Only Menu:\n"\
                  "   4. Add Food\n"\
                  "   5. Remove Food\n"\
                  "   6. Display Balance\n"\
                  "   7. Abort Program\n"\
                  "Select your option (1-7): "

#define HELP_MAIN_MENU "Main Menu: \n"\
                  "   1. Display Meal Options \n"\
                  "   2. Purchase Meal\n"\
                  "   3. Save and Exit\n"\
                  "Administrator-Only Menu:\n"\
                  "   4. Add Food\n"\
                  "   5. Remove Food\n"\
                  "   6. Display Balance\n"\
                  "   7. Abort Program\n"\
                  "Note: Enter \"help\" anytime to know what commands can be executed.\n"\
                  "Select your option (1-7): "
#include "Coin.h"
#include <string>

// Declaration of readInput function with help message
std::string readInput(bool main = false, bool helpMessage = false, const std::string question = "");

// Declaration of isDivisibleByFiveCents function
bool isDivisibleByFiveCents(const std::string& price_str);

// Declaration of isNumber function
bool isNumber(std::string s);

// Declaration of compareCoins function
bool compareCoins(const Coin& coin1, const Coin& coin2);

#endif  // HELPER_H