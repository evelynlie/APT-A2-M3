#include "Helper.h"
#include "Coin.h"
#include <iostream>
#include <cstdlib>

// Helper method to read and return user input in string
std::string readInput() {
    std::string input;
    // if Ctril+D (end of file) is not pressed
    if(!std::cin.eof()) {
        std::getline(std::cin, input);
    }    
    else{ // If the user presses Ctrl+D, exit the program     
        std::cerr << "\nGoodbye!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return input;
}

// Helper method to check if the price is divisible by 5 cents
bool isDivisibleByFiveCents(const std::string& price_str) {
    double price = std::stod(price_str); // Convert string to double
    int price_cents = static_cast<int>(std::round(price * 100)); // Convert to cents
    return price_cents % 5 == 0; // Check if divisible by 5 cents
}

// Helper method to validate if the given string is a number
// Adapted from Assignment 1 Start Code
bool isNumber(std::string s) {
    std::string::const_iterator it = s.begin();
    char dot = '.';
    int nb_dots = 0;
    bool exit = false;
    while (it != s.end() && exit == false) 
    {
        if (*it == dot)
        {
            nb_dots++;
            if (nb_dots>1)
            {
                exit = true;
            }
        }   
        else if (!isdigit(*it))
        {
            exit = true;
        } 

        ++it;
    }
    return !s.empty() && s[0] != dot && it == s.end();
}

// Helper method for sorting coins
bool compareCoins(const Coin& coin1, const Coin& coin2) {
    return coin1.denom < coin2.denom; // Sort by denomination
}